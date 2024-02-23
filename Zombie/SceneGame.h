#pragma once
#include "Scene.h"

class Player;
class Zombie;
class ZombieSpawner;
class TileMap;
class SpriteGo;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	TileMap* tileMap;

	Zombie* zombie = nullptr;
	SpriteGo* mospoint;
	std::vector< ZombieSpawner*> spawners;

	std::list<GameObject*> zombieList;         //좀비를 저장해주기 위함

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	const std::list<GameObject*>& GetZombieList() { return zombieList; }


	bool IsInTileMap(const sf::Vector2f& point);
	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);

	void Init() override;
	void Release()override;

	void Enter()override;
	void Exit() override;

	void Update(float dt)override;
	void Draw(sf::RenderWindow& window)override;

};

