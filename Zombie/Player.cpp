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
	//tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background")); //���� ������ ����
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();                          // ��ũ�� ��ǥ ���� ��ǥ�� ����� �� �ʿ䰡 ����
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	//std::cout << mouseWorldPos.x << "     " << mouseWorldPos.y << std::endl;  //TEST

	look = mouseWorldPos - position;
	Utils::Normalize(look);        

	float angle = Utils::Angle(look);          //����
	sprite.setRotation(angle);

	//SetRotation(); //ȣ��
	//�÷��̾���� ���콺 �����͸� �ٶ󺸴� ����� ����

	
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	/*SetPosition(position + direction * speed * dt);*/
	//Translate(position + direction * speed * dt);        //���� ����
	
	sf::Vector2f pos = position + direction * speed * dt;
	//if (tileMap != nullptr)
	//{
	//  /*sf::FloatRect tileMapBounds = tileMap->GetGrobalBounds();
	//	const sf::Vector2f tileSize = tileMap->GetCellSize();
	//	tileMapBounds.left += tileSize.x;
	//	tileMapBounds.top += tileSize.y;
	//	tileMapBounds.width -= tileSize.x * 2.f;
	//	tileMapBounds.height -= tileSize.y * 2.f;*/

	//	//Utils::Clamp(const sf::Vector2f& v, const sf::FloatRect& rect)�Լ��� ��ü
	//	//pos.x = Utils::Clamp(pos.x, tileMapBounds.left, tileMapBounds.left + tileMapBounds.width);
	//	//pos.y = Utils::Clamp(pos.y, tileMapBounds.top, tileMapBounds.top + tileMapBounds.height);

	//} //�Ʒ� �ɷ� ����

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
