#include "RF-Agent.h"

RfAgent::RfAgent()
{
	srand(time(NULL));
}

int RfAgent::getMove(const std::vector<double>& gameStat)
{
	int move;
	if (checkLoosing(gameStat, move))
		return move;
	else if (checkWin(gameStat, move))
		return move;
	else
	{
		randomMove(gameStat, move);
		return move;
	}
}

bool RfAgent::checkLoosing(const std::vector<double>& gameStat, int& move)
{
	if (gameStat[0] == 0.0 && (
		(gameStat[1] == 2.0 && gameStat[2] == 2.0) ||
		(gameStat[4] == 2.0 && gameStat[8] == 2.0) ||
		(gameStat[3] == 2.0 && gameStat[6] == 2.0)))
	{
		move = 0;
		return true;
	}

	else if (gameStat[1] == 0.0 && (
		(gameStat[0] == 2.0 && gameStat[2] == 2.0) ||
		(gameStat[4] == 2.0 && gameStat[7] == 2.0)))
	{
		move = 1;
		return true;
	}

	else if (gameStat[2] == 0.0 && (
		(gameStat[1] == 2.0 && gameStat[0] == 2.0) ||
		(gameStat[5] == 2.0 && gameStat[8] == 2.0) ||
		(gameStat[4] == 2.0 && gameStat[6] == 2.0)))
	{
		move = 2;
		return true;
	}

	else if (gameStat[3] == 0.0 && (
		(gameStat[0] == 2.0 && gameStat[6] == 2.0) ||
		(gameStat[4] == 2.0 && gameStat[5] == 2.0)))
	{
		move = 3;
		return true;
	}

	else if (gameStat[4] == 0.0 && (
		(gameStat[1] == 2.0 && gameStat[7] == 2.0) ||
		(gameStat[3] == 2.0 && gameStat[5] == 2.0) ||
		(gameStat[2] == 2.0 && gameStat[6] == 2.0) ||
		(gameStat[0] == 2.0 && gameStat[8] == 2.0)))
	{
		move = 4;
		return true;
	}

	else if (gameStat[5] == 0.0 && (
		(gameStat[3] == 2.0 && gameStat[4] == 2.0) ||
		(gameStat[2] == 2.0 && gameStat[8] == 2.0)))
	{
		move = 5;
		return true;
	}

	else if (gameStat[6] == 0.0 && (
		(gameStat[7] == 2.0 && gameStat[8] == 2.0) ||
		(gameStat[4] == 2.0 && gameStat[2] == 2.0) ||
		(gameStat[3] == 2.0 && gameStat[0] == 2.0)))
	{
		move = 6;
		return true;
	}

	else if (gameStat[7] == 0.0 && (
		(gameStat[1] == 2.0 && gameStat[4] == 2.0) ||
		(gameStat[6] == 2.0 && gameStat[8] == 2.0)))
	{
		move = 7;
		return true;
	}

	else if (gameStat[8] == 0.0 && (
		(gameStat[7] == 2.0 && gameStat[6] == 2.0) ||
		(gameStat[4] == 2.0 && gameStat[0] == 2.0) ||
		(gameStat[5] == 2.0 && gameStat[2] == 2.0)))
	{
		move = 8;
		return true;
	}

	else
		return false;
}

bool RfAgent::checkWin(const std::vector<double>& gameStat, int& move)
{
	if (gameStat[0] == 0.0 && (
		(gameStat[1] == 1.0 && gameStat[2] == 1.0) ||
		(gameStat[4] == 1.0 && gameStat[8] == 1.0) ||
		(gameStat[3] == 1.0 && gameStat[6] == 1.0)))
	{
		move = 0;
		return true;
	}

	else if (gameStat[1] == 0.0 && (
		(gameStat[0] == 1.0 && gameStat[2] == 1.0) ||
		(gameStat[4] == 1.0 && gameStat[7] == 1.0)))
	{
		move = 1;
		return true;
	}

	else if (gameStat[2] == 0.0 && (
		(gameStat[1] == 1.0 && gameStat[0] == 1.0) ||
		(gameStat[5] == 1.0 && gameStat[8] == 1.0) ||
		(gameStat[4] == 1.0 && gameStat[6] == 1.0)))
	{
		move = 2;
		return true;
	}

	else if (gameStat[3] == 0.0 && (
		(gameStat[0] == 1.0 && gameStat[6] == 1.0) ||
		(gameStat[4] == 1.0 && gameStat[5] == 1.0)))
	{
		move = 3;
		return true;
	}

	else if (gameStat[4] == 0.0 && (
		(gameStat[1] == 1.0 && gameStat[7] == 1.0) ||
		(gameStat[3] == 1.0 && gameStat[5] == 1.0) ||
		(gameStat[2] == 1.0 && gameStat[6] == 1.0) ||
		(gameStat[0] == 1.0 && gameStat[8] == 1.0)))
	{
		move = 4;
		return true;
	}

	else if (gameStat[5] == 0.0 && (
		(gameStat[3] == 1.0 && gameStat[4] == 1.0) ||
		(gameStat[2] == 1.0 && gameStat[8] == 1.0)))
	{
		move = 5;
		return true;
	}

	else if (gameStat[6] == 0.0 && (
		(gameStat[7] == 1.0 && gameStat[8] == 1.0) ||
		(gameStat[4] == 1.0 && gameStat[2] == 1.0) ||
		(gameStat[3] == 1.0 && gameStat[0] == 1.0)))
	{
		move = 6;
		return true;
	}

	else if (gameStat[7] == 0.0 && (
		(gameStat[1] == 1.0 && gameStat[4] == 1.0) ||
		(gameStat[6] == 1.0 && gameStat[8] == 1.0)))
	{
		move = 7;
		return true;
	}

	else if (gameStat[8] == 0.0 && (
		(gameStat[7] == 1.0 && gameStat[6] == 1.0) ||
		(gameStat[4] == 1.0 && gameStat[0] == 1.0) ||
		(gameStat[5] == 1.0 && gameStat[2] == 1.0)))
	{
		move = 8;
		return true;
	}

	else
		return false;
}

void RfAgent::randomMove(const std::vector<double>& gameStat, int& move)
{
	std::vector<int> possibleMoves;

	for (int i = 0; i < gameStat.size(); i++)
	{
		if (gameStat[i] == 0.0)
			possibleMoves.push_back(i);
	}
	move = possibleMoves[rand() % possibleMoves.size()];
}