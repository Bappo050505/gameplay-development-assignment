#include "Renderer.h"
#include "IDSystem.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>

Renderer* Renderer::s_instance = nullptr;

Renderer::Renderer(SDL_Renderer* sdlRenderer) : m_renderer(sdlRenderer) 
{
	TTF_Init();
};

Renderer::~Renderer()
{
	for (TextureData im : m_images)
	{
		SDL_DestroyTexture(im.tex);
	}
	SDL_DestroyRenderer(m_renderer);
	TTF_Quit();
}

FontID Renderer::AddFont(const char* fontPath, int sizePts)
{
	FontID font;
	TTF_Font* f = TTF_OpenFont(fontPath, sizePts);
	if (f)
	{
		std::string id = fontPath;
		id.append(":" + std::to_string(sizePts));
		
		font.id = m_fonts.size();
		font.filePath = id;

		m_fonts.push_back(FontPair{id, f});
	}
	else
	{
		std::cout << "\nError: Could not find font " << fontPath << ". Is it in the build folder?";
	}

	return font;
}


FontID Renderer::GetFont(const char* fontPath, int sizePnts)
{
	std::string id = fontPath + ':' + sizePnts;
	int count = 0;
	for (FontPair f : m_fonts)
	{
		if (strcmp(f.id.c_str(), id.c_str()) == 0)
		{
			FontID font;
			font.filePath = fontPath;
			font.id = 2;
			return font;
		}
	}

	return AddFont(fontPath, sizePnts);
}

void Renderer::Create(SDL_Renderer* sdlRenderer)
{
	if (!s_instance) 
	{
		s_instance = new Renderer(sdlRenderer); 
	}
	else
	{
		std::cout << "Instance of Renderer already exists!\n";
	}
}
void Renderer::Destroy()
{
	if (s_instance)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

void Renderer::Update()
{

	// Draw all entities


	SDL_RenderPresent(m_renderer);
	SDL_RenderClear(m_renderer);
}

void Renderer::SetRenderDrawColour(int r, int g, int b)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
}

void Renderer::Remove(ImageID id)
{
	if (id.IsValid())
	{
		m_freeIdSlots.push_back(id.id);
	}
}


ImageID Renderer::AddImage(const char* filepath)
{
	int count = 0;
	ImageID out;
	out.filePath = filepath;
	for (TextureData t : m_images)
	{
		if (strcmp(t.id.c_str(), filepath) == 0)
		{
			out.id = count;
			return out;
		}
		count++;
	}

	SDL_Surface* source = SDL_LoadBMP(filepath);
	if (source)
	{
		// This sets the alpha colour. Any pixel that is (255, 0, 255) will not be rendered.
		SDL_SetColorKey(source, SDL_TRUE, SDL_MapRGB(source->format, 255, 0, 255));
		out.id = AddTexture(source, filepath);
	}

	return out;
}


ImageID Renderer::AddText(const char* text, FontID font, int r, int g, int b)
{
	ImageID out;
	int fontID = font.id;
	if (fontID < 0 || fontID >= m_fonts.size())
	{
		std::cout << "\nError: Could not find font " << fontID << std::endl;
		return out;
	}

	TTF_Font* f = m_fonts[fontID].font;
	SDL_Colour col;
	col.r = r;
	col.g = g;
	col.b = b;

	SDL_Surface* surface = TTF_RenderText_Solid(f, text, col);
	std::string id = text;
	id += ":";
	id.append(m_fonts[fontID].id);

	out.filePath = id;
	out.id = AddTexture(surface, id);

	return out;
}

int Renderer::AddTexture(SDL_Surface* s, std::string id)
{
	SDL_Texture* tex = SDL_CreateTextureFromSurface(m_renderer, s);
	SDL_FreeSurface(s);

	if (tex)
	{
		int w, h;
		SDL_QueryTexture(tex, NULL, NULL, &w, &h);
		SDL_Rect dstrect = { 0, 0, w, h };

		if (m_freeIdSlots.empty())
		{
			m_images.push_back(TextureData{ tex, id, w, h });

			return m_images.size() - 1;
		}
		else
		{
			int idx = m_freeIdSlots.back();
			m_freeIdSlots.pop_back();
			m_images[idx] = TextureData{ tex, id, w, h };
			return idx;
		}
	}
	std::cout << "Error generating text: " << id << std::endl;
	return -1;
}

void Renderer::Render(ImageID imageId, int x, int y, int sizeX, int sizeY)
{
	if (imageId.IsValid())
	{
		TextureData t = m_images[imageId.id];
		SDL_Rect location;
		location.x = x;
		location.y = y;
		location.w = sizeX == 0 ? t.w : sizeX;
		location.h = sizeY == 0 ? t.h : sizeY;
		SDL_RenderCopy(m_renderer, t.tex, NULL, &location);
	}
}