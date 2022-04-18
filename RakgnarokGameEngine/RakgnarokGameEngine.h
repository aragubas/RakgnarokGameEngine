#pragma once
#include <SDL.h>
#include "Assets.h"
#include "Scene.h"
#include "Utils/SpaghettiLog.h"

class RakgnarokGameEngine
{
	static RakgnarokGameEngine *rak_instance;
	
	RakgnarokGameEngine() { };

	Assets *assets = 0;
	SDL_Window *window = 0;
	SDL_Renderer *renderer = 0;
	SpaghettiLog *log = 0;
	bool IsRunning = true;

	void EventUpdate();
	void Update(float delta_time);
	void Draw();
	void Exit();
	void ReadConfigFile();
	

public:
	static RakgnarokGameEngine *GetInstance();
	Scene *current_scene;
	
	int Initialize();
	void Run();
	void SetScene(Scene* scene);

	// Graphics settings
	bool graphics_vsync = true;
	bool graphics_hardware_accelerated = true;

	// Sound Settings
	bool sound_enabled = true;

	// Debug settings
	bool debug_renderer_flags = false;
};