//Larry Schultheis
//CMPSC 441
//Lab 12 - RL project part 1

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
int selectAction(int numActions, int numFeatures, int action);
void performSelectedAction(int action);
float obtainReward();
void updateWeights(int action);
void updateState(vector<bool>& state);


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

int totalDamageTaken;

bool hasPotion = true;

float alpha = 0.1;
float gamma = 0.1;
float epsilon = 0.1;

int rounds = 0;

const int numActions = 8;
const int numFeatures = 9;    // minimum 4, but as many as you wish
int countRounds;

// the weights table used for function approximation
vector<vector<float>> weights(numActions, vector<float>(numFeatures + 1, 0.0));

vector<bool> state(numFeatures, false);    // the current state represented as vector of binary features
vector<bool> state_p(numFeatures, false);  // the next state State Prime

int main()
{
	srand(time(NULL));

	state[0] = 1;

	// Set up Reinforcement Learning here
	cin >> rounds;

	for (int i = 0; i < rounds; i++)
	{
		//outer loop = num rounds

		int action = 0;
		hasPotion = true;
		totalDamageTaken = 0;

		while (true)
		{
			//inner loop - repeat until winner

			//select action
			action = selectAction(numActions, numFeatures, action);
			performSelectedAction(action);
			updateState(state);
			updateWeights(action);
			printInfo(weights, state);

			//check for end of round
			if (endRound > 0)
			{
				//round over break inner loop
				break;
			}
		}
		countRounds++;
	}
	printInfo(weights, state);
	cerr << endl;
	cout.flush();
	system("pause");
	return 0;

}


int selectAction(int numActions, int numFeatures, int action)
{
	float sum = 0;
	float largestSum = 0;
	float explore = ((double)rand() / (RAND_MAX));

	if (explore > epsilon && countRounds > 3)
	{
		//choose best
		for (int i = 0; i < numActions - 1; i++)
		{
			for (int j = 0; j < numFeatures; j++)
			{
				if (state[j] == 1)
					sum += weights[i][j];
			}
			if (sum > largestSum)
			{
				largestSum = sum;
				action = i;
			}
			sum = 0;
		}
	}
	else
	{
		//random action
		return rand() % 7;
	}
	if (hasPotion && totalDamageTaken >= 78)
	{
		hasPotion = false;
		totalDamageTaken = totalDamageTaken - 50;
		return HEAL;
	}
	return action;
	//return rand() % numActions;
}

void performSelectedAction(int action)
{
	//perform action
	cout << action << endl;
}

float obtainReward()
{
	if ((damageDealt - damageTaken) == 0)
		return 1;
	return damageDealt - damageTaken;
}

void updateWeights(int action)
{
	float temp = 0;
	for (int i = 0; i < numActions; i++)
	{
		for (int j = 0; j < numFeatures; j++)
		{
			if (temp < weights[i][j])
				temp = weights[i][j];
		}
	}

	for (int i = 0; i < numFeatures; i++)
	{
		if (state[i] == 1)
		{
			float reward = obtainReward();
			weights[action][i] = weights[action][i] + alpha * (reward + gamma * temp - weights[action][i]);
		}
	}
}

void updateState(vector<bool>& state)
{
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

	totalDamageTaken += damageTaken;

	state[1] = oppoGlobeActive == 1;
	state[2] = oppoStoneskin == 1;
	state[3] = oppoStrengthEffect == 1;
	state[4] = globeActive == 1;
	state[5] = stoneskin == 1;
	state[6] = strengthEffect == 1;
	//state[7] = oppoHealthSub50 == 1;
	//state[8] = oppoHealthSub10 == 1;
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