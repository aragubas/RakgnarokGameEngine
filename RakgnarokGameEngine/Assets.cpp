#include "Assets.h"
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include <SDL_image.h>

Assets* Assets::instance = 0;

Assets::Assets()
{
	font_small = TTF_OpenFont("Data/font/PressStart2P.ttf", 8);

	
}

void Assets::Unload()
{
	// Destroy loaded fonts
	TTF_CloseFont(font_small);
	
	// Destroy all textures loaded
	for(auto iter = textures.begin(); iter != textures.end(); ++iter)
	{
		SDL_DestroyTexture(iter->second);
	}
	
	textures.clear();
}

void Assets::LoadTextures(SDL_Renderer* renderer)
{
	// Load all textures in texture folder
	std::string path = "Data/texture/";
	
	for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(path))
	{
		// Skip non-files
		if (!entry.is_regular_file()) { continue; }
		std::filesystem::path filePath = entry.path();
		std::string fileName = filePath.filename().string();
		
		std::string relativePath = filePath.string().replace(0, path.length(), "./");

		// Insert texture into map
		SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.string().c_str());
		
		if (!texture)
		{
			printf("AssetManager::LoadTextures ; Failed to load texture: %s\n", IMG_GetError());
			continue;
		}
		
		textures.insert(std::make_pair(relativePath, texture));
	}
	
}

SDL_Texture* Assets::GetTexture(std::string texture_path)
{
	if (textures.find(texture_path) == textures.end())
	{
		throw std::runtime_error("AssetManager::GetTexture ; Texture not found: " + texture_path);
	}
	
	return textures[texture_path];
}

Assets* Assets::GetInstance()
{
	if (!instance)
	{
		instance = new Assets;
	}

	return instance;
}
