#include <SFML/Graphics.hpp>
#include <iostream>
// element of the gameboard
struct Block
{
	Block(int x, int y) : posX(x), posY(y), status(0) {}
	Block(){}
	// status: information if the block is empty (value = 0) or if one of the player has taken it (value = 1 for player 1, value 2 for player 2)
	int posX, posY, status;
};

// class containing gameBoard
class World
{
public:
	World(sf::Vector2u windSize);
	~World();

	int getBlockSize();
	void initGameboard();
	void setCol(int c);
	void update();
	void render(sf::RenderWindow& window);
	int playerInput(sf::Vector2i pos);
	std::vector<double> returnGameStatus();
	std::vector<std::vector<double>> returnPossibleMoves();
	std::vector<double> getMoves();
	void agentInput(int in, int player);
	bool checkIfWon();
	bool checkIfWonNext(const std::vector<double>& nextMove,int player);
	bool checkIfDraw(const std::vector<double>& nextMove);
	void setWinnerFields();
	void setWinnerFieldsRewards();
	int getWinner();
	void reset();
	void printMoves(std::vector<std::vector<double>> possibleMoves);
private:
	std::vector<std::vector<Block>> gameBoard;
	std::vector<std::vector<double>> possibleStates;
	sf::Vector2u windowSize;
	int blockSize, winner;
	std::vector<int> wF,wFR;
	sf::RectangleShape rect;

};
