#pragma once
#include "GameObject.h"
class TileMap : public GameObject
{
protected:
	sf::VertexArray va;                  // 그리기 객체로 사용, 타일 맵을 새로 만든다
	std::string spriteSheetId;           // 
	sf::Texture* texture;

	int rows = 10;
	int cols = 10;

	sf::Vector2f cellCount;    
	sf::Vector2f cellSize;     

	sf::Transform transfrom;                //Transform변환을 표현하는 클래스// 스케일, 로테이션, 이동에 대한 변화를 나타내고 있는 것이다.
public:
	TileMap(const std::string& name = "");

	void SetSpriteSheetId(const std::string& id);
	void Set(const sf::Vector2f& count, const sf::Vector2f& size);
	void UpdateTransform();

	sf::FloatRect GetLocalBounds() override;
	sf::FloatRect GetGrobalBounds() override;

	const sf::Vector2f& GetCellSize() const { return cellSize; }
	const sf::Vector2f& GetCellCount() const { return cellCount; }

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetPosition(const sf::Vector2f& pos) override;

	void transLate(const sf::Vector2f& delta);

	void SetScale(const sf::Vector2f& scale) override;

	void SetFlipX(bool flip) override;

	void SetFlipY(bool flip) override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetRotation(float r)override;

};

