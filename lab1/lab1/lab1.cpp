//Larry Schultheis
//CMPSC 441
//Lab1

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

int main()
{
	int rounds;
	srand(time(NULL));
	int rand;
	int userGuess;

	vector<gameplay> gameplaySeq;

	cout << "How many rounds would you like to play?" << endl;
	cin >> rounds;
	
	while (rounds > 0) 
	{
		rand = (std::rand() % 2) + 1;

		cout << "Rock (0), Paper (1), or Scissors (2)" << endl;
		cin >> userGuess;

		cout << rand << endl;


		if ((rand == 0 && userGuess == 0) || (rand == 1 && userGuess == 1) || (rand == 2 && userGuess == 2))
		{
			cout << "It's a tie" << endl;
		}

		if ((rand == 0 && userGuess == 1) || (rand == 1 && userGuess == 2) || (rand == 2 && userGuess == 0))
		{
			cout << "You win!" << endl;
		}

		if ((rand == 0 && userGuess == 2) || (rand == 1 && userGuess == 0) || (rand == 2 && userGuess == 1))
		{
			cout << "You lose!" << endl;
		}

		cout << endl;

		gameplay *gp = new gameplay();
		gp->AINum = rand;
		gp->OppoNum = userGuess;

		gameplaySeq.push_back(*gp);

		rounds--;
	}

	for (int i = 0; i < gameplaySeq.size(); i++)
	{
		cout << gameplaySeq.at(i).AINum << " " << gameplaySeq.at(i).OppoNum << endl;
	}


	cout.flush();
	system("pause");
	return 0;
}

