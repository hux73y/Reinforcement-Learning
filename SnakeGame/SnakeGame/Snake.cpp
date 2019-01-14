#include "Snake.h"

Snake::Snake(int blockSize, sf::Vector2i item, int x) : bound(x)
{
	size = blockSize;
	bodyRect.setSize(sf::Vector2f(size - 1, size - 1));
	reset(item);
}

Snake::~Snake() {}

void Snake::reset(sf::Vector2i item)
{
	snakeBody.clear();

	//snakeBody.push_back(SnakeSegment(5, 9));
	//snakeBody.push_back(SnakeSegment(5, 8));
	//snakeBody.push_back(SnakeSegment(5, 7));
	//snakeBody.push_back(SnakeSegment(5, 6));
	snakeBody.push_back(SnakeSegment(4, 4));

	setDirection(Direction::None); // start of still
	speed = 1;
	lives = 3;
	score = 0.0;
	steps = 0;
	firstRound = true;
	lost = false;
	hDir = HeadDirection::Up;
	srand(time(NULL));
}

void Snake::setDirection(Direction d)
{
	dir = d;
}

Direction Snake::getDirection()
{
	return dir;
}

Direction Snake::getPhysicalDirection()
{
	if (snakeBody.size() <= 1) return Direction::None;
	SnakeSegment& head = snakeBody[0];
	SnakeSegment& neck = snakeBody[1];

	if (head.position.x == neck.position.x)
		return (head.position.y > neck.position.y ? Direction::Down : Direction::Up);
	else if (head.position.y == neck.position.y)
		return (head.position.x > neck.position.x ? Direction::Right : Direction::Left);

	return Direction();
}

int Snake::getSpeed()
{
	return speed;
}

sf::Vector2i Snake::getPosition()
{
	return (!snakeBody.empty() ? snakeBody.front().position : sf::Vector2i(1, 1));
}

int Snake::getLives()
{
	return lives;
}

double Snake::getScore()
{
	return score;
}

void Snake::increaseScore()
{
	score += 0.08;
}

bool Snake::hasLost()
{
	return lost;
}

void Snake::setScore(double s)
{
	score = s;
}

void Snake::decreaseScore()
{
	score = score / 2.0;
}

void Snake::lose()
{
	lost = true;
}

void Snake::toggleLost()
{
	lost = !lost;
}

void Snake::extend()
{
	if (snakeBody.empty()) { return; }
	SnakeSegment& tail_head = snakeBody[snakeBody.size() - 1];

	if (snakeBody.size() > 1)
	{
		SnakeSegment& tail_bone = snakeBody[snakeBody.size() - 2];
		if (tail_head.position.x == tail_bone.position.x)
		{
			if (tail_head.position.y > tail_bone.position.y)
				snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			else
				snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		}
		else if (tail_head.position.y == tail_bone.position.y)
		{
			if (tail_head.position.x > tail_bone.position.x)
				snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			else
				snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}
	}
	else
	{
		if (dir == Direction::Up)
			snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		else if (dir == Direction::Down)
			snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		else if (dir == Direction::Left)
			snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		else if (dir == Direction::Right)
			snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
	}
}

void Snake::tick()
{
	if (snakeBody.empty()) { return; }
	if (dir == Direction::None) { return; }
	move();
	checkCollision();
}

void Snake::move()
{
	for (int i = snakeBody.size() - 1; i > 0; --i)
		snakeBody[i].position = snakeBody[i - 1].position;
	if (dir == Direction::Left)
	{
		moveLeft();
	}
	else if (dir == Direction::Up)
	{
		moveUp();
	}
	else if (dir == Direction::Right)
	{
		moveRight();
	}
}

void Snake::moveLeft()
{
	if (hDir == HeadDirection::Up)
	{
		--snakeBody[0].position.x;
		hDir = HeadDirection::Left;
	}
	else if (hDir == HeadDirection::Right)
	{
		--snakeBody[0].position.y;
		hDir = HeadDirection::Up;
	}
	else if (hDir == HeadDirection::Down)
	{
		++snakeBody[0].position.x;
		hDir = HeadDirection::Right;
	}
	else
	{
		++snakeBody[0].position.y;
		hDir = HeadDirection::Down;
	}
}

