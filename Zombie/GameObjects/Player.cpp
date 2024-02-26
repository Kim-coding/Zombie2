#include "pch.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Item.h"
#include "UiHud.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);

	isFiring = false;
	fireTimer = fireInterval;
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();

	isFiring = false;
	fireTimer = fireInterval;

	hp = maxHp;
	ammo = maxAmmo;
	
	isAlive = true;
	isNoDamage = false;

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	//tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background")); //위의 것으로 변경
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();                          // 스크린 좌표 월드 좌표로 만들어 줄 필요가 있음
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	//std::cout << mouseWorldPos.x << "     " << mouseWorldPos.y << std::endl;  //TEST

	look = mouseWorldPos - position;
	Utils::Normalize(look);        

	float angle = Utils::Angle(look);          //바라보는 방향
	SetRotation(angle);

	//플레이어부터 마우스 포인터를 바라보는 방향과 각도

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	
	sf::Vector2f pos = position + direction * speed * dt;
	//if (tileMap != nullptr)
	//{
	//  /*sf::FloatRect tileMapBounds = tileMap->GetGrobalBounds();
	//	const sf::Vector2f tileSize = tileMap->GetCellSize();
	//	tileMapBounds.left += tileSize.x;
	//	tileMapBounds.top += tileSize.y;
	//	tileMapBounds.width -= tileSize.x * 2.f;
	//	tileMapBounds.height -= tileSize.y * 2.f;*/

	//	//Utils::Clamp(const sf::Vector2f& v, const sf::FloatRect& rect)함수로 대체
	//	//pos.x = Utils::Clamp(pos.x, tileMapBounds.left, tileMapBounds.left + tileMapBounds.width);
	//	//pos.y = Utils::Clamp(pos.y, tileMapBounds.top, tileMapBounds.top + tileMapBounds.height);

	//} //아래 걸로 변경

	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);


	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		isFiring = true;

	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		isFiring = false;

	}

	fireTimer += dt;                                //발사 간격
	if (isFiring && fireTimer > fireInterval && ammo > 0)
	{
		Fire();
		fireTimer = 0.f;
	}
	if (isNoDamage)
	{
		noDamageTimer += dt;
		if (noDamageTimer > noDamageTime)
		{
			isNoDamage = false;
		}
	}
}


void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::Fire()
{
	Bullet* bullet = new Bullet();
	bullet->Init();
	bullet->Reset();
	bullet->SetPosition(position);
	bullet->Fire(look, bulletSpeed, bulletDamage);
	sceneGame->AddGo(bullet);

	SOUND_MGR.PlaySfx("sound/shoot.wav");

}

void Player::OnDamage(int damage)
{
	if (!isAlive || isNoDamage)
		return;

	hp -= damage;
	sceneGame->GetHud()->SetHp(hp,maxHp);

	isNoDamage = true;
	noDamageTimer = 0.f;

	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Player::OnDie()
{
	if (!isAlive)
		return;

	isAlive = false;
	SetActive(false);
}

void Player::OnItem(Item* item)
{
	switch (item->GetType())
	{
	case Item::Types::Ammo:
		ammo += item->GetValue();
		break;
	case Item::Types::Health:
		hp += item->GetValue();
		sceneGame->GetHud()->SetHp(hp, maxHp);
		break;
	}
}
