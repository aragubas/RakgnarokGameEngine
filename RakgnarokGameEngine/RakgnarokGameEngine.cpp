#include "RakgnarokGameEngine.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <format>
#include "Scenes/DeltatimeTest.h"
#include "Utils/String.h"

// Initialize pointer
RakgnarokGameEngine* RakgnarokGameEngine::rak_instance = 0;

RakgnarokGameEngine* RakgnarokGameEngine::GetInstance()
{
    if (!rak_instance)
    {
        rak_instance = new RakgnarokGameEngine();
    }

    return rak_instance;
}

void RakgnarokGameEngine::ReadConfigFile()
{
	// Read settings file
	std::string path = "Data/settings.rak";
	std::fstream fileStream;

	fileStream.open(path, std::ios::in);

	if (fileStream.is_open())
	{
		std::string line = "";

		// Read all lines of configuration file
		while (std::getline(fileStream, line))
		{
			// Skip empty lines
			if (line.length() < 4) { continue; }

			// Skip commented line
			if (line.rfind("//", 0) == 0) { continue; }


			// Get the key
			int firstTokenLength = line.find(":");
			std::string key = line.substr(0, firstTokenLength);
			std::string untrimmed_value = line.substr(firstTokenLength + 1);
			std::string value = StringUtils::trim(untrimmed_value);

			// Graphics Settings
			if (key.starts_with("Graphics"))
			{
				int firstTokenLength = key.find(".");
				std::string untrimmed_graphicsKey = key.substr(firstTokenLength + 1);
				std::string graphicsKey = StringUtils::trim(untrimmed_graphicsKey);

				// VSync setting
				if (graphicsKey == "Vsync")
				{
					graphics_vsync = value == "true";
				}

				// Hardware Acceleration setting
				if (graphicsKey == "HardwareAcceleration")
				{
					graphics_hardware_accelerated = value == "true";
				}
			}

			// Sound Settings
			if (key.starts_with("Sound"))
			{
				int firstTokenLength = key.find(".");
				std::string untrimmed_soundKey = key.substr(firstTokenLength + 1);
				std::string soundKey = StringUtils::trim(untrimmed_soundKey);

				// Sound Volume setting
				if (soundKey == "Enabled")
				{
					sound_enabled = value == "true";
				}
			}

			// Debug Settings
			if (key.starts_with("Debug"))
			{
				int firstTokenLength = key.find(".");
				std::string untrimmed_graphicsKey = key.substr(firstTokenLength + 1);
				std::string graphicsKey = StringUtils::trim(untrimmed_graphicsKey);

				// RendererFlags Debug
				if (graphicsKey == "RendererFlags")
				{
					debug_renderer_flags = value == "true";
				}

				// Set the log level
				if (graphicsKey == "LogLevel")
				{
					// strtol converts the first digits of a string to a long, and returns the rest of string in the second parameter
					// We can check if the string pointer is null to see if the value is actually a number

					char* converted_value;
					long val = strtol(value.c_str(), &converted_value, 10);

					if (*converted_value == NULL)
					{
						std::cout << (int)val << std::endl;
						log->SetLogLevel((int)val);
					}
					
				}
			}


		}
	}
	else
	{
		std::cout << "RakEngine::ReadConfigFile ; Could not open configuration file \"settings.rak\" located in Data folder." << std::endl;
	}

}

int RakgnarokGameEngine::Initialize()
{
	// Initialize spaghetti log
	this->log = SpaghettiLog::GetInstance();

	// Set switches, read config file!
	ReadConfigFile();

	// Initialize SDL main
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("RakEngine::Initialize ; SDL could not be initialized. %s\n", SDL_GetError());
		return -1;
	}
	
	// Initialize SDL_ttf
	if (TTF_Init() < 0)
	{
		printf("RakEngine::Initialize ; SDL_ttf could not be initialized. %s\n", TTF_GetError());
		return -1;
	}

	// Initialize SDL_image
	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		printf("RakEngine::Initialize ; SDL_image could not be initialized. %s\n", IMG_GetError());
		return -1;
	}

	// Initializa SDL_mixer
	if (sound_enabled)
	{
		// Initialize SDL_mixer with OGG file format support
		if (Mix_Init(MIX_INIT_OGG) < 0)
		{
			printf("RakEngine::Initialize ; SDL_mixer could not be initialized. %s\n", Mix_GetError());
			return -1;
		}
		
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("RakEngine::Initialize ; Error while opening audio stream. %s\n", Mix_GetError());
			return -1;
		}
	}
	else
	{
		printf("RakEngine::Initialize ; Audio subsystem is disabled.\n");
	}
	
	// Create window
	window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created. %s\n", SDL_GetError());
		return -1;
	}
	
	// Create renderer
	Uint32 flags = (graphics_hardware_accelerated ? SDL_RENDERER_ACCELERATED : 0) | (graphics_vsync ? SDL_RENDERER_PRESENTVSYNC : 0);
	
	renderer = SDL_CreateRenderer(window, -1, flags);
	if (renderer == NULL)
	{
		printf("Renderer could not be created. %s\n", SDL_GetError());
		return -1;
	}

	if (debug_renderer_flags)
	{
		std::string flags_report = "RakDebug::RendererFlags";
		
		flags_report += "\n  HardwareAcceleration: ";
		if (flags & SDL_RENDERER_ACCELERATED) { flags_report += "enabled"; } else { flags_report += "disabled"; }
		
		flags_report += "\n  Vsync: ";
		if (flags & SDL_RENDERER_PRESENTVSYNC) { flags_report += "enabled"; } else { flags_report += "disabled"; }

		std::cout << flags_report << std::endl;
	}

	// Set the renderer's draw color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Load all assets
	assets = Assets::GetInstance();
	assets->LoadTextures(renderer);

	// Set scene to Empty Scene
	SetScene(new EmptyScene());

	return 0;
}

void RakgnarokGameEngine::EventUpdate()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			Exit();
			return;
		}

		// Updates event of current scene
		current_scene->EventUpdate(event);
	}
}

void RakgnarokGameEngine::Update(float delta_time)
{
	current_scene->Update(delta_time);
}

void RakgnarokGameEngine::Draw()
{
	// Clear renderer
	SDL_RenderClear(renderer);
	
	// Draws current scene
	current_scene->Draw(renderer);

	// Update window and wait for vsync
	SDL_RenderPresent(renderer);
}

void RakgnarokGameEngine::Exit()
{
	IsRunning = false;
	
	assets->Unload();
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


void RakgnarokGameEngine::Run()
{
	float current_time = SDL_GetPerformanceCounter();
	//Uint64 last_time = 0;

	float last_time = 0;
	float delta_time = 0;
	
	while (IsRunning)
	{
		//start_time = SDL_GetPerformanceCounter();
		
		// Update SDL_Events
		EventUpdate();

		// Calculate delta time
		current_time = SDL_GetPerformanceCounter();
		delta_time = (current_time - last_time) * 1000 / (double)SDL_GetPerformanceFrequency() / 1000.f;

		//if (delta_time > 0.25) { delta_time = 0.25; }

		Update(delta_time);

		// Draw
		Draw();
		
		last_time = current_time;
	}

	Exit();
}

void RakgnarokGameEngine::SetScene(Scene* scene)
{
	// Calls unload function is current scene isn't null
	if (current_scene != NULL)
	{
		current_scene->Unload();
		
		delete current_scene;
	}
	
	// Change current scene
	current_scene = scene;
	scene->Initialize();

}
