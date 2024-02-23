#include "pch.h"
#include "Zombie.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"

Zombie* Zombie::Create(Types ZombieType)
{
	Zombie* zombie = new Zombie("Zombie");

	zombie->type = ZombieType;
	switch (ZombieType)
	{
	case Zombie::Types::Bloater:
		zombie->textureId = "graphics/bloater.png";
		zombie->maxHp = 40;
		zombie->speed = 100;
		zombie->damage = 100;
		zombie->attackInterval = 1.f;

		break;
	case Zombie::Types::Chaser:
		zombie->textureId = "graphics/chaser.png";
		zombie->maxHp = 70;
		zombie->speed = 75;
		zombie->damage = 50;
		zombie->attackInterval = 0.5f;

		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = 10;
		zombie->speed = 50;
		zombie->damage = 75;
		zombie->attackInterval = 0.25;

		break;
	}

	return zombie;
}

Zombie::Zombie(const std::string& name)
	:SpriteGo(name)
{
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void Zombie::Release()
{
	SpriteGo::Release();

}

void Zombie::Reset()
{
	SpriteGo::Reset();
	hp = maxHp;
	isAlive = true;
	attackTimer = attackInterval;

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());


}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	if (!isAlive)
		return;

	direction = player->GetPosition() - position;
	SetRotation(Utils::Angle(direction));
	Utils::Normalize(direction);
	//Translate(Utils::GetNormal(direction) * speed * dt);

	sf::Vector2f pos = position + direction * speed * dt;
	if (sceneGame != nullptr)
	{
		/*sf::FloatRect tilMapBounds = tileMap->GetGrobalBounds();
		const sf::Vector2f tileSize = tileMap->GetCellSize();
		tilMapBounds.left += tileSize.x;
		tilMapBounds.top += tileSize.y;
		tilMapBounds.width -= tileSize.x * 2.f;
		tilMapBounds.height -= tileSize.y * 2.f;

		pos.x = Utils::Clamp(pos.x, tilMapBounds.left, tilMapBounds.left + tilMapBounds.width);
		pos.y = Utils::Clamp(pos.y, tilMapBounds.top, tilMapBounds.left + tilMapBounds.height);*/
		pos = sceneGame->ClampByTileMap(pos);  //주석 내용을 계산해 주는 함수
	}
	SetPosition(pos);



	//if (Utils::Distance(position, player->GetPosition()) < 50.f)  
	//{
	//	SCENE_MGR.GetCurrentScene()->RemoveGo(this);  //좀비 삭제 부분 RemoveGo에 조건에 맞는 좀비 객체 전달
	//}

	/*auto& list = sceneGame->GetZombieList();
	for (auto go : list)
	{

		if (GetGrobalBounds().intersects(go->GetGrobalBounds()))
		{

			Player* player = (Player*)go;
			if (player != nullptr)
				player->OnDamage(damage);

			break;
		}
	}*/
}

void Zombie::FixedUpdate(float dt)
{
	attackTimer += dt;

	if (attackTimer > attackInterval)
	{
		if (GetGrobalBounds().intersects(player->GetGrobalBounds()))
		{
			player->OnDamage(damage);
			attackTimer = 0.f;
		}
	}
}


void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Zombie::OnDamage(int damage)
{
	if (!isAlive)
		return;

	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Zombie::OnDie()
{
	//좀비가 죽을 때 효과를 넣어주면 됨.
	if (!isAlive)
		return;

	isAlive = false;
	SetActive(false);
	sceneGame->RemoveGo(this);

}


