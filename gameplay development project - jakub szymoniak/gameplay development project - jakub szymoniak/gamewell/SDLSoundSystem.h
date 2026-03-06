#pragma once
#include <vector>

struct Mix_Chunk;
struct Mix_Music;
class SDLSoundSystem
{
public:
	static SDLSoundSystem* Get();

	bool PlayMusic(int music);
	void StopMusic();
	bool PlaySFX(int sound);

	int LoadMusic(const char* musicTrackPath);
	int LoadSFX(const char* sfxTrackPath);


private:
	static SDLSoundSystem* instance;

	std::vector<Mix_Chunk*> m_sfx;
	std::vector<Mix_Music*> m_music;
};