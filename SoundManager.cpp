#include "SoundManager.h"

SoundManager* SoundManager::soundManagerInstance = 0;

SoundManager::SoundManager()
{
	/* The SoundManager class is a singleton, this works because there should be only one place that the sounds are stored
	and it should be accessible from anywhere in the game. Before sound can be used, Mix_OpenAudio must be called to set
	up the audio for the game. Mix_OpenAudio takes the parameters of (int frequency, Uint16 format, int channels, int
	chunksize) */

	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

SoundManager::~SoundManager()
{
	// When SoundManager is destroyed, let's close all audio
	Mix_CloseAudio();
}

SoundManager* SoundManager::Instance()
{
	if (soundManagerInstance == 0)
	{
		soundManagerInstance = new SoundManager();
		return soundManagerInstance;
	}

	return soundManagerInstance;
}

bool SoundManager::LoadAudio(string fileName_, string ID_, SoundType type_)
{
	/* When loading a music file or a sound effect into SoundManager, pass in the type of sound we want to load as an
	enum called SoundType. This type is then used to decide which std::map to add the loaded sound to and also which
	LoadAudio function to use from SDL_mixer. */

	if (type_ == SOUND_MUSIC)
	{
		Mix_Music* mixMusic = Mix_LoadMUS(fileName_.c_str());

		if (mixMusic == 0)
		{
			cout << "Couldn't load music: ERROR - " << Mix_GetError() << endl;
			return false;
		}

		music[ID_] = mixMusic;
		return true;
	}

	else if (type_ == SOUND_SFX)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(fileName_.c_str());

		if (chunk == 0)
		{
			cout << "Couldn't load SFX: ERROR - " << Mix_GetError() << endl;
			return false;
		}

		SFXs[ID_] = chunk;
		return true;
	}

	return false;
}

void SoundManager::PlaySound(string ID_, int loop_)
{
	/* Mix_PlayChannel takes an int value as the 1st parameter, which is the channel that the sound is to be played on. 
	A value of -1 tells SDL_mixer to play the sound on any available channel. */
	Mix_PlayChannel(-1, SFXs[ID_], loop_);
}

void SoundManager::PlayMusic(string ID_, int loop_)
{
	Mix_PlayMusic(music[ID_], loop_);
}