void Snake::moveRight()
{
	if (hDir == HeadDirection::Up)
	{
		++snakeBody[0].position.x;
		hDir = HeadDirection::Right;
	}
	else if (hDir == HeadDirection::Right)
	{
		++snakeBody[0].position.y;
		hDir = HeadDirection::Down;
	}
	else if (hDir == HeadDirection::Down)
	{
		--snakeBody[0].position.x;
		hDir = HeadDirection::Left;
	}
	else
	{
		--snakeBody[0].position.y;
		hDir = HeadDirection::Up;
	}
}

void Snake::moveUp()
{
	if (hDir == HeadDirection::Up)
	{
		--snakeBody[0].position.y;
		hDir = HeadDirection::Up;
	}
	else if (hDir == HeadDirection::Right)
	{
		++snakeBody[0].position.x;
		hDir = HeadDirection::Right;
	}
	else if (hDir == HeadDirection::Down)
	{
		++snakeBody[0].position.y;
		hDir = HeadDirection::Down;
	}
	else
	{
		--snakeBody[0].position.x;
		hDir = HeadDirection::Left;
	}
}


int Snake::getSteps()
{
	return steps;
}

bool Snake::checkIfObstacle(int x, int y)
{
	if (x < 1 || x >= (bound - 1) || y < 1 || y >= (bound - 1))
	{
		return true;
	}
	if (snakeBody.size() > 3)
	{
		for (auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr)
		{
			if (itr->position.x == x && itr->position.y == y)
			{
				return true;
			}
		}

	}
	return false;
}

void Snake::setObstacles()
{
	setLeftObstacle();
	setFrontObstacle();
	setRightObstacle();
}

void Snake::setLeftObstacle()
{
	if (hDir == HeadDirection::Up)
	{
		if (checkIfObstacle(snakeBody[0].position.x - 1, snakeBody[0].position.y))
			obstacleLeft = true;
		else
			obstacleLeft = false;
	}
	else if (hDir == HeadDirection::Right)
	{
		if (checkIfObstacle(snakeBody[0].position.x, snakeBody[0].position.y - 1))
			obstacleLeft = true;
		else
			obstacleLeft = false;
	}
	else if (hDir == HeadDirection::Down)
	{
		if (checkIfObstacle(snakeBody[0].position.x + 1, snakeBody[0].position.y))
			obstacleLeft = true;
		else
			obstacleLeft = false;
	}
	else if(hDir == HeadDirection::Left)
	{
		if (checkIfObstacle(snakeBody[0].position.x, snakeBody[0].position.y + 1))
			obstacleLeft = true;
		else
			obstacleLeft = false;
	}
}

void Snake::setRightObstacle()
{
	if (hDir == HeadDirection::Up)
	{
		if (checkIfObstacle(snakeBody[0].position.x + 1, snakeBody[0].position.y))
			obstacleRight = true;
		else
			obstacleRight = false;
	}
	else if (hDir == HeadDirection::Right)
	{
		if (checkIfObstacle(snakeBody[0].position.x, snakeBody[0].position.y + 1))
			obstacleRight = true;
		else
			obstacleRight = false;
	}
	else if (hDir == HeadDirection::Down)
	{
		if (checkIfObstacle(snakeBody[0].position.x - 1, snakeBody[0].position.y))
			obstacleRight = true;
		else
			obstacleRight = false;
	}
	else if (hDir == HeadDirection::Left)
	{
		if (checkIfObstacle(snakeBody[0].position.x, snakeBody[0].position.y - 1))
			obstacleRight = true;
		else
			obstacleRight = false;
	}
}

void Snake::setFrontObstacle()
{
	if (hDir == HeadDirection::Up)
	{
		if (checkIfObstacle(snakeBody[0].position.x, snakeBody[0].position.y - 1))
			obstacleFront = true;
		else
			obstacleFront = false;
	}
	else if (hDir == HeadDirection::Right)
	{
		if (checkIfObstacle(snakeBody[0].position.x + 1, snakeBody[0].position.y))
			obstacleFront = true;
		else
			obstacleFront = false;
	}
	else if (hDir == HeadDirection::Down)
	{
		if (checkIfObstacle(snakeBody[0].position.x, snakeBody[0].position.y + 1))
			obstacleFront = true;
		else
			obstacleFront = false;
	}
	else if (hDir == HeadDirection::Left)
	{
		if (checkIfObstacle(snakeBody[0].position.x - 1, snakeBody[0].position.y))
			obstacleFront = true;
		else
			obstacleFront = false;
	}
}

