#include "pch.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	//tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background")); //위의 것으로 변경
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();                          // 스크린 좌표 월드 좌표로 만들어 줄 필요가 있음
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	//std::cout << mouseWorldPos.x << "     " << mouseWorldPos.y << std::endl;  //TEST

	look = mouseWorldPos - position;
	Utils::Normalize(look);        

	float angle = Utils::Angle(look);          //각도
	sprite.setRotation(angle);

	//SetRotation(); //호출
	//플레이어부터 마우스 포인터를 바라보는 방향과 각도

	
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	/*SetPosition(position + direction * speed * dt);*/
	//Translate(position + direction * speed * dt);        //위와 동일
	
	sf::Vector2f pos = position + direction * speed * dt;
	//if (tileMap != nullptr)
	//{
	//  /*sf::FloatRect tileMapBounds = tileMap->GetGrobalBounds();
	//	const sf::Vector2f tileSize = tileMap->GetCellSize();
	//	tileMapBounds.left += tileSize.x;
	//	tileMapBounds.top += tileSize.y;
	//	tileMapBounds.width -= tileSize.x * 2.f;
	//	tileMapBounds.height -= tileSize.y * 2.f;*/

	//	//Utils::Clamp(const sf::Vector2f& v, const sf::FloatRect& rect)함수로 대체
	//	//pos.x = Utils::Clamp(pos.x, tileMapBounds.left, tileMapBounds.left + tileMapBounds.width);
	//	//pos.y = Utils::Clamp(pos.y, tileMapBounds.top, tileMapBounds.top + tileMapBounds.height);

	//} //아래 걸로 변경

	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
