#include "RL-Agent.h"

RlAgent::RlAgent(int c,int r)
{
	//setupForTraining(c,r);
	setupForPlay(c,r);
}

void RlAgent::setupForTraining(int c,int r)
{
	color = c;
	randomRate = r;
	srand(time(NULL));
	learnRate = 0.5;
}

void RlAgent::setupForPlay(int c, int r)
{
	loadRewardsFromFile();
	color = c;
	randomRate = r;
	learnRate = 0.5;
	srand(time(NULL));
}

/*return the next move of the agent,
first find the possible states for the next move,
then take the best of them, 
then set the reward of the last state in dependence of the current state
and return the next move*/
int RlAgent::findBestMove(const std::vector<double>& gameStat, int round)
{
	std::vector<double> afterState = greedyMove(gameStat);
	return findMove(gameStat,afterState);
}

int RlAgent::findBestMoveTraining(const std::vector<double>& gameStat, int round)
{
	
	if ((rand() % randomRate) == 0)
	{
		lastInput = randomMove(gameStat);
		return findMove(gameStat, lastInput);
	}
	
	if (round <= 1)
	{
		lastInput = greedyMove(gameStat);
		return findMove(gameStat, lastInput);
	}
	
	std::vector<double> afterState = greedyMove(gameStat);
	double errorSignal = learnRate * (nnetwork.getValue(afterState) - nnetwork.getValue(lastInput));
	int bla = nnetwork.getValue(lastInput);
	nnetwork.backProb(errorSignal, 1.0);
	lastInput = afterState;
	return findMove(gameStat, lastInput);
}
//convert the gamestat in other form to be able to process from the network
std::vector<double> RlAgent::convertGameStat(const std::vector<double>& gameStat)
{
	std::vector<double> newGameStat;
	for (int i = 0; i < gameStat.size(); i++)
	{
		if (gameStat[i] == (double) color)
		{
			newGameStat.push_back(1.0);
		}
		else if (gameStat[i] == 0.0)
		{
			newGameStat.push_back(0.0);
		}
		else
		{
			newGameStat.push_back(-1.0);
		}
	}
	return newGameStat;
}

std::vector<double> RlAgent::greedyMove(const std::vector<double>& gameStat)
{
	std::vector<std::vector<double>> networkInput;
	setNetworkInput(networkInput, gameStat);
	double max = nnetwork.getValue(networkInput[0]);
	int bestState = 0;
	for (int i = 1; i < networkInput.size(); i++)
	{
		if (max < nnetwork.getValue(networkInput[i]))
		{
			max = nnetwork.getValue(networkInput[i]);
			bestState = i;
		}
	}
	return networkInput[bestState];
}

void RlAgent::setNetworkInput(std::vector<std::vector<double>>& inputNetwork, const std::vector<double>& gameStat)
{
	for (int i = 0; i < gameStat.size(); i++)
	{	
		if(gameStat[i] == 0.0)
		{
			std::vector<double> input = convertGameStat(gameStat);
			input[i] = 1.0;
			inputNetwork.push_back(input);	
		}
	}
}
int RlAgent::findMove(const std::vector<double>& gameStat, const std::vector<double>& nextGameStat)
{
	for(int i = 0; i < gameStat.size(); i++)
	{
		if(gameStat[i] == 0.0 && nextGameStat[i] != 0.0)
			return i;
	}
}
std::vector<double> RlAgent::randomMove(const std::vector<double>& gameStat)
{
	std::vector<int> possibleMoves;
	std::vector<double> randomMovee = convertGameStat(gameStat);
	
	for(int i = 0; i < gameStat.size(); i++)
	{
		if(gameStat[i] == 0.0)
			possibleMoves.push_back(i);
	}
	randomMovee[possibleMoves[rand() % possibleMoves.size()]] = 1.0;  
	return randomMovee;
}
std::vector<double> RlAgent::makeMoveVector(double move)
{
	std::vector<double> moveVec;
	for (int i = 0; i < 9; i++)
	{
		if ((double)i == move)
			moveVec.push_back(1.0);
		else
			moveVec.push_back(0.0);
	}
	return moveVec;
}

double RlAgent::takeReward(double reward)
{
	
	double eSignal = learnRate * (reward - nnetwork.getValue(lastInput));
	nnetwork.backProb(eSignal, 1.0);

	if (eSignal > 0)
		return eSignal;
	else
		return (-1) * eSignal;
}

void RlAgent::printGameStat(const std::vector<double>& gameStat)
{
	std::cout << "gamestat: \n";
	for (int i = 0; i < gameStat.size(); i++)
			std::cout << gameStat[i] << ",";
	std::cout << "\n";
}
void RlAgent::printMoves(const std::vector<double>& moves)
{
	std::cout << "moves: \n";
	for (int i = 0; i < moves.size(); i++)
			std::cout << moves[i] << ",";
	std::cout << "\n";
}
void RlAgent::printLastInput()
{
	std::cout << "last Input: \n";
	for(int i = 0; i < lastInput.size(); i++)
	{
		if(i % 9 == 8)
		std::cout << "\n";
		else
		std::cout << lastInput[i] << ",";
	}
	std::cout << "\n";
}
void RlAgent::setLearnRate(double x)
{
	learnRate -= x;
}

std::vector<double> RlAgent::concatVectors(const std::vector<double>& a, const std::vector<double>& b)
{
	std::vector<double> cVector = a;
	for (int i = 0; i < b.size(); i++)
		cVector.push_back(b[i]);
	return cVector;
}

void RlAgent::saveRewardsInFile()
{
	std::ofstream myfile("Weights750k.txt");
	std::vector<std::vector<double>> inputMatrix = nnetwork.returnInputMatrix();
	std::vector<double> hiddenMatrix = nnetwork.returnHiddenMatrix();
	if (myfile.is_open())
	{
		for (int i = 0; i < inputMatrix.size(); i++)
			for(int j = 0; j < inputMatrix[i].size(); j++)
			{
				myfile << inputMatrix[i][j] << " , ";
			}
		for (int i = 0; i < inputMatrix.size(); i++)
			myfile << hiddenMatrix[i] << " , ";

		myfile.close();
	}
	else std::cout << "Unable to open file";
}
//load the learned rewards
void RlAgent::loadRewardsFromFile()
{
	std::ifstream myfile("Weights750k.txt");
	std::vector<std::vector<double>> inputMatrix = nnetwork.returnInputMatrix();
	std::vector<double> hiddenMatrix = nnetwork.returnHiddenMatrix();
	char sign;
	if (myfile.is_open())
	{
		for (int i = 0; i < inputMatrix.size(); i++)
			for (int j = 0; j < inputMatrix[i].size(); j++)
			{
				myfile >> inputMatrix[i][j];
				myfile >> sign;
			}
		for (int i = 0; i < inputMatrix.size(); i++)
		{
			myfile >> hiddenMatrix[i];
			myfile >> sign;
		}			
		nnetwork.setInputMatrix(inputMatrix);
		nnetwork.setHiddenMatrix(hiddenMatrix);
		myfile.close();
	}

	else std::cout << "Unable to open file";
}
