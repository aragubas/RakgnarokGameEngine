// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Assets.h"
#include "RakgnarokGameEngine.h"
#include <iostream>

int main()
{
	// Creates engine instance
	RakgnarokGameEngine* engine = RakgnarokGameEngine::GetInstance();	

	engine->Initialize();
	engine->Run();

	printf("Goodbye world!");
}