void Snake::setFoodDirection(sf::Vector2i& item)
{
	setBounds();

	if (hDir == HeadDirection::Up)
		checkFoodUp(item);
	else if (hDir == HeadDirection::Right)
		checkFoodRight(item);
	else if (hDir == HeadDirection::Down)
		checkFoodDown(item);
	else if (hDir == HeadDirection::Left)
		checkFoodLeft(item);
}

void Snake::setBounds()
{
	bounds.clear();
	setLeftBound();
	setRightBound();
	setLowerLeftBound();
	setLowerRightBound();
}

void Snake::setLeftBound()
{
	std::vector<SnakeSegment> leftBound;
	int x = snakeBody[0].position.x - 1;
	int y = snakeBody[0].position.y - 1;
	
	while (x >= 0 && y >= 0)
	{
		leftBound.push_back(SnakeSegment(x, y));
		x--;
		y--;
	}
	bounds.push_back(leftBound);
}

void Snake::setRightBound()
{
	std::vector<SnakeSegment> rightBound;
	int x = snakeBody[0].position.x + 1;
	int y = snakeBody[0].position.y - 1;
	while (x <= bound && y >= 0)
	{
		rightBound.push_back(SnakeSegment(x, y));
		x++;
		y--;
	}
	bounds.push_back(rightBound);
}

void Snake::setLowerLeftBound()
{
	std::vector<SnakeSegment> lowerLeftBound;
	int x = snakeBody[0].position.x - 1;
	int y = snakeBody[0].position.y + 1;
	while (x >= 0 && y <= bound)
	{
		lowerLeftBound.push_back(SnakeSegment(x, y));
		x--;
		y++;
	}
	bounds.push_back(lowerLeftBound);
}

void Snake::setLowerRightBound()
{
	std::vector<SnakeSegment> LowerRightBound;
	int x = snakeBody[0].position.x + 1;
	int y = snakeBody[0].position.y + 1;
	while (x <= bound && y <= bound)
	{
		LowerRightBound.push_back(SnakeSegment(x, y));
		x++;
		y++;
	}
	bounds.push_back(LowerRightBound);
}

bool Snake::checkFoodFrontIn(sf::Vector2i& item)
{
	for (int i = 0; i < bounds[0].size(); i++)
		if (item.x == bounds[0][i].position.x && item.y < bounds[0][i].position.y)
			return true;
	for (int i = 0; i < bounds[1].size(); i++)
		if (item.x == bounds[1][i].position.x && item.y < bounds[1][i].position.y)
			return true;
	if (item.x == snakeBody[0].position.x && item.y < snakeBody[0].position.y)
		return true;
	
	return false;
}

bool Snake::checkFoodFrontOn(sf::Vector2i & item)
{
	for (int i = 0; i < bounds[0].size(); i++)
		if (item.x == bounds[0][i].position.x && item.y <= bounds[0][i].position.y)
			return true;
	for (int i = 0; i < bounds[1].size(); i++)
		if (item.x == bounds[1][i].position.x && item.y <= bounds[1][i].position.y)
			return true;
	if (item.x == snakeBody[0].position.x && item.y < snakeBody[0].position.y)
		return true;

	return false;
}

bool Snake::checkFoodRightIn(sf::Vector2i & item)
{
	for (int i = 0; i < bounds[1].size(); i++)
		if (item.x > bounds[1][i].position.x && item.y == bounds[1][i].position.y)
			return true;
	for (int i = 0; i < bounds[3].size(); i++)
		if (item.x > bounds[3][i].position.x && item.y == bounds[3][i].position.y)
			return true;
	if (item.x > snakeBody[0].position.x && item.y == snakeBody[0].position.y)
		return true;

	return false;
}

bool Snake::checkFoodRightOn(sf::Vector2i & item)
{
	for (int i = 0; i < bounds[1].size(); i++)
		if (item.x >= bounds[1][i].position.x && item.y == bounds[1][i].position.y)
			return true;
	for (int i = 0; i < bounds[3].size(); i++)
		if (item.x >= bounds[3][i].position.x && item.y == bounds[3][i].position.y)
			return true;
	if (item.x > snakeBody[0].position.x && item.y == snakeBody[0].position.y)
		return true;

	return false;
}

