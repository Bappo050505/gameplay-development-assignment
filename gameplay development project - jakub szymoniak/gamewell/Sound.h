#pragma once
#include "IDSystem.h"

class Sound final
{
public:
	/// Plays a music track. Only one can play at once.
	/// music - The ID Generated from LoadMusic for the track you want to play
	/// returns - true if successful, false if cannot play
	static bool PlayMusic(MusicID music);

	/// Stops Music from playing
	static void StopMusic();

	/// Plays a sfx track. Many can play at once.
	/// sound - The ID Generated from LoadMusic for the track you want to play
	/// returns - true if successful, false if cannot play
	static bool PlaySFX(SFXID sound);

	/// Load a music track
	/// musicTrackPath - The relative path to the sound. Relative to the executable location (or main in debugging)
	/// returns a valid ID if successful. An invalid ID otherwise. Test with IsValid()
	static MusicID LoadMusic(const char* musicTrackPath);

	/// Load an SFX track
	/// sfxTrackPath - The relative path to the sound. Relative to the executable location (or main in debugging)
	/// returns a valid ID if successful. An invalid ID otherwise. Test with IsValid()
	static SFXID LoadSFX(const char* sfxTrackPath);
};

