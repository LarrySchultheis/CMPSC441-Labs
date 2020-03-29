//Larry Schultheis
//CMPSC 441
//Lab 10

#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

const int gamma = 0.1;
const int epsilon = 0.1;

// Q-learning steps

// Select action a based on policy
int selectAction(vector<vector<float>>& QTable, int state);
// Perform action
void performSelectedAction(vector<vector<float>>& QTable, int action, int state, int& state_p, int& loc);
// Calculate the reward r
float obtainReward(vector<vector<float>>& QTable, int loc, int& previousLoc);
// Update Q value of the current state and action
void updateQ(vector<vector<float>>& QTable, int action, int state, int state_p, float reward);
// Set state to be the next state, state_p
void updateState(vector<vector<float>>& QTable, int& state, int state_p);
// Display info
void printInfo(vector<vector<float>>& QTable, int state, int loc);




int main()
{

	int numStates = 4;   // two binary features in the state, resulting in [0,0],[0,1],[1,0],[1,1]
	int numActions = 3;

	vector<vector<float>> QTable(numStates, vector<float>(numActions, 0.5));


	int state = 0;
	int state_p = 0;
	int loc = 0;
	int previousLoc = 0;

	while (true)
	{
		printInfo(QTable, state, loc);

		int action = selectAction(QTable, state);

		performSelectedAction(QTable, action, state, state_p, loc);

		float reward = obtainReward(QTable, loc, previousLoc);

		updateQ(QTable, action, state, state_p, reward);

		updateState(QTable, state, state_p);

		system("pause");
	}

	return 0;
}


// Perform action
// The result of each action is set from the environment itself
// and outside of the control of the learning algorithm
void performSelectedAction(vector<vector<float>>& QTable, int action, int state, int& state_p, int& loc)
{

	if (action == 0) {
		if (state == 0) {
			loc += 10;
		}
		else if (state == 1) {
			loc -= 20;
		}
		else if (state == 2) {
			loc -= 20;
		}
		else if (state == 3) {
			loc -= 10;
		}
		state_p = 1;
	}
	else if (action == 1) {
		if (state == 0) {
			loc -= 20;
		}
		else if (state == 1) {
			loc += 20;
		}
		else if (state == 2) {
			loc -= 20;
		}
		else if (state == 3) {
			loc -= 10;
		}
		state_p = 2;
	}
	else if (action == 2) {
		if (state == 0) {
			loc -= 20;
		}
		else if (state == 1) {
			loc -= 20;
		}
		else if (state == 2) {
			loc += 15;
		}
		else if (state == 3) {
			loc -= 10;
		}
		state_p = 3;
	}

}





//  Set state to be the next state, state_p
void updateState(vector<vector<float>>& QTable, int& state, int state_p)
{
	state = state_p;
}


void printInfo(vector<vector<float>>& QTable, int state, int loc)
{
	system("cls");

	cerr << endl << "Q Table: " << endl;
	for (int i = 0; i < QTable.size(); i++) {
		cerr << "State" << i << " ";
		for (int j = 0; j < QTable[0].size(); j++) {
			cerr << QTable[i][j] << " ";
		}

		cerr << endl;
	}

	for (int i = -10; i < 50; i++) {

		if (i == (int)loc / 10) {
			cerr << state;
		}
		else {
			cerr << "_";
		}

	}
	cerr << "->" << endl;
}


// Select action a based on policy
int selectAction(vector<vector<float>>& QTable, int state)
{
	double explorationRate = ((double)rand() / (RAND_MAX));
	cout << explorationRate;
	return rand() % 2;
}


// Calculate the reward r
// The reward should be how far the AI has moved forward
// You have current location and previous location
float obtainReward(vector<vector<float>>& QTable, int loc, int& previousLoc)
{
	return loc - previousLoc;
}


// Update Q value of the current state and action
void updateQ(vector<vector<float>>& QTable, int action, int state, int state_p, float reward)
{

}