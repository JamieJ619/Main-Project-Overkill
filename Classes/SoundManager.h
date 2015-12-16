#pragma comment(lib,"fmodex_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"

#include <vector>
#include <string>
#include "SFML\System\Vector2.hpp"

class SoundManager
{
public:
	~SoundManager();
	SoundManager();
	
	void PlayBackgroundMusic();
	void StopSound();
	void Update(sf::Vector2f p_pos, sf::Vector2f p_vel);
	void Inititialise();
	
	void PlayBulletSound();
	//void PlayGameMusic();
	void PlayReloadSound();
	void PauseMusic();
	void UnPauseMusic();
	
	void PlayZombieSound();

	bool enable3dAudio = true;
	bool dopplerEnabaled = false;
	bool reverbEnabled = true;
	FMOD_VECTOR sourcePos;
	FMOD::Reverb *reverb;


private:

	FMOD::System *FMODsys;
	FMOD_RESULT result;
	FMOD::Sound *backgroundMusic;
	FMOD::Channel *channel1;

	FMOD::Sound *bulletSound;
	FMOD::Channel *channel2;

	FMOD::Sound *gameMusic;
	FMOD::Channel *channel3;

	FMOD::Sound *reloadSound;
	FMOD::Channel *channel4;

	FMOD::Sound *zombieSound;
	FMOD::Channel *channel5;
};

