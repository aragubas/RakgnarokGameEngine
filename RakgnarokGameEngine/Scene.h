#pragma once
#include <SDL.h>

class Scene
{
public:
	Scene() { };
	
	virtual void Update(float deltaTime) = 0;
	virtual void EventUpdate(SDL_Event event) = 0;
	virtual void Draw(SDL_Renderer* renderer) = 0;
	virtual void Unload() = 0;
	virtual void Initialize() = 0;
	
};