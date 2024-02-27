#pragma once
#include "Scene.h"

class Player;
class Zombie;
class ZombieSpawner;
class ItemSpawner;
class TileMap;
class SpriteGo;
class UiHud;

class SceneGame : public Scene
{
public:
	enum class Status
	{
		Playing,
		NextWave,

	};

protected:
	Status currentStatus;

	Player* player = nullptr;
	TileMap* tileMap;

	UiHud* uihud;
	

	Zombie* zombie = nullptr;
	SpriteGo* crosshair;

	std::vector<ZombieSpawner*> spawners;
	std::vector<ItemSpawner*> itemspawners;   

	std::list<GameObject*> zombieList;         //좀비를 저장해주기 위함

	int wave = 1;

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	const std::list<GameObject*>& GetZombieList() { return zombieList; }
	UiHud* GetHud() {return uihud;}

	Status GetStatus() const { return currentStatus; }
	void SetStatus(Status newStatus);

	bool IsInTileMap(const sf::Vector2f& point);
	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);

	void Init() override;
	void Release()override;

	void Enter()override;
	void Exit() override;


	void Update(float dt)override;
	void Draw(sf::RenderWindow& window)override;

};

