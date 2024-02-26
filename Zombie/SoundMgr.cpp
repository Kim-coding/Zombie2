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
	
}

void SoundMgr::PlayBgm(std::string id, bool crossFade)//crossFade부분을 구현
{

}

void SoundMgr::StopBgm()
{



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