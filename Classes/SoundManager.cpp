#include "stdafx.h"
#include "SoundManager.h"
#include <string>
#include "SFML\System\Vector2.hpp"

SoundManager::SoundManager()
{
	enable3dAudio = true;

	FMOD::System_Create(&FMODsys);
	FMODsys->init(100, FMOD_INIT_NORMAL, 0);
}


SoundManager::~SoundManager()
{
}

void SoundManager::Inititialise()
{

	FMODsys->createSound("pistolSound.mp3", FMOD_DEFAULT, 0, &bulletSound);
	FMODsys->createSound("reload.wav", FMOD_DEFAULT, 0, &reloadSound);

	FMODsys->createStream("test.mp3", FMOD_LOOP_NORMAL | FMOD_3D, 0, &zombieSound);

	FMODsys->createStream("backgroundMusic.wav", FMOD_DEFAULT, 0, &backgroundMusic);
	backgroundMusic->setMode(FMOD_LOOP_NORMAL);

	//FMODsys->createStream("backgroundMusic1.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &gameMusic);
	//gameMusic->setMode(FMOD_LOOP_NORMAL);
}

void SoundManager::PlayBackgroundMusic()
{
	FMODsys->playSound(FMOD_CHANNEL_REUSE, backgroundMusic, false, &channel1);
	//channel1->setVolume(0.8f);
	
} 

void SoundManager::PlayBulletSound()
{
	FMODsys->playSound(FMOD_CHANNEL_REUSE, bulletSound, false, &channel2);
	//channel2->setVolume(1);
}
void SoundManager::PlayReloadSound()
{
	FMODsys->playSound(FMOD_CHANNEL_REUSE, reloadSound, false, &channel4);
	//channel4->setVolume(1);
}
/*
void SoundManager::PlayGameMusic()
{
	FMODsys->playSound(FMOD_CHANNEL_REUSE, gameMusic, false, &channel3);
	//channel3->setVolume(0.7f);
}
*/
void SoundManager::PlayZombieSound()
{
	float volume = 1.0f;
	sourcePos = { 300.0f, 0.0f, 400.0f };
	FMODsys->playSound(FMOD_CHANNEL_REUSE, zombieSound, false, &channel5);
	channel5->setVolume(volume);
	channel5->set3DMinMaxDistance(100, 1000);

	FMODsys->createReverb(&reverb);
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_SEWERPIPE;
	reverb->setProperties(&prop);
	FMOD_VECTOR pos = { 300, 0.0f, 400 };
	float mindist = 150;
	float maxdist = 150;
	reverb->set3DAttributes(&pos, mindist, maxdist);
	reverb->setActive(true);
}

void SoundManager::StopSound()
{
	channel1->stop();
}
void SoundManager::PauseMusic()
{
	channel1->setPaused(true);
	channel3->setPaused(true);
}
void SoundManager::UnPauseMusic()
{
	channel1->setPaused(false);
	channel3->setPaused(false);
}

void SoundManager::Update(sf::Vector2f p_pos, sf::Vector2f p_vel)
{
	FMOD_VECTOR  listenerpos = { p_pos.x, 0.0f, p_pos.y };
	FMOD_VECTOR  listenervel = { 0, 0,0 };

	if (enable3dAudio)
	{
		if (dopplerEnabaled)
			listenervel = { p_vel.x, 0.0f, p_vel.y };

		FMODsys->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);
		channel5->set3DAttributes(&sourcePos, 0);
	}
	else
	{
		FMOD_VECTOR zero = { 0, 0, 0 };
		channel5->set3DAttributes(&zero, 0);
		FMODsys->set3DListenerAttributes(0, &zero, &zero, 0, 0);
	}

	FMODsys->update();
}

