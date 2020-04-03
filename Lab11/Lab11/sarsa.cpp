//Larry Schultheis
//CMPSC 441
//Lab 11
//SARSA algorithm

#include <iostream>
#include <time.h>
#include <vector>
using namespace std;


// Q-Learning steps

// Select action a based on policy
int selectAction(vector<vector<float>>& QTable, int state);
// Perform action
void performSelectedAction(vector<vector<float>>& QTable, int action, int action_p, int state, int& state_p, int& loc);
// Calculate the reward r
float obtainReward(vector<vector<float>>& QTable, int loc, int& previousLoc);
// Update Q value of the current state and action
// Return the change in Q in absolute value
float updateQ(vector<vector<float>>& QTable, int action, int action_p, int state, int state_p, float reward);
// Set state to be the next state, state_p
void updateState(vector<vector<float>>& QTable, int& state, int state_p);

void updateAction(vector<vector<float>>& QTable, int& action, int action_p);


// Display info
void printInfo(vector<vector<float>>& QTable, int state, int loc);


const float gamma = 0.1;
const float alpha = 0.1;
const float epsilon = 0.2;


int main()
{

	int numStates = 4;   // two binary features in the state, resulting in [0,0],[0,1],[1,0],[1,1]
	int numActions = 3;

	vector<vector<float>> QTable(numStates, vector<float>(numActions, 0.5));
	vector<vector<float>> OldQTable(numStates, vector<float>(numActions, 0.5));
	vector<vector<float>> QTableChanges(numStates, vector<float>(numActions, 0.5));


	srand(time(NULL));

	int state = 0;
	int state_p = 0;
	int loc = 0;
	int previousLoc = 0;

	bool changed = false;
	int counter = 0;


	int randAction = rand() % 2;
	int action = randAction;
	int action_p = action;

	// change this part so that Q-Learning stops instead of looping forever
	while (true)
	{
		OldQTable = QTable;

		printInfo(QTable, state, loc);

		//int action = selectAction(QTable, state);

		//action_p = action;

		performSelectedAction(QTable, action, action_p, state, state_p, loc);

		float reward = obtainReward(QTable, loc, previousLoc);

		action_p = selectAction(QTable, state_p);

		float ret = updateQ(QTable, action, action_p, state, state_p, reward);

		updateState(QTable, state, state_p);
		updateAction(QTable, action, action_p);

		//convergence check
		for (int i = 0; i < QTable.size(); i++)
		{
			for (int j = 0; j < QTable[i].size(); j++)
			{
				QTableChanges[i][j] = QTable[i][j] - OldQTable[i][j];
				if (QTableChanges[i][j] > 0.3)
				{
					counter = 0;
					break;
				}
			}
		}
		counter++;
		if (counter >= 15)
			break;
	}


	printInfo(QTable, state, loc);
	std::cerr << "Convergence!" << endl;
	std::system("pause");
	return 0;
}


// Perform action
// The result of each action is set from the environment itself
// and outside of the control of the learning algorithm
void performSelectedAction(vector<vector<float>>& QTable, int action, int action_p, int state, int& state_p, int& loc)
{

	if (action == 0) {
		if (state == 0) {
			loc += rand() % 10 + 5;
		}
		else if (state == 1) {
			loc -= rand() % 2 + 15;
		}
		else if (state == 2) {
			loc -= rand() % 2 + 10;
		}
		else if (state == 3) {
			loc -= rand() % 2 + 1;
		}
		state_p = 1;
	}
	else if (action == 1) {
		if (state == 0) {
			loc -= rand() % 2 + 15;
		}
		else if (state == 1) {
			loc += rand() % 10 + 15;
		}
		else if (state == 2) {
			loc -= rand() % 2 + 10;
		}
		else if (state == 3) {
			loc -= rand() % 2 + 10;
		}
		state_p = 2;
	}
	else if (action == 2) {
		if (state == 0) {
			loc += rand() % 10 + 10;
		}
		else if (state == 1) {
			loc -= rand() % 2 + 15;
		}
		else if (state == 2) {
			loc += rand() % 10 + 5;
		}
		else if (state == 3) {
			loc -= rand() % 2 + 10;
		}
		state_p = 3;
	}
	action_p = action;
}

//  Set state to be the next state, state_p
void updateState(vector<vector<float>>& QTable, int& state, int state_p)
{
	state = state_p;
}

void updateAction(vector<vector<float>>& QTable, int& action, int action_p)
{
	action = action_p;
}

void printInfo(vector<vector<float>>& QTable, int state, int loc)
{
	std::system("cls");

	std::cerr << endl << "Q Table: " << endl;
	for (int i = 0; i < QTable.size(); i++) {
		std::cerr << "State" << i << " ";
		for (int j = 0; j < QTable[0].size(); j++) {
			std::cerr << QTable[i][j] << " ";
		}

		std::cerr << endl;
	}

	for (int i = -10; i < 50; i++) {

		if (i == (int)loc / 10) {
			std::cerr << state;
		}
		else {
			std::cerr << "_";
		}

	}
	std::cerr << "->" << endl;
}





// Select action a based on policy
// Return the action
int selectAction(vector<vector<float>>& QTable, int state)
{
	//epsilon greedy policy

	//get the exploration rate (random number betwen 0 and 1) 
	float explorationRate = ((double)rand() / (RAND_MAX));

	//set the highest q value to the first 
	float highestQ = QTable[state][0];

	//track the column (action)
	int action = 0;

	if (explorationRate > epsilon)
	{
		//choose best action
		//for each action in the current state
		for (int i = 0; i < QTable[state].size(); i++)
		{
			if (QTable[state][i] > highestQ)
			{
				//keep track of the highest q value and action
				highestQ = QTable[state][i];
				action = i;
			}
		}

		return action;
	}
	else
	{
		//choose random action
		int randAction = rand() % 2;
		return randAction;
	}



}


// Calculate the reward r
// The reward should be how far the AI has moved forward
// Return the reward
float obtainReward(vector<vector<float>>& QTable, int loc, int& previousLoc)
{
	float reward = loc - previousLoc;
	previousLoc = loc;
	return reward;
}


// Update Q value of the current state and action
// Return the change in Q in absolute value
float updateQ(vector<vector<float>>& QTable, int action, int state, int action_p, int state_p, float reward)
{
	//set the highest q value to the first 
	float bestAction = QTable[state_p][0];
	vector<vector<float>> OldQ;

	//for each action in the current state
	//for (int i = 0; i < QTable[state_p].size(); i++)
	//{
	//	//if the current action is better than the current best
	//	//update the best action
	//	if (QTable[state_p][i] > bestAction)
	//		bestAction = QTable[state_p][i];
	//}

	OldQ = QTable;
	//Update this q value entry using the reward evaluation function
	QTable[state][action] = QTable[state][action] + (alpha * (reward + (gamma * action_p) - QTable[state][action]));
	return abs(QTable[state][action] - OldQ[state][action]);


}
