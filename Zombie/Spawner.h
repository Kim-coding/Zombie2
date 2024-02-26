#pragma once
#include "GameObject.h"

class SceneGame;

class Spawner : public GameObject
{
protected:
	float interval = 5.f;                         //���� �ֱ�
	int spawnCount = 1;                           //�� ���� �����Ǵ� ��
	float radius = 250.f;                         //���� �ݰ�

	int maxSpawn = 10;                            //�ִ� ����  ��
	int Count = 0;                                //���� ������ ����
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

