#pragma once
#include "SpriteGo.h"
class SprieGoEffect :
    public SpriteGo
{
protected:
    float duration = 3.f;
    float timer = 0.f;

public:
    SprieGoEffect(const std::string& name = "");
    ~SprieGoEffect();

    void SetDuration(float s) { duration = s; }

    void Reset() override;
    void Update(float dt) override;
};

