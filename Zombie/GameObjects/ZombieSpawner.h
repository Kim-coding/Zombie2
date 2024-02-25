#pragma once
#include "GameObject.h"
#include "Zombie.h"

class SceneGame;

class ZombieSpawner : public GameObject
{
protected:
	std::vector<Zombie::Types> zombieTypes;       //생성할 좀비 종류

	float interval = 1.f;                         //좀비 생성 주기

	int spawnCount = 1;                           //한 번에 생성되는 좀비 수

	float radius = 250.f;                         //좀비 생성 반경

	float timer = 0.f;

	SceneGame* sceneGame = nullptr;
public:
	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;



};

