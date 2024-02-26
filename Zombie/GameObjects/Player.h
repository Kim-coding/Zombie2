#pragma once
#include "SpriteGo.h"

class SceneGame;
class Zombie;
class Item;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = {0.f, 0.f};  //πÊ«‚ ∫§≈Õ
	sf::Vector2f look = {1.f,0.f};        //»∏¿¸ ∫§≈Õ
	float speed = 500.f;

	SceneGame* sceneGame = nullptr;
	Zombie* zombie;

	float fireInterval = 0.5f;
	float bulletSpeed = 1000.f;
	int bulletDamage = 30;
	
	int maxHp = 1000;
	int hp;
	int maxAmmo = 20;
	int ammo = maxAmmo;

	bool isAlive = true;
	bool isNoDamage = false;
	float noDamageTime = 0.5f;
	float noDamageTimer = 0.f;

	bool isFiring = false;
	float fireTimer = 0.f;
public:
	Player(const std::string& name = "");
	~Player() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire();

	void OnDamage(int damage);
	void OnDie();
	void OnItem(Item* item);
};

