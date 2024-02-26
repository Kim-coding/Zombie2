#include "pch.h"
#include "SprieGoEffect.h"

SprieGoEffect::SprieGoEffect(const std::string& name)
{
}

SprieGoEffect::~SprieGoEffect()
{
}

void SprieGoEffect::Reset()
{
	SpriteGo::Reset();
}

void SprieGoEffect::Update(float dt)
{
	timer += dt;
	if (timer > duration)
	{
		SetActive(false);
		SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	}
}
