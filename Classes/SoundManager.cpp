#include "stdafx.h"
#include "SoundManager.h"
#include <string>

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::Inititialise()
{
	FMOD::System_Create(&FMODsys);
	FMODsys->init(100, FMOD_INIT_NORMAL, 0);

	FMODsys->createSound("pistolSound.mp3", FMOD_DEFAULT, 0, &bulletSound);

	FMODsys->createStream("backgroundMusic.wav", FMOD_DEFAULT, 0, &backgroundMusic);
	backgroundMusic->setMode(FMOD_LOOP_NORMAL);

	FMODsys->createSound("backgroundMusic1.mp3", FMOD_DEFAULT, 0, &gameMusic);
	gameMusic->setMode(FMOD_LOOP_NORMAL);
}

void SoundManager::PlayBackgroundMusic()
{
	FMODsys->playSound(FMOD_CHANNEL_FREE, backgroundMusic, false, &channel1);
	channel1->setVolume(0.8f);
	
} 
void SoundManager::PlayBulletSound()
{
	FMODsys->playSound(FMOD_CHANNEL_REUSE, bulletSound, false, &channel2);
	channel2->setVolume(1);
}
void SoundManager::PlayGameMusic()
{
	FMODsys->playSound(FMOD_CHANNEL_REUSE, gameMusic, false, &channel3);
	channel3->setVolume(0.2f);
}

void SoundManager::StopSound()
{
	channel1->stop();
}

void SoundManager::Update()
{
	FMODsys->update(); // very important!!!
}

