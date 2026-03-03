#include "Object.h"
#include "Renderer.h"
#include "InputManager.h"
#include "IDSystem.h"
#include <iostream>

//Object::Object(): m_x(0), m_y(0), m_w(0), m_h(0), m_shouldDraw(false), m_animIdx(0), m_animTimer(0), m_shouldCollide(false), m_scale(0), m_numFrames(-1), m_imageIDs(nullptr), m_timerInterval(0)
//{
//
//}

Object::Object(const char* filepath, int x, int y, int width, int height, bool shoulddraw) : m_x(x), m_y(y), m_w(width), m_h(height), m_shouldDraw(shoulddraw), m_animIdx(0), m_animTimer(0), m_shouldCollide(true), m_scale(1), m_deletable(false)
{
	Init(filepath, x, y, width, height, shoulddraw);
}

Object::Object(const char* filepath[], int numImages, int fps, int x, int y, int width, int height, bool shoulddraw) : m_x(x), m_y(y), m_w(width), m_h(height), m_shouldDraw(shoulddraw), m_animIdx(0), m_animTimer(0), m_shouldCollide(true), m_scale(1)
{
	InitAnimated(filepath, numImages, fps, x, y, width, height, shoulddraw);
}

Object::Object(const Object& other) : m_x(other.m_x), m_y(other.m_y), m_w(other.m_w), m_h(other.m_h), m_shouldDraw(other.m_shouldDraw), m_animIdx(other.m_animIdx), m_animTimer(other.m_animTimer), m_shouldCollide(other.m_shouldCollide)
, m_numFrames(other.m_numFrames), m_timerInterval(other.m_timerInterval), m_scale(other.m_scale)
{
	m_imageIDs = new ImageID[m_numFrames];
	for (int i = 0; i < m_numFrames; ++i)
	{
		m_imageIDs[i] = other.m_imageIDs[i];
	}
}


Object::Object(int x, int y, bool shouldDraw) : m_x(x), m_y(y), m_w(0), m_h(0), m_shouldDraw(shouldDraw), m_animIdx(0), m_animTimer(0), m_shouldCollide(true), m_numFrames(1), m_timerInterval(-1), m_scale(0), m_imageIDs(nullptr)
{
}

Object::~Object()
{
	if (m_imageIDs)
	{
		delete[] m_imageIDs;
		m_imageIDs = nullptr;
	}
}

void Object::Init(const char* filepath, int x, int y, int width, int height, bool shoulddraw)
{
	m_x = x;
	m_y = y;
	m_w = width;
	m_h = height;
	m_shouldDraw = shoulddraw;
	m_shouldCollide = true;
	m_scale = 1;

	m_imageIDs = new ImageID[1];
	ImageID out;
	if (!(out = Renderer::Get()->AddImage(filepath)).IsValid())
	{
		std::cout << "Could not find image at " << filepath << std::endl;
	}

	m_imageIDs[0] = out;
	m_timerInterval = -1;
	m_numFrames = 1;
}



void Object::InitAnimated(const char* filepath[], int numImages, int fps, int x, int y, int width, int height, bool shoulddraw)
{
	m_x = x;
	m_y = y;
	m_w = width;
	m_h = height;
	m_shouldDraw = shoulddraw;
	m_shouldCollide = true;
	m_scale = 1;

	m_imageIDs = new ImageID[numImages];
	for (int i = 0; i < numImages; ++i)
	{
		if (!(m_imageIDs[i] = Renderer::Get()->AddImage(filepath[i])).IsValid())
		{
			std::cout << "Could not find image at " << filepath[i] << std::endl;
		}
	}
	m_timerInterval = (60.f / fps) / 60.f;
	m_numFrames = numImages;
}

void Object::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Object::SetUniformScale(float percentOfOriginalSize)
{
	m_scale = percentOfOriginalSize;
}

void Object::SetShouldDraw(bool draw)
{
	m_shouldDraw = draw && m_numFrames > -1;
}

void Object::SetShouldCollide(bool collide)
{
	m_shouldCollide = collide && m_numFrames > -1;
}

void Object::GetPosition(float& x, float& y)
{
	x = m_x;
	y = m_y;
}


void Object::GetDimensions(int& x, int& y, int& w, int& h) const
{
	x = m_x;
	y = m_y;
	w = m_w;
	h = m_h;
}

bool Object::GetShouldDraw() const
{
	return m_shouldDraw;
}

bool Object::GetShouldCollide() const
{
	return m_shouldCollide;
}

void Object::Update()
{
	if (m_numFrames > 1)
	{
		if ((m_animTimer += InputManager::Get()->GetDeltaTime()) >= m_timerInterval)
		{
			m_animIdx = (m_animIdx + 1) % m_numFrames;
			m_animTimer = 0;
		}
	}


	if (m_shouldDraw)
	{
		int midX = (m_x + m_w) / 2;
		int midY = (m_y + m_h) / 2;

		float x, y, w = m_w * m_scale, h = m_h * m_scale;
		x = m_x - ((w - m_w) * 0.5f);
		y = m_y - ((h - m_h) * 0.5f);

		Renderer::Get()->Render(m_imageIDs[m_animIdx], x, y, w, h);
	}
}

bool Object::IsOverlapping(const Object& other)
{
	if (!m_shouldCollide || !other.GetShouldCollide())
	{
		return false;
	}
	int oMinX, oMinY, oMaxX, oMaxY, w, h;
	other.GetDimensions(oMinX, oMinY, w, h);
	oMaxX = oMinX + w;
	oMaxY = oMinY + h;

	int minX = m_x, maxX = m_x + m_w, minY = m_y, maxY = m_y + m_h;

	if (minX > oMaxX || oMinX > maxX)
	{
		return false;
	}
	if (minY > oMaxY || oMinY > maxY)
	{
		return false;
	}

	return true;
}


