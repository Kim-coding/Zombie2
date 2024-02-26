#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "GameObject.h"
#include "UiHud.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

bool SceneGame::IsInTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGrobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return rect.contains(point);        //contains 영역 안에 있으면 true 아니면 false
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGrobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);
	return 	Utils::Clamp(point, rect);
}

void SceneGame::Init()
{
	spawners.push_back(new ZombieSpawner());        //ZombieSpawner
	spawners.push_back(new ZombieSpawner());
	itemspawners.push_back(new ItemSpawner());      //ItemSpawner

	for (auto s : spawners)
	{
		s->SetPosition(Utils::RandomOnUnitCircle() * 250.f);
		AddGo(s);
	}

	for (auto i : itemspawners)                     //ItemSpawner
	{
		i->SetPosition(Utils::RandomOnUnitCircle() * 250.f);
		AddGo(i);
	}

	player = new Player("Player");
	AddGo(player);

	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1;
	AddGo(tileMap);

	//Ui
	crosshair = new SpriteGo("Crosshair");
	crosshair->SetTexture("graphics/crosshair.png");
	crosshair->sortLayer = -1;
	crosshair->SetOrigin(Origins::MC);
	AddGo(crosshair, Layers::Ui);

	uihud = new UiHud("Hud");
	uihud->Init();
	uihud->Reset();
	AddGo(uihud, Layers::Ui);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();

	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;

	worldView.setSize(windowSize);             //화면이 캐릭터를 따라가도록 만들거임
	worldView.setCenter({ 0.f,0.f });
	uiView.setSize(windowSize);                //좌 상점이 기본으로 한다.
	uiView.setCenter(centerPos);

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition({ 0.f, 0.f });
	tileMap->SetOrigin(Origins::MC);
	//tileMap->SetRotation(45);      //타일 기울기
	//tileMap->SetScale({2.f, 2.f}); //타일 스케일 2배

	player->SetPosition({ 0.f, 0.f });

	uihud->SetScore(0);
	uihud->SetHiScore(0);
	uihud->SetAmmo(uihud->GetAmmo(), uihud->GetTotalAmmo());
	uihud->SetWave(1);
	uihud->SetZombieCount(20);
}

void SceneGame::Exit()
{
	Scene::Exit();
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
}

void SceneGame::Update(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);   //Zombie 객체를 찾아 zombieList에 push_back//

  	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());
	
	crosshair->SetPosition(ScreenToUi((sf::Vector2i)InputMgr::GetMousePos()));
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}
