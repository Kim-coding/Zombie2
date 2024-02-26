#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "GameObject.h"

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

	for (auto i : itemspawners)                    //ItemSpawner
	{
		i->SetPosition(Utils::RandomOnUnitCircle() * 100.f);
		AddGo(i);
	}

	player = new Player("Player");
	AddGo(player);

	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1;
	AddGo(tileMap);

	mospoint = new SpriteGo("mospoint");
	mospoint->SetTexture("graphics/crosshair.png");
	mospoint->SetOrigin(Origins::MC);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();


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
}

void SceneGame::Exit()
{
	Scene::Exit();

}

void SceneGame::Update(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);   //Zombie 객체를 찾아 zombieList에 push_back//

  	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		TileMap* tilemap = dynamic_cast<TileMap*>(FindGo("Background"));
		if (tilemap->sortLayer == 1)
		{
			tilemap->sortLayer = 1;          //타일을 제일 앞으로 보내기
		}
		else
		{
			tilemap->sortLayer = -1;         //타일을 제일 뒤로 보내기
		}
		ResortGo(tilemap);
	}
	
	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);
	mospoint->SetPosition(mouseWorldPos);
	AddGo(mospoint);

	/*좀비 Scene클래스 에서 삭제되도록 만들었음*/
	//std::vector<GameObject*> removeZombies;      //좀비 객체들을 저장할 공간
	//for (auto obj : gameObjects)
	//{
	//	Zombie* zombie = dynamic_cast<Zombie*>(obj);
	//	if (zombie != nullptr)
	//	{
	//		float distance = Utils::Distance(player->GetPosition(), zombie->GetPosition());
	//		if (distance <= 10.f)
	//		{
	//			removeZombies.push_back(zombie);           //player와 거리가 10이하인 것은 충돌된 것으로 삭제 대상
	//		}
	//	}
	//}

	/*for (auto obj : removeZombies)
	{
		RemoveGo(obj);
		delete obj;
	}*/
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
