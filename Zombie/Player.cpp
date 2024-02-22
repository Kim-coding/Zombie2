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

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();                          // ��ũ�� ��ǥ ���� ��ǥ�� ����� �� �ʿ䰡 ����
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	//std::cout << mouseWorldPos.x << "     " << mouseWorldPos.y << std::endl;  //TEST

	look = mouseWorldPos - position;
	Utils::Normalize(look);        

	float angle = Utils::Angle(look);          //����
	sprite.setRotation(angle);

	//SetRotation(); //ȣ��
	//�÷��̾���� ���콺 �����͸� �ٶ󺸴� ����� ����

	
	direction.x = InputMgr::GetAxis(Axis::Horizontal);    //������ �ڵ�
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	SetPosition(position + direction * speed * dt);
	//Translate(position + direction * speed * dt);        //���� ����

	
	//float h = InputMgr::GetAxis(Axis::Horizontal);        //�� �ڵ�
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
