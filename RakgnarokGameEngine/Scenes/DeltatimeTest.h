#pragma once
#include "../Scene.h"
#include "../Controls/Label.h"

class EmptyScene : public Scene
{
private:
	Label* label1;
	Label* label2;
	Label* labelDelta;
	int X_addmode;
	int Y_addmode;
	int X2_addmode;
	int Y2_addmode;
	std::string explanation_text;
	int framerate_lock = 60;
	float speed = 76.3;
	double higher_delta = 0;


public:
	// Inherited via Scene
	virtual void Update(float deltaTime) override;

	virtual void EventUpdate(SDL_Event event) override;

	virtual void Draw(SDL_Renderer* renderer) override;

	virtual void Unload() override;

	virtual void Initialize() override;


};