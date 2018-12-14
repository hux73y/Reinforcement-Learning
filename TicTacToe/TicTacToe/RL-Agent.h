#include <vector>
#include <iostream>
#include <stdlib.h>    
#include <time.h>
#include <fstream>
#include "NN.h"

class RlAgent
{
public:
	RlAgent(){}
	RlAgent(int c,int r);
	void setupForTraining(int c,int r);
	void setupForPlay(int c,int r);
	int findBestMove(const std::vector<double>& gameStat,int round);
	int findBestMoveTraining(const std::vector<double>& gameStat, int round);
	std::vector<double> convertGameStat(const std::vector<double>& gameStat);
	std::vector<double> greedyMove(const std::vector<double>& possibleStates);
	void setNetworkInput(std::vector<std::vector<double>>& input, const std::vector<double>& gameStat);
	int findMove(const std::vector<double>& gameStat, const std::vector<double>& nextGameStat);
	std::vector<double> randomMove(const std::vector<double>& gameStat);
	std::vector<double> makeMoveVector(double move);
	double takeReward(double reward);
	void saveRewardsInFile();
	void loadRewardsFromFile();
	void printGameStat(const std::vector<double>& gameStat);
	void printMoves(const std::vector<double>& moves);
	void printLastInput();
	void setLearnRate(double x);
	std::vector<double> concatVectors(const std::vector<double>& a, const std::vector<double>& b);
private:
	NNetwork nnetwork = NNetwork(9,18);
	std::vector<double> lastInput,nextInput;
	int color,randomRate;
	double learnRate;
};
