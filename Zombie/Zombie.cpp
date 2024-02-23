#include "pch.h"
#include "Zombie.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"

Zombie* Zombie::Create(Types ZombieType)
{
	Zombie* zombie = new Zombie();

	zombie->type = ZombieType;
	switch (ZombieType)
	{
	case Zombie::Types::Bloater:
		zombie->textureId = "graphics/bloater.png";
		zombie->maxHp = 40;
		zombie->speed = 100;

		break;
	case Zombie::Types::Chaser:
		zombie->textureId = "graphics/chaser.png";
		zombie->maxHp = 70;
		zombie->speed = 75;

		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = 10;
		zombie->speed = 50;

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
	
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());


}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2f direction = player->GetPosition() - position;
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



	if (Utils::Distance(position, player->GetPosition()) < 50.f)  
	{
		SCENE_MGR.GetCurrentScene()->RemoveGo(this);  //좀비 삭제 부분 RemoveGo에 조건에 맞는 좀비 객체 전달
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}


