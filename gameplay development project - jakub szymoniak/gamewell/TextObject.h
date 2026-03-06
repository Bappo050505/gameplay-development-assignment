#pragma once
#include "Object.h"
#include "IDSystem.h"


/// A simple struct to hold a colour value.
/// Alpha is not currently used, so is not included here.
struct Colour { int r, g, b; };

/// A Text Object. Functions like any other Object once created.
class TextObject : public Object
{
public:
	/// Constuctor for use without a pre-existing Font.
	/// text - The text you want on screen
	/// fontPath - The location of the .ttf file (Must be ttf format!) 
	/// fontSize - The size in points. This is not pixel size. 
	/// x - The X position to render at 
	/// y - The Y Position to render at 
	/// textColour - R G B colour values (range 0-255) for the text 
	/// m_shouldDraw - Whether rendering is enabled 
	TextObject(const char* text, const char* fontPath, int fontSize, int x, int y, Colour textColour, bool m_shouldDraw);

	/// Constuctor for use with a pre-existing Font.
	/// text - The text you want on screen 
	/// font - The size in points. This is not pixel size. 
	/// x - The X position to render at 
	/// y - The Y Position to render at 
	/// textColour - R G B colour values (range 0-255) for the text 
	/// m_shouldDraw - Whether rendering is enabled 
	TextObject(const char* text, FontID font, int x, int y, Colour textColour, bool m_shouldDraw);

	/// Use this to extract the font used for this object. 
	/// It can be used to create new TextObjects more easily.
	virtual FontID GetFont() final;


	void SetText(const char* text);
	void SetColour(const Colour& text);

private:
	void Init(const char* text, const FontID& fontid, const Colour& c, bool shouldDraw);

	FontID m_font;
	Colour m_colour;
	const char* m_text;
};

