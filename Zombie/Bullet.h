#pragma once
#include "GameObject.h"

class Player;
class Zombie;

class Bullet : public GameObject
{
protected:
	sf::CircleShape shape;

	float speed = 1000.f;
	sf::Vector2f direction = {0, 0};



public:
	Bullet(const std::string& name = "");

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

