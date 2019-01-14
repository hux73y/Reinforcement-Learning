#include "Game.h"

Game::Game() : window("Snake", sf::Vector2u(160,160)), snake(world.getBlockSize(),world.getItem(),10), world(sf::Vector2u(160, 160))
{
	//textbox.setup(5, 14, 350, sf::Vector2f(255, 0));
	//textbox.add("seed random number generator with: " + std::to_string(time(NULL)));
	
	matches = 0;
}

Game::~Game() {}

void Game::update()
{
	window.update(); // update window events
	if (matches > 15000)
	{
		float timestep = 1.0f / snake.getSpeed();
		if (elapsed.asSeconds() >= timestep)
		{
			handleInputTest();
			snake.tick();
			world.update(snake);
			elapsed -= sf::seconds(timestep);
			if (snake.hasLost())
			{
				//textbox.add("Game Over! Score: " + std::to_string(snake.getScore()));
				snake.reset(world.getItem());
				matches++;
			}
		}
	}
	else
	{
		
			handleInput();
			snake.tick();
			world.update(snake);
			if (snake.hasLost())
			{
				snake.setReward();
				snake.reset(world.getItem());
				matches++;
				std::cout << matches << "\n";
			}
	}
}

void Game::handleInput()
{
	
	
	int moveIndex = snake.findMoveTD(world.getPossiblePerceptions(snake));
	if (moveIndex == 0)
		snake.setDirection(Direction::Left);
	else if (moveIndex == 1)
		snake.setDirection(Direction::Up);
	else
		snake.setDirection(Direction::Right);
}

void Game::handleInputTest()
{
	int moveIndex = snake.findMove(world.getPossiblePerceptions(snake));
	if (moveIndex == 0)
		snake.setDirection(Direction::Left);
	else if (moveIndex == 1)
		snake.setDirection(Direction::Up);
	else
		snake.setDirection(Direction::Right);

}

void Game::render()
{
	window.beginDraw(); // clear
	world.render(*window.getRenderWindow());
	snake.render(*window.getRenderWindow());
	textbox.render(*window.getRenderWindow());
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


















