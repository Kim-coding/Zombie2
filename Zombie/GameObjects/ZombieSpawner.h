#pragma once
#include "Spawner.h"
#include "Zombie.h"

class SceneGame;

class ZombieSpawner : public Spawner
{
protected:
	std::vector<Zombie::Types> zombieTypes;       //생성할 좀비 종류
public:
	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner() override = default;

	GameObject* Create() override;

	void Reset() override;
};

