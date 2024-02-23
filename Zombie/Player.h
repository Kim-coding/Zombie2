#pragma once
#include "SpriteGo.h"

class SceneGame;
class Zombie;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = {0.f, 0.f};  //���� ����
	sf::Vector2f look = {1.f,0.f};        //ȸ�� ����

	float speed = 500.f;

	SceneGame* sceneGame = nullptr;
	Zombie* zombie;

	bool isFiring = false;
	float fireInterval = 0.5f;
	float bulletSpeed = 1000.f;

	int bulletDamage = 30;
	float fireTime = 0.f;
	
	int maxHp = 100;
	int hp;
	bool isAlive = false;
	bool isNoDamage = false;
	float noDamageTimer = 0.f;
	float noDamageTime = 0.5f;

	float fireTimer = 0.f;
public:
	Player(const std::string& name = "");
	~Player() override = default;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void Fire();
	void OnDamage(int damage);
	void OnDie();
};

