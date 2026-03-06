#include "Sound.h"
#include "SDLSoundSystem.h"
#include <iostream>


bool Sound::PlayMusic(MusicID music)
{
    if (!SDLSoundSystem::Get()->PlayMusic(music.id))
    {
        std::cout << "Music \"" << music.filePath << "\" has failed to play!";
        return false;
    }
    return true;
}

void Sound::StopMusic()
{
    return SDLSoundSystem::Get()->StopMusic();
}

bool Sound::PlaySFX(SFXID sound)
{
    if (!SDLSoundSystem::Get()->PlaySFX(sound.id))
    {
        std::cout << "Sound \"" << sound.filePath << "\" has failed to play!";
        return false;
    }
    return true;
}

MusicID Sound::LoadMusic(const char* musicTrackPath)
{
    MusicID result;
    result.id = SDLSoundSystem::Get()->LoadMusic(musicTrackPath);
    result.filePath = musicTrackPath;
    return result;
}

SFXID Sound::LoadSFX(const char* musicTrackPath)
{
    SFXID result;
    result.id = SDLSoundSystem::Get()->LoadSFX(musicTrackPath);
    result.filePath = musicTrackPath;
    return result;
}
