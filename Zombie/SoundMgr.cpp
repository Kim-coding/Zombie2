#include "pch.h"
#include "SoundMgr.h"

SoundMgr::SoundMgr()
{
}

SoundMgr::~SoundMgr()
{
	Release();
}

void SoundMgr::Init(int totalChannels)  //리스트 세팅
{
	Release();
	for (int i = 0; i < totalChannels; ++i)
	{
		waiting.push_back(new sf::Sound());
	}
}

void SoundMgr::Release()
{
	for (auto sound : waiting)
	{
		delete sound;
	}
	waiting.clear();
	for (auto sound : playing)
	{
		delete sound;
	}
	playing.clear();
}

void SoundMgr::Update(float dt)
{
	//if (InputMgr::GetKeyDown(sf::Keyboard::Num1))      //테스트 코드
	//{
	//	//PlayBgm(/*bgm넣는 부분*/);
	//}
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		bgmVolume = 25.f;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))  
	{
		bgmVolume = 100.f;
	}


	if (isFading)
	{
		bool isEndBack = false;
		bool isEndfront = false;

		int backBgmIndex = (frontBgmIndex == 1) ? 0 : 1;

		float backVolume = bgm[backBgmIndex].getVolume();
		backVolume = Utils::Lerp(backVolume, 0.f, dt * fadeSpeed);
		bgm[backBgmIndex].setVolume(backVolume);
		if (abs(backVolume) < fadeLimit)
		{
			bgm[backBgmIndex].setVolume(0.f);
			bgm[backBgmIndex].stop();
			isEndBack = true;
		}

		float frontVolume = bgm[frontBgmIndex].getVolume();
		frontVolume = Utils::Lerp(backVolume, bgmVolume, dt * fadeSpeed);
		bgm[frontBgmIndex].setVolume(backVolume);
		if (abs(backVolume - frontVolume) < fadeLimit)
		{
			bgm[frontBgmIndex].setVolume(backVolume);
			isEndfront = true;
		}

		if (isEndBack && isEndfront)
		{
			isFading = false;
		}
	}

}


void SoundMgr::PlayBgm(std::string id, bool crossFade) //crossFade부분을 구현부분
{
	isFading = true;
	frontBgmIndex = (frontBgmIndex + 1) % 2; //0 1 0 1 0 1반전되서 나옴

	int backBgmIndex = (frontBgmIndex == 1) ? 0 : 1;

	FadeTimder = 0.f;
	bgm[frontBgmIndex].setBuffer(RES_MGR_SOUND_BUFFER.Get(id));
	bgm[frontBgmIndex].setVolume(0);
	bgm[frontBgmIndex].setLoop(0);
	bgm[frontBgmIndex].play();
}

void SoundMgr::StopBgm()
{
	/////////////////////////////////
}

void SoundMgr::PlaySfx(std::string id, bool loop)
{
	PlaySfx(RES_MGR_SOUND_BUFFER.Get(id),loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)   //사운드 재생
{
	sf::Sound* sound = nullptr;
	if (waiting.empty())          //재생가능한 것이 꽈 차있으면 
	{
		sound = playing.front(); 
		playing.pop_front();
		sound->stop();  
	}
	else
	{
		sound = waiting.front();
		waiting.pop_front();
	}

	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->setVolume(sfxVoulme);
	sound->play();

	playing.push_back(sound);
}

void SoundMgr::StopAllSfx()
{
	for (auto sound : playing)
	{
		sound->stop();
		waiting.push_back(sound);
	}
	playing.clear();
}