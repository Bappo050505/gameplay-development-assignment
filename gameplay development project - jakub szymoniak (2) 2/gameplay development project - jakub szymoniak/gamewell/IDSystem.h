#pragma once
#include <string>

/// System for generating the various IDs you need to load for the game to hold onto data.
/// Each type interfaces directly with the associated system but denies access to variables so they can only be internally created.
/// You should only ever need to pass these around - you should never need to inspect them except to call IsValid() to check if the ID is good.
class BaseID
{
public:
	BaseID();
	bool IsValid();
protected:	
	std::string filePath;
	int id;
};

// Renderer IDs
class Renderer;
class ImageID final : public BaseID
{
protected:
	friend class Renderer;
};

class FontID : public BaseID
{
protected:
	friend class Renderer;
};



// Sound IDs
class Sound;
class SoundBase : public BaseID
{
	friend class Sound;
};

class MusicID final : public SoundBase 
{
};

class SFXID final : public SoundBase 
{
};