bool Snake::checkFoodDownIn(sf::Vector2i & item)
{
	for (int i = 0; i < bounds[2].size(); i++)
		if (item.x == bounds[2][i].position.x && item.y > bounds[2][i].position.y)
			return true;
	for (int i = 0; i < bounds[3].size(); i++)
		if (item.x == bounds[3][i].position.x && item.y > bounds[3][i].position.y)
			return true;
	if (item.x == snakeBody[0].position.x && item.y > snakeBody[0].position.y)
		return true;

	return false;
}

bool Snake::checkFoodDownOn(sf::Vector2i & item)
{
	for (int i = 0; i < bounds[2].size(); i++)
		if (item.x == bounds[2][i].position.x && item.y >= bounds[2][i].position.y)
			return true;
	for (int i = 0; i < bounds[3].size(); i++)
		if (item.x == bounds[3][i].position.x && item.y >= bounds[3][i].position.y)
			return true;
	if (item.x == snakeBody[0].position.x && item.y > snakeBody[0].position.y)
		return true;

	return false;
}

bool Snake::checkFoodLeftIn(sf::Vector2i & item)
{
	for (int i = 0; i < bounds[0].size(); i++)
		if (item.x < bounds[0][i].position.x && item.y == bounds[0][i].position.y)
			return true;
	for (int i = 0; i < bounds[2].size(); i++)
		if (item.x < bounds[2][i].position.x && item.y == bounds[2][i].position.y)
			return true;
	if (item.x < snakeBody[0].position.x && item.y == snakeBody[0].position.y)
		return true;

	return false;
}

bool Snake::checkFoodLeftOn(sf::Vector2i & item)
{
	for (int i = 0; i < bounds[0].size(); i++)
		if (item.x <= bounds[0][i].position.x && item.y == bounds[0][i].position.y)
			return true;
	for (int i = 0; i < bounds[2].size(); i++)
		if (item.x <= bounds[2][i].position.x && item.y == bounds[2][i].position.y)
			return true;
	if (item.x < snakeBody[0].position.x && item.y == snakeBody[0].position.y)
		return true;

	return false;
}

void Snake::checkFoodUp(sf::Vector2i & item)
{
	if (checkFoodFrontOn(item))
		foodDir = Direction::Up;
	else if (checkFoodRightIn(item))
		foodDir = Direction::Right;
	else if (checkFoodLeftIn(item))
		foodDir = Direction::Left;
	else if (checkFoodDownOn(item))
		foodDir = Direction::Down;
}

void Snake::checkFoodRight(sf::Vector2i & item)
{
	if (checkFoodRightOn(item))
		foodDir = Direction::Up;
	else if (checkFoodDownIn(item))
		foodDir = Direction::Right;
	else if (checkFoodFrontIn(item))
		foodDir = Direction::Left;
	else if (checkFoodLeftOn(item))
		foodDir = Direction::Down;
}

void Snake::checkFoodDown(sf::Vector2i & item)
{
	if (checkFoodDownOn(item))
		foodDir = Direction::Up;
	else if (checkFoodLeftIn(item))
		foodDir = Direction::Right;
	else if (checkFoodRightIn(item))
		foodDir = Direction::Left;
	else if (checkFoodFrontOn(item))
		foodDir = Direction::Down;
}

void Snake::checkFoodLeft(sf::Vector2i & item)
{
	if (checkFoodLeftOn(item))
		foodDir = Direction::Up;
	else if (checkFoodFrontIn(item))
		foodDir = Direction::Right;
	else if (checkFoodDownIn(item))
		foodDir = Direction::Left;
	else if(checkFoodRightOn(item))
		foodDir = Direction::Down;
}

Direction Snake::getFoodDirection()
{
	return foodDir;
}


HeadDirection Snake::getHeadDirection()
{
	return hDir;
}

void Snake::setDirection(HeadDirection h)
{
	hDir = h;
}

snakeContainer & Snake::getBody()
{
	return snakeBody;
}

