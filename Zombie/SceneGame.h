#pragma once
#include "Scene.h"

class Player;
class Zombie;
class ZombieSpawner;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	Zombie* zombie = nullptr;

	std::vector< ZombieSpawner*> spawners;

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Release()override;

	void Enter()override;
	void Exit() override;

	void Update(float dt)override;
	void Draw(sf::RenderWindow& window)override;

};

