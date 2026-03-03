#include "TextObject.h"
#include "Renderer.h"
#include <iostream>

TextObject::TextObject(const char* text, FontID fontid, int x, int y, Colour c, bool shouldDraw) : Object(x, y, shouldDraw), m_font(fontid)
{
	Init(text, m_font, c, shouldDraw);
}


TextObject::TextObject(const char* text, const char* fontPath, int fontSize, int x, int y, Colour c, bool shouldDraw) : Object(x,y,shouldDraw)
{
	m_font = Renderer::Get()->GetFont(fontPath, fontSize);
	Init(text, m_font, c, shouldDraw);
}

void TextObject::Init(const char* text, const FontID& fontid, const Colour& c, bool shouldDraw)
{
	if (m_imageIDs)
	{
		Renderer::Get()->Remove(m_imageIDs[0]);
		delete[] m_imageIDs;
		m_imageIDs = nullptr;
	}

	m_colour = c;
	m_text = text;

	m_imageIDs = new ImageID[1];
	if (!(m_imageIDs[0] = Renderer::Get()->AddText(text, m_font, c.r, c.g, c.b)).IsValid())
	{
		std::cout << "Could not create text: " << text << std::endl;
	}
}

FontID TextObject::GetFont()
{
	return m_font;
}

void TextObject::SetText(const char* text)
{
	Init(text, m_font, m_colour, GetShouldDraw());
}

void TextObject::SetColour(const Colour& col)
{
	m_colour = col;
}
