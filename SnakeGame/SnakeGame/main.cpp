#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;
	while (!game.getWindow()->isDone())
	{
		//gameloop
		//game.handleInput();
		game.update();
		game.render();
		game.restartClock();
	}
	return 0;
}