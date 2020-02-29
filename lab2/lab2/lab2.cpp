//Larry Schultheis
//CMPSC 441
//Lab2

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
using namespace std;

struct gameplay
{
	int AINum;
	int OppoNum;
};

int getChoice(int guess) {
	int choice = 0;
	switch (guess)
	{
	case 0:
		choice = 1;
		break;
	case 1:
		choice = 2;
		break;
	case 2:
		choice = 0;
		break;
	}

	return choice;
}

int getOppo(vector<gameplay> gameplaySeq) {
	bool same = true;
	for (int j = 1; j < 3; j++) {
		if (gameplaySeq.at(j).OppoNum != gameplaySeq.at(j - 1).OppoNum) {
			same = false;
			break;
		}
	}
	if (same) {
		//single or switch
		return 1;
	}
	else {
		//mimic
		return 0;
	}
}


int main()
{
	int rounds;
	int oppoAgent = 0;
	int oppoGuess;
	int count = -1;
	bool set = false;
	int agentChoice = 0;

	srand(time(NULL));
	int rand;

	vector<gameplay> gameplaySeq;

	cerr << "How many rounds would you like to play?" << endl;
	cin >> rounds;

	for (int i = 0; i < rounds; i++)
	{
		if (i <= 2)
			agentChoice = i;
		

		cout << agentChoice << endl;
		cin >> oppoGuess;

		gameplay *gp = new gameplay();
		gp->AINum = agentChoice;
		gp->OppoNum = oppoGuess;

		gameplaySeq.push_back(*gp);
		count++;

		if (i > 2) {

			if (!set) {
				oppoAgent = getOppo(gameplaySeq);
				set = true;
			}

			switch (oppoAgent) {
			case 0:
				//mimic
				agentChoice = getChoice(agentChoice);
				break;
			case 1:
				//single or switch
				agentChoice = getChoice(oppoGuess);
				break;
			}
		}
	}

	for (int i = 0; i < gameplaySeq.size(); i++)
	{
		cerr << gameplaySeq.at(i).AINum << " " << gameplaySeq.at(i).OppoNum << endl;
	}


	cout.flush();
	system("pause");
	return 0;
}


