#pragma once

#ifdef _WIN32
	#ifdef BUTTONDLL_EXPORTS
		#define DLL_API __declspec(dllexport)
	#else
		#define DLL_API __declspec(dllimport)
	#endif
#else
	#define DLL_API
#endif

#include <iostream>
#include <fstream>
#include <SDL.h>

using namespace std;

class DLL_API Button
{
public:
	Button();
	~Button();
	//Full path to config file + path to image
	//CONFIG ORDER: IMG, RECT, MAXINCREASE, INCREASEPERFRAME
	void init(string pathToConfig, string pathToImage, SDL_Renderer* _renderer);
	void run(int mouseX, int mouseY, bool isPressed);
	void destroy();
	bool isPressed();

private:
	SDL_Renderer* m_renderer;

	int counter; 
	int maxIncrease;
	int increasePerFrame;
	
	bool m_isClicked;

	SDL_Texture* m_buttonTexture;
	SDL_Rect m_buttonRect;

	bool isMouseInBtn(int mouseX, int mouseY);
};