#include "Label.h"

Label::Label(TTF_Font* font, SDL_Color color)
{
	this->font = font;
	this->color = color;
}

void Label::Draw(SDL_Renderer* renderer)
{
	if (UpdateFont)
	{
		BakeText(renderer);
		UpdateFont = false;
	}
	
	SDL_RenderCopy(renderer, font_texture, NULL, &rect);
}

void Label::Update(float deltaTime)
{
	
}

void Label::EventUpdate(SDL_Event* event)
{
	
}

void Label::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Label::SetSize(int w, int h)
{
	rect.w = w;
}

void Label::SetText(std::string text)
{
	// Same text, no need to re-bake
	if (text == this->text) { return; }

	// Queue font update
	UpdateFont = true;

	this->text = text;
}

std::string Label::GetText()
{
	return text;
}

void Label::BakeText(SDL_Renderer* renderer)
{
	// Delete old texture
	SDL_DestroyTexture(this->font_texture);

	SDL_Surface* surface = TTF_RenderText_Solid_Wrapped(font, text.c_str(), color, ClipWidth);

	if (surface == NULL)
	{
		printf("Failed to bake text: %s", TTF_GetError());
		return;
	}

	this->rect.h = surface->h;
	this->rect.w = surface->w;

	this->font_texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
}
