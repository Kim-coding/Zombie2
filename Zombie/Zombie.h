#pragma once
#include "SpriteGo.h"
#include "Player.h"

class SceneGame;

class Zombie : public SpriteGo
{
public:
	enum class Types   //좀비 종류
	{
		Bloater,
		Chaser,
		Crawler,
	};
	static const int TotalTypes = 3;   //좀비 수?
	static Zombie* Create(Types ZombieType);

protected:
	Types type;
	
	//스텟
	int maxHp;
	float speed;

	//현재 상태
	int hp;
	
	Player* player;                     //좀비가 플레이어를 추적할 수 있도록
	SceneGame* sceneGame = nullptr;
	Zombie(const std::string& name = "");

public:
	~Zombie() override = default;

	void Init()override;
	void Release()override;
	void Reset()override;
	void Update(float dt)override;
	void Draw(sf::RenderWindow& window)override;
};

