#pragma once

#include <iostream>
#include <map>

#include <SDL_mixer.h>

using namespace std;

enum SoundType
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public:
	static SoundManager* Instance();

	bool LoadAudio(string fileName_, string ID_, SoundType type_);

	void playSound(string ID_, int loop_);
	void PlayMusic(string ID_, int loop_);

private:
	static SoundManager* soundManagerInstance;

	/* These maps stores pointers to one of two different types used by SDL_mixer (Mix_Chunk* and Mix_Music*), keyed 
	using strings. The Mix_Chunk* types are used for sound effects and the Mix_Music* types are of course used for music. */
	map<string, Mix_Chunk*> SFXs;
	map<string, Mix_Music*> music;

	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&);
	SoundManager& operator=(const SoundManager&);
};

typedef SoundManager TheSoundManager;