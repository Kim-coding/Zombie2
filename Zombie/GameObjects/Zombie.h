#pragma once
#include "SpriteGo.h"

class Player;
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
	static const int TotalTypes = 3;   
	static Zombie* Create(Types ZombieType);

protected:
	Types type;
	
	
	int maxHp;
	float speed;
	int damage;
	float attackInterval;
	float attackTimer = 0.f;

	
	int hp;
	
	Player* player = nullptr;
	SceneGame* sceneGame = nullptr;

	sf::Vector2f direction;
	bool isAlive = true;

	Zombie(const std::string& name = "");
public:
	
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void OnDamage(int damage);
	void OnDie();
};

