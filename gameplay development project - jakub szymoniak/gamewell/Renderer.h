#pragma once
#include <vector>
#include <string>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Surface;
struct TTF_Font;
class FontID;
class ImageID;
class Renderer
{
private:
	Renderer(SDL_Renderer* sdlRenderer);
	~Renderer();

	FontID AddFont(const char* fontPath, int sizePnts);
	int AddTexture(SDL_Surface* s, std::string id);

	static Renderer* s_instance;
	SDL_Renderer* m_renderer;

	struct TextureData
	{
		SDL_Texture* tex;
		std::string id;
		int w;
		int h;
	};

	struct FontPair
	{
		std::string id;
		TTF_Font* font;
	};

	std::vector<TextureData> m_images;
	std::vector<int> m_freeIdSlots;

	std::vector<FontPair> m_fonts;


public:
	static void Create(SDL_Renderer* sdlRenderer);
	static void Destroy();
	static Renderer* Get() { return s_instance; };

	void Update();
	void SetRenderDrawColour(int r, int g, int b);

	void Remove(ImageID id);

	ImageID AddImage(const char* filepath);
	ImageID AddText(const char* text, FontID font, int r = 0, int g = 0, int b = 0);
	FontID GetFont(const char* fontPath, int sizePnts);
	
	/// <summary>
	/// Renders the asset (Image or Text) according to the following params:
	/// </summary>
	/// <param name="assetID">The id of the image or text, generated when you call AddText/Image</param>
	/// <param name="x">The x pos of the leftmost point</param>
	/// <param name="y">The y pos of the topmost point</param>
	/// <param name="sizeX">The width in pixels (if 0 will use native size)</param>
	/// <param name="sizeY">The height in pixels (if 0 will use native size)</param>
	void Render(ImageID assetID, int x, int y, int sizeX = 0, int sizeY = 0);
};

