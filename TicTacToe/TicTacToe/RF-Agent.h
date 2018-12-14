#include <vector>
#include <stdlib.h>    
#include <time.h>

class RfAgent
{
public:
	RfAgent();
	int getMove(const std::vector<double>& gameStat);
	bool checkLoosing(const std::vector<double>& gameStat, int& move);
	bool checkWin(const std::vector<double>& gameStat, int& move);
	void randomMove(const std::vector<double>& gameStat, int& move);
private:
	int lol;
};
