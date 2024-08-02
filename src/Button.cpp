#include "Button.h"
#include "pch.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::init(string pathToConfig, string pathToImage, SDL_Renderer* _renderer)
{
	fstream stream;
	string tmp, Img;

	stream.open(pathToConfig);

	stream >> tmp >> Img;
	stream >> tmp >> m_buttonRect.x >> m_buttonRect.y >> m_buttonRect.w >> m_buttonRect.h ;
	stream >> tmp >> maxIncrease;
	stream >> tmp >> increasePerFrame;

	stream.close();

	counter = 0;
	m_isClicked = false;
	m_renderer = _renderer;

	SDL_Surface* loadingSurface = SDL_LoadBMP((pathToImage + Img).c_str());
	m_buttonTexture = SDL_CreateTextureFromSurface(m_renderer, loadingSurface);
	SDL_FreeSurface(loadingSurface);
}

void Button::run(int mouseX, int mouseY, bool isPressed)
{
	SDL_RenderCopy(m_renderer, m_buttonTexture, NULL, &m_buttonRect);

	m_isClicked = false;
	if (isMouseInBtn(mouseX, mouseY))
	{
		if (isPressed)
		{
			m_isClicked = true;
		}

		if (counter <= maxIncrease)
		{
			m_buttonRect.w += increasePerFrame * 2;
			m_buttonRect.h += increasePerFrame * 2;
			m_buttonRect.x -= increasePerFrame;
			m_buttonRect.y -= increasePerFrame;
			counter += increasePerFrame;
		}
	}
	else if (counter >= 0)
	{
		m_buttonRect.x += increasePerFrame;
		m_buttonRect.y += increasePerFrame;
		m_buttonRect.w -= increasePerFrame * 2;
		m_buttonRect.h -= increasePerFrame * 2;
		counter -= increasePerFrame;
	}
}

void Button::destroy()
{
	SDL_DestroyTexture(m_buttonTexture);
}

bool Button::isPressed()
{
	return m_isClicked;
}

bool Button::isMouseInBtn(int mouseX, int mouseY)
{
	if (mouseX >= m_buttonRect.x && mouseX <= m_buttonRect.x + m_buttonRect.w &&
		mouseY >= m_buttonRect.y && mouseY <= m_buttonRect.y + m_buttonRect.h)
	{
		return true;
	}

	return false;
}
