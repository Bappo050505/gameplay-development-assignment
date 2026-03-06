#include "SDLSoundSystem.h"
#include <iostream>

#include "SDL_Mixer.h"

SDLSoundSystem* SDLSoundSystem::instance = nullptr;
SDLSoundSystem* SDLSoundSystem::Get()
{
    if (!instance)
    {
        instance = new SDLSoundSystem();
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            return nullptr;
        }
    }
    return instance;
}

bool SDLSoundSystem::PlayMusic(int music)
{
    if (music != -1)
    {
        return !((Mix_PlayMusic(m_music[music], INT_MAX) == -1));
    }

    std::cout << "\nInvalid music ID: -1\n";
    return false;
}

void SDLSoundSystem::StopMusic()
{
    Mix_HaltMusic();
}

bool SDLSoundSystem::PlaySFX(int sound)
{
    if (sound != -1)
    {
        return !((Mix_PlayChannel(-1, m_sfx[sound], 0) == -1));
    }

    std::cout << "\nInvalid sound ID: -1\n";
    return false;
}

int SDLSoundSystem::LoadMusic(const char* musicTrackPath)
{
    Mix_Music* out = Mix_LoadMUS(musicTrackPath);
    if (out)
    {
        m_music.push_back(out);
        return m_music.size() - 1;
    }
    std::cout << "\nError loading \"" << musicTrackPath << "\" Music could not be located!\n";
    return -1;
}

int SDLSoundSystem::LoadSFX(const char* sfxTrackPath)
{
    Mix_Chunk* out = Mix_LoadWAV(sfxTrackPath);
    if (out)
    {
        m_sfx.push_back(out);
        return m_sfx.size() - 1;
    }

    std::cout << "\nError loading \"" << sfxTrackPath << "\" SFX could not be located!\n";
}
