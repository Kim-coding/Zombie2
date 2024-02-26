#pragma once
#include "GameObject.h"

class SceneGame;

class Spawner : public GameObject
{
protected:
	float interval = 5.f;                         //생성 주기
	int spawnCount = 1;                           //한 번에 생성되는 수
	float radius = 250.f;                         //생성 반경

	int maxSpawn = 10;                            //최대 생성  수
	int Count = 0;                                //현재 생성된 개수
	float timer = 0.f;
	float WaveTimer = 0.f;

	int zombieCount;

	SceneGame* sceneGame = nullptr;
public:
	Spawner(const std::string& name = "");
	~Spawner() override = default;

	virtual GameObject* Create();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	int GetMaxSpawn() { return maxSpawn; }
	void SetMaxSpawn(int s) { maxSpawn = s; }
};

