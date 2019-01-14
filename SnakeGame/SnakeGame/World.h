#include <SFML/Graphics.hpp>
#include "Snake.h"


class World
{
public:
	World(sf::Vector2u windSize);
	~World();

	int getBlockSize();

	void respawnApple();
	std::vector<std::vector<double>> getPossiblePerceptions(Snake& player);
	std::vector<double> getPerception(Snake& player);
	sf::Vector2i getItem();
	void update(Snake& player);
	void render(sf::RenderWindow& window);
private:
	int appleCount;
	sf::Vector2u windowSize;
	sf::Vector2i item;
	int blockSize;
	sf::CircleShape apple;
	sf::RectangleShape bounds[4];
};