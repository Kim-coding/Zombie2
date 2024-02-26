#include "pch.h"
#include "SoundMgr.h"

SoundMgr::SoundMgr()
{
}

SoundMgr::~SoundMgr()
{
	Release();
}

void SoundMgr::Init(int totalChannels)  //����Ʈ ����
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

void SoundMgr::PlayBgm(std::string id, bool crossFade)//crossFade�κ��� ����
{

}

void SoundMgr::StopBgm()
{



}

void SoundMgr::PlaySfx(std::string id, bool loop)
{
	PlaySfx(RES_MGR_SOUND_BUFFER.Get(id),loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)   //���� ���
{
	sf::Sound* sound = nullptr;
	if (waiting.empty())          //��������� ���� �� �������� 
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