#pragma once
class Renderer;
class FontBase
{
protected:
	friend class Renderer;
	int m_fontID;
};
