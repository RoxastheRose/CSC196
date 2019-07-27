#include "Game.h"
#include "..//core/Core.h"
#include "../external/core/include/core.h"
#include "..//framework/factory.h"
#include "..//math/math.h"
#include "..//renderer/renderer.h"

#include <iostream>
#include <assert.h>
#include <chrono>
#include <thread>
#include <random>

Game game;

bool Update(float dt)
{
	bool quit = false;
	if (Core::Input::IsPressed(Core::Input::KEY_ESCAPE))
	{
		quit = true;
	}

	game.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}


int main()
{
	game.StartUp();

	char window[] = "CSC195";
	Core::Init(window, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	Core::Shutdown();

	game.ShutDown();
	return 0;
};
