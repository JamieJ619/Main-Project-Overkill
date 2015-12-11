#pragma comment(lib,"fmodex_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"

#include <vector>
#include <string>

class SoundManager
{
public:
	~SoundManager();
	SoundManager();
	
	void PlayBackgroundMusic();
	void StopSound();
	void Update();
	void Inititialise();
	void PlayBulletSound();
	void PlayGameMusic();
private:

	FMOD::System *FMODsys;
	FMOD_RESULT result;
	FMOD::Sound *backgroundMusic;
	FMOD::Channel *channel1;

	FMOD::Sound *bulletSound;
	FMOD::Channel *channel2;

	FMOD::Sound *gameMusic;
	FMOD::Channel *channel3;
};

