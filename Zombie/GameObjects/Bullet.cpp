#include "pch.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Zombie.h"

Bullet::Bullet(const std::string& name)
	:SpriteGo(name)
{
}

void Bullet::Fire(const sf::Vector2f& dir, float s, int d)
{
	direction = dir;
	speed = s;
	damage = d;
	SetRotation(Utils::Angle(direction));
}

void Bullet::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/bullet.png");
	SetOrigin(Origins::ML);
}

void Bullet::Reset()
{
	SpriteGo::Reset();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void Bullet::Update(float dt)
{

	SetPosition(position + direction * speed * dt);

	if (sceneGame != nullptr)
	{
		//벽(경계)과 충돌 처리
		if (!sceneGame->IsInTileMap(position))
		{
			SetActive(false);
			sceneGame->RemoveGo(this);
		}
	}

}

void Bullet::FixedUpdate(float dt)
{
	//std::list<GameObject*> list;
	//sceneGame->FindGoAll("Zombie", list, Scene::Layers::World);   //좀비 수만 큼 순회 하므로 비 효율적
	//아래로 변경

	auto& list = sceneGame->GetZombieList();
	for (auto go : list)
	{
		if (!go->GetActive())
			continue;

		if (GetGrobalBounds().intersects(go->GetGrobalBounds()))
		{
			SetActive(false);
			sceneGame->RemoveGo(this);

			Zombie* zombie = dynamic_cast<Zombie*>(go);
			if (zombie != nullptr)
				zombie->OnDamage(damage);

			break;
		}
	}
}