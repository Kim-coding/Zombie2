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

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);

	void Init() override;
	void Release()override;

	void Enter()override;
	void Exit() override;

	void Update(float dt)override;
	void Draw(sf::RenderWindow& window)override;

};

