#include "pch.h"
#include "Scene.h"

Scene::Scene(SceneIds id) :
	id(id),
	texResMgr(RES_MGR_TEXTURE),
	fontResMgr(RES_MGR_FONT),
	soundResMgr(RES_MGR_SOUND_BUFFER)
{
}

sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, worldView);
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f worldPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPos, uiView);
}

sf::Vector2f Scene::ScreenToUi(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, uiView);
}

sf::Vector2i Scene::UiToScreen(sf::Vector2f UiPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(UiPos, uiView);
}

void Scene::Init()
{
	for (auto obj : gameObjects)
	{
		obj->Init();
	}
	for (auto obj : uigameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		delete obj;
	}
	gameObjects.clear();

	for (auto obj : uigameObjects)
	{
		delete obj;
	}
	uigameObjects.clear();
}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
	for (auto obj : uigameObjects)
	{
		obj->Reset();
	}
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
	for (auto obj : uigameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}

	for (auto obj : resortingGameObjects)
	{
		auto it = std::find(gameObjects.begin(), gameObjects.end(), obj);
		if (it != gameObjects.end())
		{
			gameObjects.remove(obj);
			AddGo(obj, Layers::World);
			continue;
		}

		it = std::find(uigameObjects.begin(), uigameObjects.end(), obj);
		if (it != uigameObjects.end())
		{
			uigameObjects.remove(obj);
			AddGo(obj, Layers::Ui);
			continue;
		}
	}
	resortingGameObjects.clear();

	for (auto obj : removeGameObjects)
	{
		gameObjects.remove(obj);
		uigameObjects.remove(obj);

		delete obj;
	}
	removeGameObjects.clear();
}

void Scene::Draw(sf::RenderWindow& window)
{
	//gameObjects.sort([](auto a, auto b) {
	//	if (a->sortLayer != b->sortLayer)
	//	{
	//	return a->sortLayer < b->sortLayer;
	//	}
	//	return a->sortOrder < b->sortOrder; 
	//});

	//uigameObjects.sort([](auto a, auto b) {                   //함수를 식으로 구현하는 것 : 람다식?이락 함
	//	if (a->sortLayer != b->sortLayer)                     //이름 없는 함수
	//	{
	//		return a->sortLayer < b->sortLayer;
	//	}
	//	return a->sortOrder < b->sortOrder;
	//});                                                        //이와 같은 것은 복잡도가 높음 N X logN

	const sf::View& saveView = window.getView();

	window.setView(worldView);          //화면이 플레이어를 따라 가도록
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}

	window.setView(uiView);
	for (auto obj : uigameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}

	window.setView(saveView);           
}

GameObject* Scene::FindGo(const std::string& name, Layers layer)
{
	if ((layer & Layers::World) == Layers::World)
	{
		for (auto obj : gameObjects)
		{
			if (obj->name == name)
			{
				return obj;
			}
		}
	}
	if ((layer & Layers::Ui) == Layers::Ui)
	{
		for (auto obj : uigameObjects)
		{
			if (obj->name == name)
			{
				return obj;
			}
		}
	}
	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list, Layers layer)
{
	list.clear();                                     //리스트를 비워 새로 찾은 값을 넣어주기 위함
	if ((layer & Layers::World) == Layers::World)
	{
		for (auto obj : gameObjects)
		{
			if (obj->name == name)
			{
				list.push_back(obj);
			}
		}
	}
	if ((layer & Layers::World) == Layers::World)
	{
		for (auto obj : uigameObjects)
		{
			if (obj->name == name)
			{
				list.push_back(obj);
			}
		}
	}
	return list.size();                               //찾은 값의 개수 리턴
}

GameObject* Scene::AddGo(GameObject* obj, Layers layer)
{
	if(layer == Layers::World)
	{ 
		if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
		{
			auto it = gameObjects.begin();
			while (it != gameObjects.end())
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					gameObjects.insert(it, obj);
					return obj;
				}
				++it;
			}
			gameObjects.push_back(obj);
			return obj;
		}
	}
	
	if (layer == Layers::Ui)
	{
		if (std::find(uigameObjects.begin(), uigameObjects.end(), obj) == uigameObjects.end())
		{
			auto it = uigameObjects.begin();
			while (it != uigameObjects.end())
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					uigameObjects.insert(it, obj);
					return obj;
				}
				++it;
			}
		}
		uigameObjects.push_back(obj);
		return obj;
	}
	return nullptr;
}

void Scene::ResortGo(GameObject* obj)
{
	resortingGameObjects.push_back(obj);
}

void Scene::RemoveGo(GameObject* obj)
{	
	//obj->SetActive(false);
	removeGameObjects.push_back(obj);
}
