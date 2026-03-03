#include "Font.h"
#include "Renderer.h"

Font::Font(const char* filepath, int size)
{
	m_fontID = Renderer::Get()->GetFont(filepath, size).m_fontID;
}

Font::Font(int fontID)
{
	m_fontID = fontID;
}
