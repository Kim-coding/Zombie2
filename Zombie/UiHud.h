#pragma once
#include "GameObject.h"
#include "TextGo.h"
#include "SpriteGo.h"

class SpritGo;
class TextGo;

class UiHud : public GameObject
{
protected:
	std::string formatScore = "Score: ";
	std::string formatHiScore = "Hi Score: ";
	std::string formatWave = "Wave: ";
	std::string formatZombieCount = "Zombies: ";

	TextGo textScore;
	TextGo textHiScore;
	SpriteGo imgAmmoIcon;
	TextGo textAmmo;
	sf::RectangleShape gaugeHp;
	TextGo textWave;
	TextGo textZombieCount;

	sf::Vector2f gaugeHpSize = {500,40};

	sf::Vector2f referenceResolution = { 1920, 1080 };
	sf::Vector2f resolution;

public:
	UiHud(const std::string& name = "");
	virtual ~UiHud() override = default;

	void SetResoultion(const sf::Vector2f resolution);

	void SetScore(int s);
	void SetHiScore(int s);

	void SetAmmo(int current, int total);
	void SetHp(int hp, int max);
	void SetWave(int w);
	void SetZombieCount(int count);


	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	virtual void Draw(sf::RenderWindow& window) override;
};

