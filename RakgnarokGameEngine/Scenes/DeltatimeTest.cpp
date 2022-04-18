#include "DeltatimeTest.h"
#include "../Assets.h"

void EmptyScene::Initialize()
{
	Assets* assets = Assets::GetInstance();

	label1 = new Label(assets->font_small, SDL_Color{ 255, 0, 255} );
	label1->SetText("Delta Time");

	label2 = new Label(assets->font_small, SDL_Color{ 0, 255, 255 });
	label2->SetText("No Delta Time");

	labelDelta = new Label(assets->font_small, SDL_Color{ 255, 0, 0 });
	labelDelta->SetPosition(5, 5);

	explanation_text = "This is a test scene for testing delta time\nThe magenta label has movement calculated with delta time\nThe cyan one doesn't\n\nPress 'q' and 'e' to change the framerate and 'r' to reset the positions.\nYou must disabled vsync in to be able to see the difference.";
}

void EmptyScene::Update(float deltaTime)
{
	if (X_addmode == 0) { label1->rect.x += speed * deltaTime; } else { label1->rect.x -= speed * deltaTime; }
	if (Y_addmode == 0) { label1->rect.y += speed * deltaTime; } else { label1->rect.y -= speed * deltaTime; }

	// Limit inside screen
	if (label1->rect.x + label1->rect.w >= 640) { label1->rect.x = 640 - label1->rect.w; };
	if (label1->rect.y + label1->rect.h >= 480) { label1->rect.y = 480 - label1->rect.h; };
	
	if (label1->rect.x < 0) { label1->rect.x = 0; };
	if (label1->rect.y < 0) { label1->rect.y = 0; };
	
	if (label1->rect.x <= 0) { X_addmode = 0; }
	if (label1->rect.y <= 0) { Y_addmode = 0; }

	if (label1->rect.x + label1->rect.w >= 640) { X_addmode = 1; }
	if (label1->rect.y + label1->rect.h >= 480) { Y_addmode = 1; }

	// Label 2 "No Delta Time"
	const float speed2 = 76.3f * 0.026214f;
	
	if (X2_addmode == 0) { label2->rect.x += speed2; }
	else { label2->rect.x -= speed2; }
	if (Y2_addmode == 0) { label2->rect.y += speed2; }
	else { label2->rect.y -= speed2; }

	// Limit inside screen
	if (label2->rect.x + label2->rect.w >= 640) { label2->rect.x = 640 - label2->rect.w; };
	if (label2->rect.y + label2->rect.h >= 480) { label2->rect.y = 480 - label2->rect.h; };

	if (label2->rect.x < 0) { label2->rect.x = 0; };
	if (label2->rect.y < 0) { label2->rect.y = 0; };

	if (label2->rect.x <= 0) { X2_addmode = 0; }
	if (label2->rect.y <= 0) { Y2_addmode = 0; }

	if (label2->rect.x + label2->rect.w >= 640) { X2_addmode = 1; }
	if (label2->rect.y + label2->rect.h >= 480) { Y2_addmode = 1; }

	labelDelta->SetText(std::to_string(deltaTime) + ", h:" + std::to_string(higher_delta) + ", framerate:" + std::to_string(framerate_lock) + "\n" + explanation_text);
	if (deltaTime > higher_delta) { higher_delta = deltaTime; }

	// Simulates lag, for testing
	SDL_Delay(1000 / framerate_lock);
}

void EmptyScene::EventUpdate(SDL_Event event)
{
	// Check if only the q key is pressed
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_e)
		{
			framerate_lock++;

			if (framerate_lock > 800) { framerate_lock = 800; }
		}

		if (event.key.keysym.sym == SDLK_q)
		{
			framerate_lock--;

			if (framerate_lock < 2) { framerate_lock = 2; }
		}

		if (event.key.keysym.sym == SDLK_r)
		{
			// Reset positions
			label1->rect.x = 0;
			label1->rect.y = 0;
			label2->rect.x = 0;
			label2->rect.y = 0;
			X_addmode = 0;
			Y_addmode = 0;
			X2_addmode = 0;
			Y2_addmode = 0;
		}

	}

	
	
}

void EmptyScene::Draw(SDL_Renderer* renderer)
{
	label1->Draw(renderer);
	label2->Draw(renderer);
	
	labelDelta->Draw(renderer);
}

void EmptyScene::Unload()
{
	
}

