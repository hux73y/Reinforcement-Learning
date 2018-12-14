#include "Game.h"

Game::Game() : window("Snake", sf::Vector2u(320, 320)), world(sf::Vector2u(320, 320)),agent(2,10),agent2(1,10)
{
	playerTurn = 1;
	round = 0;
	matches = 1;
}

Game::~Game() {}
//update function for human player
void Game::update()
{
	window.update(); // update window events
	if (world.checkIfWon())
	{
		/*
		if (world.getWinner() == 1)
			//agent.takeReward(0.0);
		else
			//agent.takeReward(1.0);
			*/
			clock.restart();
			while (clock.getElapsedTime().asSeconds() < 1.0f)
			{
			}
			matches++;
			reset();
	}
	else if (round == 9)
	{
		//agent.takeReward(0.5);
		clock.restart();
		while (clock.getElapsedTime().asSeconds() < 1.0f)
		{
		}
		matches++;
		reset();
	}
		
}
//inputfunction for human player
void Game::handleInput()
{
	int move = 0;
	if (playerTurn == 1)
	{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (world.playerInput(sf::Mouse::getPosition(*window.getRenderWindow())))
				{
					playerTurn = 2;
					round++;
				}
			}
	}
	else
	{
		move = agent.findBestMove(world.returnGameStatus(),round);
		world.agentInput(move,2);
		round++;
		playerTurn = 1;
	}
	
}

//input function to train agent
void Game::handleInputTrainAgent()
{
	int move = 0;
	if (playerTurn == 1)
	{
			move = agent2.findBestMoveTraining(world.returnGameStatus(), round);
			world.agentInput(move, 1);
			round++;
			playerTurn = 2;
	}
	else
	{	
		move = agent.findBestMoveTraining(world.returnGameStatus(), round);
		world.agentInput(move, 2);
		round++;
		playerTurn = 1;
	}
}
//update function to train agent
void Game::updateTrainAgent()
{
	window.update(); // update window events
	if (world.checkIfWon())
	{
		if (world.getWinner() == 1)
		{
			totalEsignal += agent.takeReward(0.1);
			agent2.takeReward(0.9);
		}
		else
		{
			agent2.takeReward(0.1);
			totalEsignal += agent.takeReward(0.9);
		}
		matches++;
		reset();
		std::cout << matches << "\n";
	}
	else if(round == 9)
	{
		totalEsignal += agent.takeReward(0.5);
		agent2.takeReward(0.5);
		matches++;
		reset();
		std::cout << matches << "\n";
	}	

	if (matches == 750000)
	{
		agent.saveRewardsInFile();
		char cc; std::cin >> cc;
	}
}
void Game::handleInputTrainAgentReflex()
{
	int move = 0;
	if (playerTurn == 1)
	{		
			move = reflexAgent.getMove(world.returnGameStatus());
			world.agentInput(move, 1);
			round++;
			playerTurn = 2;
		
	}
	else
	{	
		move = agent.findBestMove(world.returnGameStatus(), round);
		world.agentInput(move, 2);
		round++;
		playerTurn = 1;
	}
}
void Game::updateTrainAgentReflex()
{
	window.update(); // update window events
	if (world.checkIfWon())
	{

		if (world.getWinner() == 1)
		{
			agent.takeReward(0.1);
		}
		else
		{
			agent.takeReward(0.9);
		}
		matches++;
		reset();
		std::cout << matches << "\n";
	}
	else if(round == 9)
	{
		agent.takeReward(0.5);
		matches++;
		reset();
		std::cout << matches << "\n";
	}

}
void Game::render()
{
	window.beginDraw(); // clear
	world.render(*window.getRenderWindow());
	window.endDraw(); // display
}

Window* Game::getWindow()
{
	return &window;
}

sf::Time Game::getElapsed()
{
	return elapsed;
}
void Game::restartClock()
{
	elapsed += clock.restart();
}

void Game::reset()
{
	if (matches % 2 == 0)
		playerTurn = 1;
	else
		playerTurn = 2;
	round = 0;
	world.reset();
}

int Game::getMatches()
{
	return matches;
}

