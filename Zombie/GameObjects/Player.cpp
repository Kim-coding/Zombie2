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
	//tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background")); //���� ������ ����
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();                          // ��ũ�� ��ǥ ���� ��ǥ�� ����� �� �ʿ䰡 ����
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	//std::cout << mouseWorldPos.x << "     " << mouseWorldPos.y << std::endl;  //TEST

	look = mouseWorldPos - position;
	Utils::Normalize(look);        

	float angle = Utils::Angle(look);          //�ٶ󺸴� ����
	SetRotation(angle);

	//�÷��̾���� ���콺 �����͸� �ٶ󺸴� ����� ����

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	
	sf::Vector2f pos = position + direction * speed * dt;

	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);

	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		if (magazine >= maxAmmo)      //������ źâ�� ������ ���ο� źâ ��ü �ϹǷ� 20�� ������ ����
		{
			magazine -= maxAmmo;
			ammo += maxAmmo;
			if (ammo >= maxAmmo)
			{
				ammo = maxAmmo;
			}
		}
		else
		{
			ammo += magazine;
			magazine = 0;
			if (ammo >= 20)
			{
				ammo = 20;
			}
		}
		sceneGame->GetHud()->SetAmmo(ammo, magazine + ammo);
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		isFiring = true;

	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		isFiring = false;

	}

	fireTimer += dt;                                //�߻� ����
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
	ammo -= 1;
	sceneGame->GetHud()->SetAmmo(ammo, magazine + ammo);
		
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
		magazine += item->GetAmmoValue();
		if (magazine > maxMagazine)
			magazine = maxMagazine;
		sceneGame->GetHud()->SetAmmo(ammo, magazine + ammo);
		break;
	case Item::Types::Health:
		hp += item->GetHpValue();
		sceneGame->GetHud()->SetHp(hp, maxHp);
		break;
	}
}
