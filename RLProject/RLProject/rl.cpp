#include <iostream>
#include <time.h>
#include <iomanip>
#include <vector>
using namespace std;

const int MISSILE = 0;
const int FIREBALL = 1;
const int DAGGER = 2;
const int STAFF = 3;
const int GLOBE = 4;
const int STONESKIN = 5;
const int STRENGTH = 6;
const int HEAL = 7;


// Display info
void printInfo(vector<vector<float>>& weights, vector<bool>& state);

// Q-Learning or SARSA steps with function approximation
int selectAction(int numActions);
void performSelectedAction(int action, vector<bool>& state);
float obtainReward();
void updateWeights();
void updateState();
void updateAction();   // SARSA only


//current game info
//1 - yes, 0 - no for binary states
int oppoAction;
int damageDealt = 0;
int damageTaken = 0;
int oppoHealthSub50 = 0;
int oppoHealthSub10 = 0;
int globeActive = 0;
int stoneskin = 0;
int strengthEffect = 0;
int oppoGlobeActive = 0;
int oppoStoneskin = 0;
int oppoStrengthEffect = 0;
int endRound = 0; //0 - not finished, 1 - I won, 2 - Oppo won, 3 - both dead

int health = 100;


int main()
{
	srand(time(NULL));

	const int numActions = 8;
	const int numFeatures = 4;    // minimum 4, but as many as you wish
	int rounds;

	float alpha = 0.1f;
	float gamma = 0.1f;
	float epsilon = 0.1f;

	// the weights table used for function approximation
	vector<vector<float>> weights(numActions, vector<float>(numFeatures + 1, 0.0));

	vector<bool> state(numFeatures, false);    // the current state represented as vector of binary features
	vector<bool> state_p(numFeatures, false);  // the next state State Prime



	// Set up Reinforcement Learning here
	cin >> rounds;

	for (int i = 0; i < rounds; i++)
	{
		//outer loop = num rounds

		int action;
		health = 100;

		while (true)
		{
			//inner loop - repeat until winner

			//select action
			action = selectAction(numActions);

			performSelectedAction(action, state);

			//check for end of round
			if (endRound > 0)
			{
				//round over break inner loop
				break;
			}

			//obtain reward

			//update weights

			//update state

			//update action

			printInfo(weights, state);
		}
	}


	printInfo(weights, state);
	cerr << endl;
	cout.flush();
	system("pause");
	return 0;

}


int selectAction(int numActions)
{
	return rand() % numActions;
}

void performSelectedAction(int action, vector<bool> &state)
{
	//perform action
	cout << action << endl;

	//get current game info
	cin >> oppoAction;
	cin >> damageDealt;
	cin >> damageTaken;
	cin >> oppoHealthSub50;
	cin >> oppoHealthSub10;
	cin >> globeActive;
	cin >> stoneskin;
	cin >> strengthEffect;
	cin >> oppoGlobeActive;
	cin >> oppoStoneskin;
	cin >> oppoStrengthEffect;
	cin >> endRound;

	health -= damageTaken;

	state[0] = oppoGlobeActive ? 1 : true;
	state[1] = oppoStoneskin ? 1 : true;
	state[2] = strengthEffect ? 1 : true;
	state[3] = oppoHealthSub10 ? 1 : true;


}

// prints the weights and the features in the current state
void printInfo(vector<vector<float>>& weights, vector<bool>& state)
{
	int numActions = weights.size();
	int numColumns = weights[0].size();

	cerr << endl << "Weights: " << endl;
	for (int i = 0; i < numActions; i++) {
		cerr << "Action" << i << " ";
		for (int j = 0; j < numColumns; j++) {
			cerr << setw(8) << left;
			cerr << setprecision(3) << weights[i][j];
		}
		cerr << endl;
	}

	cerr << "The current state: " << endl;
	cerr << "      Always1   ";
	for (unsigned int i = 0; i < state.size(); i++) {
		cerr << setw(8) << left;
		cerr << state[i];
	}
	cerr << endl;
}