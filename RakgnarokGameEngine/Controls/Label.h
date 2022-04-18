#pragma once
#include <SDL_ttf.h>
#include "Control.h"
#include <string>

class Label : public Control
{
private:
	void BakeText(SDL_Renderer* renderer);

	SDL_Color color;
	SDL_Texture *font_texture;
	TTF_Font *font;
	std::string text;
	bool UpdateFont = true;

public:
	int ClipWidth = 0;

	Label(TTF_Font* font, SDL_Color color);

	virtual void Draw(SDL_Renderer* renderer) override;

	virtual void Update(float deltaTime) override;

	virtual void EventUpdate(SDL_Event* event) override;

	virtual void SetPosition(int x, int y) override;

	virtual void SetSize(int w, int h) override;
	
	void SetText(std::string text);
	
	std::string GetText();
};