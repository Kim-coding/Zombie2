#include "pch.h"
#include "Utils.h"

float Utils::Clamp(float v, float min, float max)
{
	if (v < min)
		return min;
	if (v > max)
		return max;
	return v;
}

sf::Vector2f Utils::Clamp(const sf::Vector2f& v, const sf::FloatRect& rect)
{
	
	return sf::Vector2f(Clamp(v.x, rect.left, rect.left + rect.width), Clamp(v.y, rect.top, rect.top + rect.height));
}

sf::FloatRect Utils::ResizeRect(const sf::FloatRect& rect, const sf::Vector2f& delta)
{
	sf::FloatRect newRect = rect;
	newRect.width += delta.x;
	newRect.height += delta.y;

	newRect.left -= delta.x * 0.5f;
	newRect.top -= delta.y * 0.5f;

	return newRect;
}

float Utils::RandomValue()
{
	return (float)rand() / RAND_MAX;
}

float Utils::RandomRange(float min, float max)
{
	float value = RandomValue();
	value *= max - min;	
	value += min;
	return value;
}

sf::Vector2f Utils::RandomOnUnitCircle()
{
	sf::Transform rotation;
	rotation.rotate(RandomRange(0.f, 360.f));
	return rotation * sf::Vector2f (1.f, 0.f);
}

sf::Vector2f Utils::RandomInUnitCircle()
{
	return RandomOnUnitCircle() * RandomValue();
}

int Utils::RandomRange(int min, int maxExclude)
{
	int range = maxExclude - min;
	int rand = std::rand() % range;
	rand += min;
	return rand;
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect)
{
	// Rect Width, Height
	sf::Vector2f newOrigin(rect.width, rect.height);
	newOrigin.x *= ((int)originPreset % 3) * 0.5f; // 0 1 2 => 0 0.5 1
	newOrigin.y *= ((int)originPreset / 3) * 0.5f; // 0 1 2 => 0 0.5 1
	obj.setOrigin(newOrigin);

	return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Magnitude(const sf::Vector2f& vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);       //sqrt 루트값 계산하는 함수
}

void Utils::Normalize( sf::Vector2f& vec)                 //1, -1로 만들어 줌, 방향 구할 때 사용할 수 있게
{
	float mag = Magnitude(vec);
	if (mag != 0.f)
	{
		vec /= mag;
	}

}


sf::Vector2f Utils::GetNormal(const sf::Vector2f& vec)
{
	float mag = Magnitude(vec);
	if (mag == 0.f)
		return vec;
	return vec / mag;
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return Magnitude(p2 - p1);
}

float Utils::RadianToDegree(float radian)
{
	return radian * (180.0 / M_PI);
}

float Utils::DegreeToRad(float degree)
{
	return degree * (M_PI / 180.0);
}

float Utils::Angle(const sf::Vector2f& vec)
{
	return RadianToDegree(std::atan2f(vec.y, vec.x));
}
