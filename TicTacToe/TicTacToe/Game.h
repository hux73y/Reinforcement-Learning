#include "Window.h"
#include <iostream>
#include "World.h"
#include "RL-Agent.h"
#include "RF-Agent.h"
#include <stdlib.h>    
#include <time.h> 

class Game
{
public:
	Game();
	~Game();

	void handleInput();
	void handleInputTrainAgent();
	void updateTrainAgent();
	void update();
	void handleInputTrainAgentReflex();
	void updateTrainAgentReflex();
	void render();
	Window* getWindow();
	sf::Time getElapsed();
	void restartClock();
	void reset();
	int getMatches();

private:

	Window window;
	World world;
	RlAgent agent,agent2;
	RfAgent reflexAgent;
	sf::Clock clock;
	sf::Time elapsed;
	int playerTurn,round, matches,losses = 0;
	double totalEsignal = 0;

};