int Snake::findMoveTD(std::vector<std::vector<double>> perceptions)
{
	if (firstRound)
	{
		int nextPerception = greedyMove(perceptions);
		lastPerception = perceptions[nextPerception];
		firstRound = false;
		return nextPerception;

	}

	if ((rand() % 10) == 0)
	{
		int perceptionIndex = rand() % 3;
		lastPerception = perceptions[perceptionIndex];
		return perceptionIndex;
	}
	int nextPerception = greedyMove(perceptions);
	double errorSignal = 1 * ((nn.getValue(perceptions[nextPerception]) - nn.getValue(lastPerception)));
	nn.backProb(errorSignal, 0.1);
	lastPerception = perceptions[nextPerception];
	return nextPerception;
}

int Snake::findMove(std::vector<std::vector<double>> perceptions)
{
	
	std::cout << "\n\nValue left = " << nn.getValue(perceptions[0]) << "\n";
	for (int i = 0; i < perceptions[0].size(); i++)
		std::cout << perceptions[0][i] << " ";
	std::cout << "\n";
	std::cout << "Value up = " << nn.getValue(perceptions[1]) << "\n";
	for (int i = 0; i < perceptions[0].size(); i++)
		std::cout << perceptions[1][i] << " ";
	std::cout << "\n";

	std::cout << "Value right = " << nn.getValue(perceptions[2]) << "\n";
	for (int i = 0; i < perceptions[0].size(); i++)
		std::cout << perceptions[2][i] << " ";
	std::cout << "\n";

	int nextPerception = greedyMove(perceptions);
	return nextPerception;
}

int Snake::greedyMove(std::vector<std::vector<double>>& perceptions)
{
	int index = 0;
	double maxValue = nn.getValue(perceptions[index]);
	for (int i = 1; i < 3; i++)
	{
		if (maxValue < nn.getValue(perceptions[i]))
		{
			maxValue = nn.getValue(perceptions[i]);
			index = i;
		}
	}
	return index;
}

void Snake::setReward()
{
	double eSignal = 0.001 - nn.getValue(lastPerception);
	nn.backProb(eSignal, 0.1);
}

void Snake::setRewardTest()
{
	std::cout << " lost value" << nn.getValue(lastPerception) << "\n";
	for (int i = 0; i < lastPerception.size(); i++)
		std::cout << lastPerception[i];
	std::cout << "\n";
}

void Snake::setRewardEat()
{
	double eSignal = 0.9 - nn.getValue(lastPerception);
	nn.backProb(eSignal, 0.1);
	/*std::cout << "win value" << nn.getValue(lastPerception) << "\n";
	for (int i = 0; i < lastPerception.size(); i++)
	std::cout << lastPerception[i];
	std::cout << "\n";*/
}

void Snake::checkCollision()
{
	if (snakeBody.size() < 5) { return; }
	SnakeSegment& head = snakeBody.front();
	for (auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr)
	{
		if (itr->position == head.position)
		{
			lose();
			break;
		}
	}
}

void Snake::cut(int segment)
{
	for (int i = 0; i < segment; i++)
		snakeBody.pop_back();
	--lives;
	if (lives == 0) { lose(); return; }
}

void Snake::render(sf::RenderWindow& window)
{
	if (snakeBody.empty()) { return; }
	auto head = snakeBody.begin();
	bodyRect.setFillColor(sf::Color::Yellow);
	bodyRect.setPosition(head->position.x * size, head->position.y * size);
	window.draw(bodyRect);

	bodyRect.setFillColor(sf::Color::Green);
	for (auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); itr++)
	{
		bodyRect.setPosition(itr->position.x * size, itr->position.y * size);
		window.draw(bodyRect);
	}
}

void Snake::printPercep()
{
	for (int i = 0; i < lastPerception.size(); i++)
	{
		std::cout << lastPerception[i] << " , ";
	}
	std::cout << "\n\n";

}

bool Snake::checkColl()
{
	if (snakeBody.size() < 5) { return false; }
	SnakeSegment& head = snakeBody.front();
	for (auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr)
	{
		if (itr->position == head.position)
		{
			return true;
		}
	}
	return false;
}

bool Snake::getLeftObstacle()
{
	return obstacleLeft;
}

bool Snake::getRightObstacle()
{
	return obstacleRight;
}

bool Snake::getFrontObstacle()
{
	return obstacleFront;
}

