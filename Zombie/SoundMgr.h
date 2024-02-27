#pragma once
#include "Singleton.h"

class SoundMgr : public Singleton<SoundMgr>
{
	friend Singleton<SoundMgr>;
private:
	SoundMgr();
	virtual ~SoundMgr();

	sf::Sound bgm[2];
	int frontBgmIndex = 0;  //PlayBgmȣ�� �� ����

	bool isFading = false; 
	float FadeDuration = 3.f;       //�� ���� �����ϴ� �ð�
	float FadeTimder = 0.f;         //PlayBgm�� ���� �ð��� ���� �Ҹ�1 ���̰� �Ҹ�2 �ø�

	float fadeSpeed = 1.f;           //�Ӱ谪
	float fadeLimit = 0.05f;

	std::list<sf::Sound*> playing;
	std::list<sf::Sound*> waiting;

	float sfxVoulme = 100.f;
	float bgmVolume = 100.f;

public:
	void SetSfxVolum(float v) { sfxVoulme = v; }
	void SetBgmVolum(float v) { bgmVolume = v; }

	void Init(int totalChannels = 1);
	void Release();
	void Update(float dt);

	void PlayBgm(std::string id, bool crossFade = true);
	void StopBgm();

	void PlaySfx(std::string id, bool loop = false);
	void PlaySfx(sf::SoundBuffer& buffer, bool loop = false);

	void StopAllSfx();

};

#define SOUND_MGR (Singleton<SoundMgr>::Instance())
