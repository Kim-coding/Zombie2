#include "pch.h"
#include "Player.h"

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

	
	direction.x = InputMgr::GetAxis(Axis::Horizontal);    //선생님 코드
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	SetPosition(position + direction * speed * dt);
	//Translate(position + direction * speed * dt);        //위와 동일

	
	//float h = InputMgr::GetAxis(Axis::Horizontal);        //내 코드
	//sf::Vector2f posX = sprite.getPosition();
	//posX.x += h * speed * dt;
	//SetPosition(posX);

	//float v = InputMgr::GetAxis(Axis::Vertical);
	//sf::Vector2f posY = sprite.getPosition();
	//posY.y += v * speed * dt;
	//SetPosition(posY);
	
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
