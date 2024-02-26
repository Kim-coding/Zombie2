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

	int score = 0;
	int hiscore = 0;
	int ammo = 20;
	int totalAmmo = 60;
	int wave = 1;

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

	
	/////////////////추가부분////////////////////////
	void AddScore(int score)
	{
		this->score += score;
		SetScore(this->score);
	}
	void AddHiScore()
	{	
		if (hiscore < score)
		{
			hiscore += 10;
			SetHiScore(hiscore);
		}
	}
	void AddWave()        //모든 좀비가 다 죽으면 웨이브 1 증가
	{
		wave += 1;
		SetWave(wave);
	}
	int GetAmmo()
	{
		return ammo;
	}
	int GetTotalAmmo()
	{
		return totalAmmo;
	}
	
	/////////////////////////////////////////////////
	

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	virtual void Draw(sf::RenderWindow& window) override;
};

