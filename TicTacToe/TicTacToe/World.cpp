#include "World.h"

World::World(sf::Vector2u windSize)
{
	blockSize = 100;
	windowSize = windSize;
	rect.setSize(sf::Vector2f(blockSize,blockSize));
	initGameboard();
	setWinnerFields();
	setWinnerFieldsRewards();
}

World::~World() {}


void World::update()
{
	
}

void World::render(sf::RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			rect.setPosition((gameBoard[i][j].posX * blockSize) + (10 * j) ,(gameBoard[i][j].posY * blockSize) + (10 * i));
			setCol(gameBoard[i][j].status);
			window.draw(rect);
		}
	}
}

int World::playerInput(sf::Vector2i pos)
{
	// check if player input is on a valid field
	for(int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			if ((pos.x >= ((gameBoard[i][j].posX * blockSize) + (10 * j))) && (pos.x <= (((gameBoard[i][j].posX + 1) * blockSize) + (10 * j))) &&
				(pos.y >= ((gameBoard[i][j].posY * blockSize) + (10 * i))) && (pos.y <= (((gameBoard[i][j].posY + 1 )* blockSize) + (10 * i))) && gameBoard[i][j].status == 0)
			{
				gameBoard[i][j].status = 1;
				return 1;
			}
		}
	return 0;
}

std::vector<double> World::returnGameStatus()
{
	std::vector<double> stat;
	for(int i = 0; i < 3; i ++)
		for (int j = 0; j < 3; j++)
			stat.push_back((double) gameBoard[i][j].status);

	return stat;
}

std::vector<std::vector<double>> World::returnPossibleMoves()
{

	return possibleStates;
}

std::vector<double> World::getMoves()
{

	std::vector<double> currentState = returnGameStatus();
	std::vector<double> moves;
	for (int i = 0; i < currentState.size(); i++)
		if (currentState[i] == 0.0)
			moves.push_back((double)i);

	return moves;
}

void World::agentInput(int in, int player)
{
	if (in == 0)
		gameBoard[0][0].status = player;
	else if (in == 1)
		gameBoard[0][1].status = player;
	else if (in == 2)
		gameBoard[0][2].status = player;
	else if (in == 3)
		gameBoard[1][0].status = player;
	else if (in == 4)
		gameBoard[1][1].status = player;
	else if (in == 5)
		gameBoard[1][2].status = player;
	else if (in == 6)
		gameBoard[2][0].status = player;
	else if (in == 7)
		gameBoard[2][1].status = player;
	else if (in == 8)
		gameBoard[2][2].status = player;
}

bool World::checkIfWon()
{
	for (int i = 0; i < wF.size(); i += 6)
	{
		if ((gameBoard[wF[i]][wF[i+1]].status == 1 && gameBoard[wF[i+2]][wF[i+3]].status == 1 && gameBoard[wF[i + 4]][wF[i + 5]].status == 1)
			|| (gameBoard[wF[i]][wF[i + 1]].status == 2 && gameBoard[wF[i + 2]][wF[i + 3]].status == 2 && gameBoard[wF[i + 4]][wF[i + 5]].status == 2))
		{
			if (gameBoard[wF[i]][wF[i + 1]].status == 1)
				winner = 1;
			else
				winner = 2;
			return true;
		}
	}
	return false;
}

bool World::checkIfWonNext(const std::vector<double>& nextMove, int player)
{
	for (int i = 0; i < wFR.size(); i += 3)
	{
		if (nextMove[wFR[i]] == (double) player && nextMove[wFR[i+1]] == (double)player && nextMove[wFR[i+2]] == (double)player)
		{
			return true;
		}
	}
	return false;
}

bool World::checkIfDraw(const std::vector<double>& nextMove)
{
	for (int i = 0; i < 9; i++)
	{
		if (nextMove[i] == 0)
			return false;
	}
	return true;
}

void World::setWinnerFields()
{
	wF = { 0,0,0,1,0,2,
		   1,0,1,1,1,2,
		   2,0,2,1,2,2,
		   0,0,1,0,2,0,
		   0,1,1,1,2,1,
		   0,2,1,2,2,2,
		   0,0,1,1,2,2,
		   2,0,1,1,0,2 };
}

void World::setWinnerFieldsRewards()
{
	wFR = { 0,1,2,
			3,4,5,
			6,7,8,
			0,3,6,
			1,4,7,
			2,5,8,
			0,4,8,
			6,4,2 };
}

int World::getWinner()
{
	return winner;
}

void World::reset()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			gameBoard[i][j].status = 0;
		}
	}
	winner = 0;
}

void World::printMoves(std::vector<std::vector<double>> possibleMoves)
{
	for (int i = 0; i < possibleMoves.size(); i++)
	{
		for (int j = 0; j < possibleMoves[i].size(); j++)
			std::cout << possibleMoves[i][j] << ",";
		std::cout << "\n";
	}
		
}

int World::getBlockSize() { return blockSize; }

void World::initGameboard()
{
	for (int i = 0; i < 3; i++)
	{
		std::vector<Block> v;
		for (int j = 0; j < 3; j++)
		{
			v.push_back(Block(j, i));
		}
		gameBoard.push_back(v);
	}
		
}

void World::setCol(int c)
{
	if (c == 1)
		rect.setFillColor(sf::Color::Green);
	else if (c == 2)
		rect.setFillColor(sf::Color::Red);
	else
		rect.setFillColor(sf::Color::White);
}