void Snake::printfood()
{
	if (foodDir == Direction::Up)
		std::cout << "food Up\n";
	else if (foodDir == Direction::Down)
		std::cout << "food Down\n";
	else if (foodDir == Direction::Left)
		std::cout << "food Left\n";
	else if (foodDir == Direction::Right)
		std::cout << "food Right\n";

	/*if (hDir == HeadDirection::Up)
		std::cout << "Head Up\n";
	else if (hDir == HeadDirection::Right)
		std::cout << "Head Down\n";
	else if (hDir == HeadDirection::Left)
		std::cout << "Head Left\n";
	else if (hDir == HeadDirection::Down)
		std::cout << "Head Right\n";
	else
		std::cout << "Head none\n";*/

}

void Snake::prepare()
{
	std::vector<double>input1{0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
	std::vector<double>input2{0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0};
	std::vector<double>input3{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0};
	std::vector<double>input4{ 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
	std::vector<double>input5{ 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	std::vector<double>input6{ 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
	std::vector<double>input7{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
	std::vector<double>input8{ 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0 };
	std::vector<double>input9{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0 };
	std::vector<double>input10{ 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
	std::vector<double>input11{ 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
	std::vector<double>input12{ 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
	double d;
	for (int i = 0; i < 100000; i++)
	{
		d = nn.getValue(input1);
		nn.backProb(0.9 - d, 1.0);
		d = nn.getValue(input2);
		nn.backProb(0.9 - d, 1.0);
		d = nn.getValue(input3);
		nn.backProb(0.9 - d, 1.0);
		d = nn.getValue(input4);
		nn.backProb(0.4 - d, 1.0);
		d = nn.getValue(input5);
		nn.backProb(0.4 - d, 1.0);
		d = nn.getValue(input6);
		nn.backProb(0.4 - d, 1.0);
		d = nn.getValue(input7);
		nn.backProb(0.4 - d, 1.0);
		d = nn.getValue(input8);
		nn.backProb(0.4 - d, 1.0);
		d = nn.getValue(input9);
		d = nn.getValue(input10);
		nn.backProb(0.1 - d, 1.0);
		d = nn.getValue(input11);
		nn.backProb(0.1 - d, 1.0);
		d = nn.getValue(input12);
		nn.backProb(0.1 - d, 1.0);
		std::cout << i << "\n";
	}
	std::cout << "input1 value = " << nn.getValue(input1) << "\n";
	std::cout << "input2 value = " << nn.getValue(input2) << "\n";
	std::cout << "input3 value = " << nn.getValue(input3) << "\n";
	std::cout << "input4 value = " << nn.getValue(input4) << "\n";
	std::cout << "input5 value = " << nn.getValue(input5) << "\n";
	std::cout << "input6 value = " << nn.getValue(input6) << "\n";
	std::cout << "input7 value = " << nn.getValue(input7) << "\n";
	std::cout << "input8 value = " << nn.getValue(input8) << "\n";
	std::cout << "input9 value = " << nn.getValue(input9) << "\n";
	std::cout << "input10 value = " << nn.getValue(input10) << "\n";
	std::cout << "input11 value = " << nn.getValue(input11) << "\n";
	std::cout << "input12 value = " << nn.getValue(input12) << "\n";
}

void Snake::percep(sf::Vector2i& item)
{
	lastPerception.clear();
	
	lastPerception.push_back(0.0);
	lastPerception.push_back(0.0);

	setObstacles();
	if (obstacleLeft)
		lastPerception.push_back(1.0);
	else
		lastPerception.push_back(0.0);

	if (obstacleFront)
		lastPerception.push_back(1.0);
	else
		lastPerception.push_back(0.0);

	if (obstacleRight)
		lastPerception.push_back(1.0);
	else
		lastPerception.push_back(0.0);

	setFoodDirection(item);
	if (foodDir == Direction::Up)
	{
		lastPerception.push_back(1.0);
		lastPerception.push_back(0.0);
		lastPerception.push_back(0.0);
	}
	else if (foodDir == Direction::Right)
	{
		lastPerception.push_back(0.0);
		lastPerception.push_back(1.0);
		lastPerception.push_back(0.0);
	}
	else if (foodDir == Direction::Left)
	{
		lastPerception.push_back(0.0);
		lastPerception.push_back(0.0);
		lastPerception.push_back(1.0);
	}
	else
	{
		lastPerception.push_back(0.0);
		lastPerception.push_back(0.0);
		lastPerception.push_back(0.0);
	}
}
