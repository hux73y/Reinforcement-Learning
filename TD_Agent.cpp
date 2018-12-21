#include "TD_Agent.h"
using namespace Ai_Arena;

template <class State_T>
TD_Agent<State_T>::TD_Agent(std::shared_ptr<Environment<State_T>> enviroment)
	:
	Agent<State_T>::Agent(enviroment)
	// initialize State with first gamestate
{}
template <class State_T>
void TD_Agent<State_T>::evaluate_action()
{
	if (!Agent<State_T>::m_environment->is_final(Agent<State_T>::m_self_pointer))
	{
		const auto actual_state = Agent<State_T>::m_environment->actual_state(Agent<State_T>::m_self_pointer);
		auto reward = Agent<State_T>::m_environment->reward(Agent<State_T>::m_self_pointer, actual_state);

		if (reward != 0.0)
			findActionFinal();
		else
			findAction();
	}
	else
	{
		std::cout << "actor " << id() << " sleeping\n";
		sleep();
		//TODO
		//chould do things like save his learnig progress (if learning agent)
		// saveRewardsInFile()
	}

}
template<class State_T>
void TD_Agent<State_T>::set_up()
{
}

template<class State_T>
void TD_Agent<State_T>::findAction()
{
	std::vector<Action> possible_actions =
		Agent<State_T>::m_environment->possible_actions(
			Agent<State_T>::m_self_pointer);

	const auto actual_state = Agent<State_T>::m_environment->actual_state(Agent<State_T>::m_self_pointer);

	if ((rand() % 10) == 0)
	{
		Action next = possible_actions[Utility::random_int_ts(0, possible_actions.size() - 1)];
		auto states = Agent<State_T>::m_environment->assume_action(Agent<State_T>::m_self_pointer, actual_state, next);
		lastPerception = Agent<State_T>::m_environment->get_perception(Agent<State_T>::m_self_pointer, SEE_THE_WHOLE_STATE, states[0]);
		return;
	}

	set_action(nextAction(possible_actions));
	double errorSignal = learnRate * (nnetwork.getValue(nextPerception) - nnetwork.getValue(lastPerception));
	double bla = nnetwork.getValue(lastState);
	nnetwork.backProb(errorSignal, 1.0);
	lastPerception = nextPerception;
}

template<class State_T>
void Ai_Arena::TD_Agent<State_T>::findActionFinal()
{
	const auto actual_state = Agent<State_T>::m_environment->actual_state(Agent<State_T>::m_self_pointer);
	auto reward = Agent<State_T>::m_environment->reward(Agent<State_T>::m_self_pointer, actual_state);

	if (reward == 0.1)
	{
		double errorSignal = learnRate * ((double) reward - nnetwork.getValue(lastPerception));
		nnetwork.backProb(errorSignal, 1.0);
	}
	else
	{
		std::vector<Action> possible_actions =
			Agent<State_T>::m_environment->possible_actions(
				Agent<State_T>::m_self_pointer);

		double errorSignal = learnRate * ((double)reward - nnetwork.getValue(lastPerception));
		nnetwork.backProb(errorSignal, 1.0);
		set_action(nextAction(possible_actions));
		lastPerception = nextPerception;
	}
}

template<class State_T>
void TD_Agent<State_T>::findAction2()
{
	
	const auto actual_state = Agent<State_T>::m_environment->actual_state(Agent<State_T>::m_self_pointer);
	auto reward = Agent<State_T>::m_environment->reward(Agent<State_T>::m_self_pointer, actual_state);
	
	if (reward == 0.1)
	{
		double errorSignal = learnRate * ((double)reward - nnetwork.getValue(lastPerception));
		nnetwork.backProb(errorSignal, 1.0);
	}
	else
	{
		if ((rand() % 10) == 0)
		{
			Action next = possible_actions[Utility::random_int_ts(0, possible_actions.size() - 1)];
			auto states = Agent<State_T>::m_environment->assume_action(Agent<State_T>::m_self_pointer, actual_state, next);
			lastPerception = Agent<State_T>::m_environment->get_perception(Agent<State_T>::m_self_pointer, SEE_THE_WHOLE_STATE, states[0]);
			return;
		}

		std::vector<Action> possible_actions =
			Agent<State_T>::m_environment->possible_actions(
				Agent<State_T>::m_self_pointer);

		set_action(nextAction(possible_actions));
		double nextPerceptionValue;

		if (reward == 0.9)
			nextPerceptionValue = 0.0;
		else
			nextPerceptionValue = nnetwork.getValue(nextPerception);

		double errorSignal = learnRate * ((double)reward + (nextPerceptionValue - nnetwork.getValue(lastPerception)));
		nnetwork.backProb(errorSignal, 1.0);
		lastPerception = nextPerception;
	}
}

template <class State_T>
Action TD_Agent<State_T>::nextAction(std::vector<Action> possible_actions)
{
	const auto actual_state = Agent<State_T>::m_environment->actual_state(Agent<State_T>::m_self_pointer);
	Action action = possible_actions[0];
	auto states = Agent<State_T>::m_environment->assume_action(Agent<State_T>::m_self_pointer, actual_state, action);
	nextPerception = Agent<State_T>::m_environment->get_perception(Agent<State_T>::m_self_pointer, SEE_THE_WHOLE_STATE, states[0]);
	double maxStateValue = nnetwork.getValue(nextPerception);

	for (int i = 1; i < possible_actions.size(); i++)
	{

		states = Agent<State_T>::m_environment->assume_action(Agent<State_T>::m_self_pointer, actual_state, possible_actions[i]);
		if (maxStateValue < nnetwork.getValue(Agent<State_T>::m_environment->get_perception(Agent<State_T>::m_self_pointer, SEE_THE_WHOLE_STATE, states[0]))
		{
			action = possible_actions[i];
			nextPerception = Agent<State_T>::m_environment->get_perception(Agent<State_T>::m_self_pointer, SEE_THE_WHOLE_STATE, states[0]);
		}
	}

	return action;
}

/*
//reward function of the agent, computes the error signal for the neural network's backpropagation, the function returns the error signal for statistic purpose
double RlAgent::takeReward(double reward)
{

	double eSignal = learnRate * (reward - nnetwork.getValue(lastInput));
	nnetwork.backProb(eSignal, 1.0);

	if (eSignal > 0)
		return eSignal;
	else
		return (-1) * eSignal;
}
*/

// save learned weights
template <class State_T>
void TD_Agent<State_T>::saveRewardsInFile()
{
	std::ofstream myfile("Weights750k.txt");
	std::vector<std::vector<double>> inputMatrix = nnetwork.returnInputMatrix();
	std::vector<double> hiddenMatrix = nnetwork.returnHiddenMatrix();
	if (myfile.is_open())
	{
		for (int i = 0; i < inputMatrix.size(); i++)
			for (int j = 0; j < inputMatrix[i].size(); j++)
			{
				myfile << inputMatrix[i][j] << " , ";
			}
		for (int i = 0; i < inputMatrix.size(); i++)
			myfile << hiddenMatrix[i] << " , ";

		myfile.close();
	}
	else std::cout << "Unable to open file";
}
//load previous learned weights
template <class State_T>
void TD_Agent<State_T>::loadRewardsFromFile()
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
