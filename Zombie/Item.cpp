#include "pch.h"
#include "Item.h"
#include "Player.h"

Item* Item::Create(Types t, int v)
{
	Item* newItem = new Item();
	newItem->type = t;
	newItem->hpValue = v;

	switch (newItem->type)
	{
	case Types::Ammo:
		newItem->textureId = "graphics/ammo_pickup.png";
		break;
	case Types::Health:
		newItem->textureId = "graphics/health_pickup.png";
		break;
	}

	return newItem;
}

Item::Item(const std::string& name)
	:SpriteGo(name)
{
}

void Item::Reset()
{
	SpriteGo::Reset();
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));  //플레이어 충돌 
}

void Item::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);

	if (player == nullptr)
		return;

	if (GetGrobalBounds().intersects(player->GetGrobalBounds()))
	{
		player->OnItem(this);
		SetActive(false);
		SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	}
}
