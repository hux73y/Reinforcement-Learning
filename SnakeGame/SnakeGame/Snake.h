#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>    
#include <time.h>
#include <fstream>
#include "NN.h"
#include "NeuralNetwork.h"

struct SnakeSegment
{
	SnakeSegment(int x, int y) : position(x, y) {}
	SnakeSegment (const SnakeSegment &s) { position = s.position;}
	sf::Vector2i position;
};

using snakeContainer = std::vector<SnakeSegment>;

enum class Direction { None, Down, Up, Left, Right };
enum class HeadDirection {Up = 1, Down = 2, Left = 3, Right = 4};

class Snake
{
public:
	Snake(int blockSize, sf::Vector2i item, int x);
	~Snake();

	//helper methods
	void setDirection(Direction d);
	Direction getDirection();
	Direction getPhysicalDirection();
	int getSpeed();
	sf::Vector2i getPosition();
	int getLives();
	double getScore();
	void increaseScore();
	bool hasLost();
	void setScore(double s);
	void decreaseScore();

	void lose(); //handle loosing here
	void toggleLost();

	void extend(); // grow the snake
	void reset(sf::Vector2i item); // reset to start position
	void move(); // movement method
	void moveLeft();
	void moveRight();
	void moveUp();
	int getSteps();
	bool checkIfObstacle(int x, int y);
	void setObstacles();
	void setLeftObstacle();
	void setRightObstacle();
	void setFrontObstacle();
	void setFoodDirection(sf::Vector2i& item);
	void setBounds();
	void setLeftBound();
	void setRightBound();
	void setLowerLeftBound();
	void setLowerRightBound();
	bool checkFoodFrontIn(sf::Vector2i& item);
	bool checkFoodFrontOn(sf::Vector2i& item);
	bool checkFoodRightIn(sf::Vector2i& item);
	bool checkFoodRightOn(sf::Vector2i& item);
	bool checkFoodDownIn(sf::Vector2i& item);
	bool checkFoodDownOn(sf::Vector2i& item);
	bool checkFoodLeftIn(sf::Vector2i& item);
	bool checkFoodLeftOn(sf::Vector2i& item);
	void checkFoodUp(sf::Vector2i& item);
	void checkFoodRight(sf::Vector2i& item);
	void checkFoodDown(sf::Vector2i& item);
	void checkFoodLeft(sf::Vector2i& item);
	Direction getFoodDirection();
	HeadDirection getHeadDirection();
	void setDirection(HeadDirection h);
	snakeContainer& getBody();
	int findMoveTD(std::vector<std::vector<double>> perceptions);
	int findMove(std::vector<std::vector<double>> perceptions);
	int greedyMove(std::vector<std::vector<double>>& perceptions);
	void setReward();
	void setRewardTest();
	void setRewardEat();
	void tick(); // update method
	void cut(int segment); // method for cutting
	void render(sf::RenderWindow& window);
	void printPercep();
	bool checkColl();
	bool getLeftObstacle();
	bool getRightObstacle();
	bool getFrontObstacle();
	void printfood();
	void prepare();
	void percep(sf::Vector2i& item);
private:
	void checkCollision(); // checking for collisions

	snakeContainer snakeBody; // vector container of snake segments
	int size; // size of the graphics
	int bound;
	Direction dir; // current direction
	HeadDirection hDir;
	Direction foodDir;
	bool obstacleLeft, obstacleFront, obstacleRight;
	std::vector<double> lastPerception;
	std::vector<std::vector<SnakeSegment>> bounds;
	bool firstRound;
	int speed;
	int lives;
	double score;
	bool lost;
	int steps;
	sf::RectangleShape bodyRect;
	NNetwork nnetwork = NNetwork(10, 20);
	NeuralNetwork nn = NeuralNetwork(8, 16, 2);
};