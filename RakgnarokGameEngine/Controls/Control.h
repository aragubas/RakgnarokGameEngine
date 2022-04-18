#pragma once
#include <SDL.h>

class Control
{	
public:
	SDL_Rect rect;

	Control() { };
	
	virtual void Draw(SDL_Renderer* renderer) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void EventUpdate(SDL_Event* event) = 0;
	virtual void SetPosition(int x, int y) = 0;
	virtual void SetSize(int w, int h) = 0;
};