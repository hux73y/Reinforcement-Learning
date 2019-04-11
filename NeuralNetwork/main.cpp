#include "NeuralNetwork.h"
#include <iostream>

int main()
{
	NeuralNetwork nn = NeuralNetwork(2, 4, 2, 2);
	Vector input1 = { 1.0,1.0 };
	Vector desiredOutput = { 1.0,0.0 };
	nn.calculate(input1);
	Vector output = nn.getOutput();

	for (int i = 0; i < output.size(); i++)
		std::cout << "O" << i << " = " << output[i] << "\n";

	
	for (int i = 0; i < 1000000; i++)
	{
		nn.calculate(input1);
		nn.backpropagation(desiredOutput, 0.1);
	}

	for (int i = 0; i < 10000000; i++)
	{
		nn.calculate(input1);
		nn.backpropagation(desiredOutput, 0.01);
	}
	output = nn.getOutput();
	for (int i = 0; i < output.size(); i++)
		std::cout << "O" << i << " = " << output[i] << "\n";

	char cc; std::cin >> cc;
}