#include "pch.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	:GameObject(name)
{
}

void UiHud::SetScore(int s)
{
	textScore.SetString(formatScore + std::to_string(s));
}

void UiHud::SetResoultion(const sf::Vector2f resolution)
{
}

void UiHud::SetHiScore(int s)
{
	textScore.SetString(formatHiScore + std::to_string(s));
}

void UiHud::SetAmmo(int current, int total)
{
	textAmmo.SetString(std::to_string(current) + " / " + std::to_string(total - current));
}

void UiHud::SetHp(int hp, int max)
{
	float value = (float)hp / max;	
	gaugeHp.setSize({ gaugeHpSize.x * value, gaugeHpSize.y });
}

void UiHud::SetWave(int w)
{
	textWave.SetString(formatWave + std::to_string(w));
}

void UiHud::SetZombieCount(int count)
{
	textZombieCount.SetString(formatZombieCount + std::to_string(count));
}



void UiHud::Init()
{
	GameObject::Init();

	textScore.Init();
	textHiScore.Init();
	imgAmmoIcon.Init();
	textAmmo.Init();
	textWave.Init();
	textZombieCount.Init();

	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");
	imgAmmoIcon.SetTexture("graphics/ammo_icon.png");

	float textSize = 40.f;
	textScore.Set(font, "", textSize, sf::Color::White);
	textHiScore.Set(font, "", textSize, sf::Color::White);
	textAmmo.Set(font, "", textSize, sf::Color::White);
	textWave.Set(font, "", textSize, sf::Color::White);
	textZombieCount.Set(font, "", textSize, sf::Color::White);
	gaugeHp.setFillColor(sf::Color::Red);
	gaugeHp.setSize(gaugeHpSize);

	textScore.SetOrigin(Origins::TL);
	textHiScore.SetOrigin(Origins::TR);
	imgAmmoIcon.SetOrigin(Origins::BL);
	textAmmo.SetOrigin(Origins::BL);
	Utils::SetOrigin(gaugeHp, Origins::BL);
	textWave.SetOrigin(Origins::BR);
	textZombieCount.SetOrigin(Origins::BR);

	//Top
	float topY = 150.f;

	textScore.SetPosition({ 150.f, topY });
	textHiScore.SetPosition({ referenceResolution.x - 150.f, topY });

	//Button
	float ButtonY = referenceResolution.y - 150.f;
	imgAmmoIcon.SetPosition({ 150.f, ButtonY });
	textAmmo.SetPosition({ 400.f, ButtonY });
	gaugeHp.setPosition({ 800.f, ButtonY });
	textWave.SetPosition({ referenceResolution.x - 400.f, ButtonY });
	textZombieCount.SetPosition({ referenceResolution.x - 150.f, ButtonY });
}

void UiHud::Release()
{
	GameObject::Release();
}

void UiHud::Update(float dt)
{
	GameObject::Update(dt);

	textScore.Update(dt);
	textHiScore.Update(dt);
	imgAmmoIcon.Update(dt);
	textAmmo.Update(dt);
	textWave.Update(dt);
	textZombieCount.Update(dt);
}

void UiHud::Reset()
{
	GameObject::Reset();

	SetScore(0);
	SetHiScore(0);
	SetAmmo(0,0);
	SetHp(10,10);
	SetWave(0);
	SetZombieCount(0);
}


void UiHud::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);

	textScore.Draw(window);
	textHiScore.Draw(window);
	imgAmmoIcon.Draw(window);
	window.draw(gaugeHp);
	textAmmo.Draw(window);
	textWave.Draw(window);
	textZombieCount.Draw(window);
}

