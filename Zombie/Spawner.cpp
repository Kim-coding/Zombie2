#include "pch.h"
#include "Spawner.h"
#include "SceneGame.h"
#include "UiHud.h"

Spawner::Spawner(const std::string& name)
	:GameObject(name)
{
}

GameObject* Spawner::Create()
{
	return nullptr;
}

void Spawner::Init()
{
	GameObject::Init();
}

void Spawner::Release()
{
	GameObject::Release();

}

void Spawner::Reset()
{
	GameObject::Reset();

	interval = 1.f;
	spawnCount = 1;
	radius = 250.f;
	maxSpawn = 10;

	timer = 0.f;
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void Spawner::Update(float dt)
{
	GameObject::Update(dt);

	timer += dt;
	zombieCount = sceneGame->GetHud()->GetZombies();
	if (zombieCount == 0)
	{
		WaveTimer += dt;
		if (WaveTimer > 5)
		{
			WaveTimer = 0.f;
			maxSpawn *= 2;
			Count = 0;
		}

	}

	if (timer > interval && Count < maxSpawn )
	{
		timer = 0.f;

		for (int i = 0; i < spawnCount; ++i)
		{
			sf::Vector2f pos = position + Utils::RandomInUnitCircle() * radius;
			if (sceneGame != nullptr)
			{
				pos = sceneGame->ClampByTileMap(pos);
			}
			GameObject* newGo = Create();
			newGo->Init();
			newGo->Reset();
			newGo->SetPosition(pos);

			SCENE_MGR.GetCurrentScene()->AddGo(newGo);
		}
		++Count;
	}

}
