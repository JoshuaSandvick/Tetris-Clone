#include "SoundHandler.h"
#include "SDL_mixer.h"

SoundHandler::SoundHandler(bool isMusicNotSound, std::string filename)
{
	if (isMusicNotSound) {
		musicTrack = Mix_LoadMUS(filename.c_str());
	}
	else {
		soundEffect = Mix_LoadWAV(filename.c_str());
	}
}


SoundHandler::SoundHandler()
{}


void SoundHandler::setSound(bool isMusicNotSound, std::string filename)
{
	if (isMusicNotSound) {
		musicTrack = Mix_LoadMUS(filename.c_str());
	}
	else {
		soundEffect = Mix_LoadWAV(filename.c_str());
	}
}


SoundHandler::~SoundHandler()
{
	//If a music track has been assigned
	if (musicTrack) {
		stopMusic();
		Mix_FreeMusic(musicTrack);
		musicTrack = NULL;
	}

	//If a sound effect has been assigned
	if (soundEffect) {
		Mix_FreeChunk(soundEffect);
		soundEffect = NULL;
	}
}

void SoundHandler::playMusic()
{
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(musicTrack, -1);
	}
}

void SoundHandler::stopMusic()
{
	if (Mix_PlayingMusic() == 1) {
		Mix_HaltMusic();
	}
}

void SoundHandler::playSound()
{
	Mix_PlayChannel(-1, soundEffect, 0);
}
