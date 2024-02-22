#include "pch.h"
#include "ZombieSpawner.h"

ZombieSpawner::ZombieSpawner(const std::string& name)
	:GameObject(name)
{
}

void ZombieSpawner::Init()
{
	GameObject::Init();
}

void ZombieSpawner::Release()
{
	GameObject::Release();

}

void ZombieSpawner::Reset() //초기 값으로 돌려 줌
{
	GameObject::Reset();

	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Bloater);      //랜덤으로 뽑을 때 확률 변화를 주기 위해 여러번 작성
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);

	interval = 1.f;
	spawnCount = 1;
	radius = 250.f;

	timer = 0.f;
}

void ZombieSpawner::Update(float dt)
{
	GameObject::Update(dt);
	timer += dt;
	if (timer > interval)
	{
		timer = 0.f;

		for (int i = 0; i < spawnCount; ++i)
		{
			sf::Vector2f pos = position + Utils::RandomInUnitCircle() * radius;  //랜덤한 위치에 생성
			Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];
			
			Zombie* zombie = Zombie::Create(zombieType);
			zombie->Init();
			zombie->Reset();
			zombie->SetPosition(pos);

			SCENE_MGR.GetCurrentScene()->AddGo(zombie);
		}
	}

}
