#include "Window.h"
#include <iostream>
#include "World.h"
#include "Textbox.h"

class Game
{
public:
	Game();
	~Game();

	void handleInput();
	void handleInputTest();
	void update();
	void render();
	Window* getWindow();
	sf::Time getElapsed();
	void restartClock();

private:

	Window window;
	World world;
	Snake snake;
	Textbox textbox;

	sf::Clock clock;
	sf::Time elapsed;
	int matches;
};

