#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>

class Assets
{
	static Assets *instance;
	std::map<std::string, SDL_Texture*> textures;

	Assets();
	

public:
	static Assets *GetInstance();
	void Unload();
	void LoadTextures(SDL_Renderer* renderer);
	TTF_Font* font_small;

	SDL_Texture* GetTexture(std::string texture_path);

};