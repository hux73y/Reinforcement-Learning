#include "World.h"

World::World(sf::Vector2u windSize)
{
	blockSize = 16;
	appleCount = 0;
	windowSize = windSize;
	respawnApple();
	apple.setFillColor(sf::Color::Red);
	apple.setRadius(blockSize / 2);

	for (int i = 0; i < 4; i++)
	{
		bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2))
			bounds[i].setSize(sf::Vector2f(windowSize.x, blockSize));
		else
			bounds[i].setSize(sf::Vector2f(blockSize, windowSize.y));

		if (i < 2)
			bounds[i].setPosition(0, 0);
		else
		{
			bounds[i].setOrigin(bounds[i].getSize());
			bounds[i].setPosition(sf::Vector2f(windowSize));
		}

	}
}

World::~World() {}

void World::respawnApple()
{
	int maxX = (windowSize.x / blockSize) - 2;
	int maxY = (windowSize.y / blockSize) - 2;
	item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	apple.setPosition(item.x * blockSize, item.y * blockSize);
}

std::vector<std::vector<double>> World::getPossiblePerceptions(Snake& player)
{
	std::vector<std::vector<double>> possiblePerceptions;
	snakeContainer lastPosition = player.getBody();
	HeadDirection lastHeadDirection = player.getHeadDirection();

	//moveLeft
	player.moveLeft();
	possiblePerceptions.push_back(getPerception(player));
	player.getBody() = lastPosition;
	player.setDirection(lastHeadDirection);
	//moveUp
	player.moveUp();
	possiblePerceptions.push_back(getPerception(player));
	player.getBody() = lastPosition;
	player.setDirection(lastHeadDirection);
	//moveRight
	player.moveRight();
	possiblePerceptions.push_back(getPerception(player));
	player.getBody() = lastPosition;
	player.setDirection(lastHeadDirection);

	return possiblePerceptions;
}

std::vector<double> World::getPerception(Snake & player)
{
	std::vector<double> perception;

	if (player.getPosition() == item)
	{
		perception.push_back(1.0);
		for (int i = 0; i < 7; i++)
			perception.push_back(0.0);
		return perception;
	}
	else if (player.checkColl() || player.getPosition().x <= 0 || player.getPosition().x >= ((windowSize.x / blockSize) - 1) || player.getPosition().y <= 0 || player.getPosition().y >= ((windowSize.y / blockSize) - 1))
	{
		perception.push_back(0.0);
		perception.push_back(1.0);
		for (int i = 0; i < 6; i++)
			perception.push_back(0.0);
		return perception;
	}

	perception.push_back(0.0);
	perception.push_back(0.0);
	player.setObstacles();
	if (player.getLeftObstacle())
		perception.push_back(1.0);
	else
		perception.push_back(0.0);

	if (player.getFrontObstacle())
		perception.push_back(1.0);
	else
		perception.push_back(0.0);

	if (player.getRightObstacle())
		perception.push_back(1.0);
	else
		perception.push_back(0.0);

	player.setFoodDirection(item);
	if (player.getFoodDirection() == Direction::Up)
	{
		perception.push_back(1.0);
		perception.push_back(0.0);
		perception.push_back(0.0);
	}
	else if (player.getFoodDirection() == Direction::Right)
	{
		perception.push_back(0.0);
		perception.push_back(1.0);
		perception.push_back(0.0);
	}
	
	else if (player.getFoodDirection() == Direction::Left)
	{
		perception.push_back(0.0);
		perception.push_back(0.0);
		perception.push_back(1.0);
	}
	else
	{
		perception.push_back(0.0);
		perception.push_back(0.0);
		perception.push_back(0.0);
	}
	return perception;
}


sf::Vector2i World::getItem()
{
	return item;
}

void World::update(Snake& player)
{
	if (player.getPosition() == item)
	{
		player.setRewardEat();
		player.extend();
		player.increaseScore();
		respawnApple();
		player.percep(item);
		appleCount = 0;
	}

	int gridSizeX = windowSize.x / blockSize;
	int gridSizeY = windowSize.y / blockSize;
	if (player.getPosition().x <= 0 || player.getPosition().y <= 0 || player.getPosition().x >= gridSizeX - 1 || player.getPosition().y >= gridSizeY - 1)
		player.lose();
	if (appleCount > 50)
	{
		respawnApple();
		appleCount = 0;
	}
	appleCount++;
}


void World::render(sf::RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
		window.draw(bounds[i]);

	window.draw(apple);
}

int World::getBlockSize() { return blockSize; }