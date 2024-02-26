#include "pch.h"
#include "ZombieSpawner.h"
#include "SceneGame.h"

ZombieSpawner::ZombieSpawner(const std::string& name)
	:Spawner(name)
{
}


GameObject* ZombieSpawner::Create()
{
	Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size() - 1)];
	return 	Zombie::Create(zombieType);
}

void ZombieSpawner::Reset()
{
	Spawner::Reset();

	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Bloater);      //랜덤으로 뽑을 때 확률 변화를 주기 위해 여러번 작성
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);

	interval = 1.f;
	spawnCount = 1;
	radius = 250.f;

	timer = 0.f;
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

}


