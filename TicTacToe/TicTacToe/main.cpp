#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;
	while (!game.getWindow()->isDone())
	{
		
			//gameloop
		//game.updateTrainAgent();
		//game.handleInputTrainAgent();
		//game.updateTrainAgentReflex();
		//game.handleInputTrainAgentReflex();
		game.update();
		game.handleInput();
		game.render();
	}
	return 0;
}
