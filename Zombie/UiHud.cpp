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
	textHiScore.SetString(formatHiScore + std::to_string(s));
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

	float textSize = 50.f;
	textScore.Set(font, "", textSize, sf::Color::White);
	textHiScore.Set(font, "", textSize, sf::Color::White);
	textAmmo.Set(font, "", textSize, sf::Color::White);
	textWave.Set(font, "", textSize, sf::Color::White);
	textZombieCount.Set(font, "", textSize, sf::Color::White);
	gaugeHp.setFillColor(sf::Color::Red);


	textScore.SetOrigin(Origins::TL);
	textHiScore.SetOrigin(Origins::TR);
	imgAmmoIcon.SetOrigin(Origins::BL);
	textAmmo.SetOrigin(Origins::BL);
	Utils::SetOrigin(gaugeHp, Origins::BL);
	textWave.SetOrigin(Origins::BR);
	textZombieCount.SetOrigin(Origins::BR);

	//Top
	float topY = 50.f;

	textScore.SetPosition({ 100.f, topY });
	textHiScore.SetPosition({ referenceResolution.x - 100.f, topY });

	//Button
	float ButtonY = referenceResolution.y - 50.f;
	imgAmmoIcon.SetPosition({ 150.f, ButtonY });
	textAmmo.SetPosition({ 400.f, ButtonY });
	gaugeHp.setPosition({ 600.f, ButtonY });
	textWave.SetPosition({ referenceResolution.x - 600.f, ButtonY });
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

	if (zombies == 0)
	{
		timer += dt;
		if (timer > 5)
		{
			NextWave();
			spawnerZpmbies *= 2;
			zombies = spawnerZpmbies;
			SetZombies(zombies);
		}
	}

}

void UiHud::Reset()
{
	GameObject::Reset();

	spawnerZpmbies = 20;

	SetScore(0);
	SetHiScore(0);
	SetAmmo(20, 80);
	SetHp(1,1);
	SetWave(1);
	SetZombieCount(20);
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

