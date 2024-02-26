#include "pch.h"
#include "ItemSpawner.h"
#include "SceneGame.h"

ItemSpawner::ItemSpawner(const std::string& name)
	:Spawner(name)
{
}

GameObject* ItemSpawner::Create()
{
	Item::Types itemType = itemTypes[Utils::RandomRange(0, itemTypes.size() - 1)];
	return Item::Create(itemType, 10);
}

void ItemSpawner::Reset()
{
	Spawner::Reset();

	itemTypes.push_back(Item::Types::Ammo);
	itemTypes.push_back(Item::Types::Ammo);
	itemTypes.push_back(Item::Types::Ammo);
	itemTypes.push_back(Item::Types::Health);
	itemTypes.push_back(Item::Types::Health);

	interval = 5.f;
	spawnCount = 1;
	radius = 200.f;

	timer = 0.f;
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}
