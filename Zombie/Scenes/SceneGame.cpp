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

	return rect.contains(point);        //contains ���� �ȿ� ������ true �ƴϸ� false
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

	worldView.setSize(windowSize);             //ȭ���� ĳ���͸� ���󰡵��� �������
	worldView.setCenter({ 0.f,0.f });
	uiView.setSize(windowSize);                //�� ������ �⺻���� �Ѵ�.
	uiView.setCenter(centerPos);

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition({ 0.f, 0.f });
	tileMap->SetOrigin(Origins::MC);
	//tileMap->SetRotation(45);      //Ÿ�� ����
	//tileMap->SetScale({2.f, 2.f}); //Ÿ�� ������ 2��

	player->SetPosition({ 0.f, 0.f });
}

void SceneGame::Exit()
{
	Scene::Exit();

}

void SceneGame::Update(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);   //Zombie ��ü�� ã�� zombieList�� push_back//

  	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		TileMap* tilemap = dynamic_cast<TileMap*>(FindGo("Background"));
		if (tilemap->sortLayer == 1)
		{
			tilemap->sortLayer = 1;          //Ÿ���� ���� ������ ������
		}
		else
		{
			tilemap->sortLayer = -1;         //Ÿ���� ���� �ڷ� ������
		}
		ResortGo(tilemap);
	}
	
	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);
	mospoint->SetPosition(mouseWorldPos);
	AddGo(mospoint);

	/*���� SceneŬ���� ���� �����ǵ��� �������*/
	//std::vector<GameObject*> removeZombies;      //���� ��ü���� ������ ����
	//for (auto obj : gameObjects)
	//{
	//	Zombie* zombie = dynamic_cast<Zombie*>(obj);
	//	if (zombie != nullptr)
	//	{
	//		float distance = Utils::Distance(player->GetPosition(), zombie->GetPosition());
	//		if (distance <= 10.f)
	//		{
	//			removeZombies.push_back(zombie);           //player�� �Ÿ��� 10������ ���� �浹�� ������ ���� ���
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
