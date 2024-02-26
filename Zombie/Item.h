#pragma once
#include "SpriteGo.h"

class Player;

class Item : public SpriteGo
{
public:
	enum class Types
	{
		None = -1,
		Ammo,
		Health,
		Count,
	};

	static Item* Create(Types t, int v);
protected:
	Types type = Types::None;
	int value = 500;               // ������

	Player* player;

public:
	Item(const std::string& name = "");
	~Item() override = default;

	Types GetType() const { return type; }
	int GetValue() const { return value; }

	void Reset() override;
	void FixedUpdate(float dt) override;

};

