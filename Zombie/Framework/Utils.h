#pragma once

class Utils
{
public:
	static float Clamp(float v, float min, float max);
	static sf::Vector2f Clamp(const sf::Vector2f& v, const sf::FloatRect& rect);

	static sf::FloatRect ResizeRect(const sf::FloatRect& rect, const sf::Vector2f& delta);

	// Random
	static float RandomValue(); // 0.0f ~ 1.0f
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static int RandomRange(int min, int maxExclude);


	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins originPreset);

	//Math 함수
	static float SqrMagnitude(const sf::Vector2f& vec);      //길이 * 길이
	static float Magnitude(const sf::Vector2f& vec);         // 길이
	static void Normalize(sf::Vector2f& vec);  //벡터의 길이를 1로 바꾼 벡터 반환
	static sf::Vector2f GetNormal(const sf::Vector2f& vec);  //벡터의 길이를 1로 바꾼 벡터 반환
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2);  //p1에서 p2의 방향
	
	static float RadianToDegree(float radian);
	static float DegreeToRad(float degree);
	static float Angle(const sf::Vector2f& vec);

	//선형보간 : 최소값 최댓값 사이의 값들을 뽑아 내는 것 
	//0,0부터 1,1를 연결한 부분에 해당하는 값?
	static float Lerp(float min, float max, float t);    //선형 보간
	//카메라에 적용 가능 //플레이어가 움직이면 카메라가 따라감(할당X)
	//max값에는 도달 X max값에 거의 도달하면 max로 변환 시켜줘야 함

	static sf::Vector2f Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float t);


};