//Larry Schultheis
//CMPSC 441
//Lab 7

#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

int terminal_test(vector<vector<int>>& board, int goFirst);
bool checkSpace(vector<vector<int>>& board, int row, int col);
void aiMove(vector<vector<int>>& board, int goFirst);
void oppoMove(vector<vector<int>>& board, int goFirst);

const int EMPTY = 0;
const int PLAYX = 1;
const int PLAYO = 2;



int main()
{
	// randomize seed for generating random numbers
	srand((unsigned)time(NULL));

	int row = 3;
	int column = 3;
	int goFirst;

	// declare and initialize the board
	vector<vector<int>> board(row, vector<int>(column, EMPTY));

	//goFirst = 1 for AI
	//goFirst = 0 for opponent 


	cin >> goFirst;

	while (true)
	{
		if (goFirst == 0)
		{
			//Opponent
			oppoMove(board, goFirst);
			aiMove(board, goFirst);
		}
		else if (goFirst == 1)
		{
			//AI
			aiMove(board, goFirst);
			oppoMove(board, goFirst);
		}
		else
		{
			cerr << "Invalid number for variable 'goFirst'" << endl;
		}

		int gameCheck = terminal_test(board, goFirst);
		if (gameCheck == -1)
		{
			//oppo wins
			cerr << "Opponent has won" << endl;
			break;
		}
		else if (gameCheck == 0)
		{
			//tie
			cerr << "The game is a tie" << endl;
			break;
		}
		else if (gameCheck == 1)
		{
			//ai wins
			cerr << "AI has won" << endl;
			break;
		}
		else if (gameCheck == 3)
		{
			//game not over
			cerr << "The game is not finished" << endl;
		}
		else
		{
			//invalid value
			cerr << "Invalid return value from terminal_test()" << endl;
			break;
		}
	}


	cerr << endl;
	cout.flush();
	system("pause");
	return 0;
}

// checks the current board for a winner
// Returns the current state of the board:
// 1 = AI wins, -1 = opponent wins
// 0 = tie, 3 = game not finished
int terminal_test(vector<vector<int>>& board, int goFirst)
{
	int row = board.size();
	int column = board[0].size();

	bool aiWin = false, oppoWin = false, gameOver = true;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (board[i][j] == EMPTY)
			{
				gameOver = false;
			}
		}
	}

	if (!gameOver)
		return 3;

	//check rows
	for (int i = 0; i < row; i++)
	{
		if (board[i][0] == PLAYX && board[i][1] == PLAYX && board[i][2] == PLAYX)
		{
			if (goFirst == 0)
				oppoWin = true;
			else if (goFirst == 1)
				aiWin = true;
			break;
		}

		if (board[i][0] == PLAYO && board[i][1] == PLAYO && board[i][2] == PLAYO)
		{
			if (goFirst == 0)
				aiWin = true;
			else if (goFirst == 1)
				oppoWin = true;
			break;
		}
	}

	//check columns
	for (int i = 0; i < column; i++)
	{
		if (board[0][i] == PLAYX && board[1][i] == PLAYX && board[2][i] == PLAYX)
		{
			if (goFirst == 0)
				oppoWin = true;
			else if (goFirst == 1)
				aiWin = true;
			break;
		}

		if (board[0][i] == PLAYO && board[1][i] == PLAYO && board[2][i] == PLAYO)
		{
			if (goFirst == 0)
				aiWin = true;
			else if (goFirst == 1)
				oppoWin = true;
			break;
		}
	}

	//check diagonals
	if ((board[0][0] == PLAYX && board[1][1] == PLAYX && board[2][2] == PLAYX)
		|| (board[0][2] == PLAYX && board[1][1] == PLAYX && board[2][0] == PLAYX) )
	{
		if (goFirst == 0)
			oppoWin = true;
		else if (goFirst == 1)
			aiWin = true;
	}

	if ((board[0][0] == PLAYO && board[1][1] == PLAYO && board[2][2] == PLAYO)
		|| (board[0][2] == PLAYO && board[1][1] == PLAYO && board[2][0] == PLAYO))
	{
		if (goFirst == 0)
			aiWin = true;
		else if (goFirst == 1)
			oppoWin = true;
	}

	//return game state
	if (oppoWin)
		return -1;
	else if (aiWin)
		return 1;
	else if (gameOver)
		return 0;
}

bool checkSpace(vector<vector<int>>& board, int row, int col)
{
	if (board[row][col] == EMPTY)
		return true;
	return false;
}

void aiMove(vector<vector<int>>& board, int goFirst)
{
	while (true)
	{
		int aiRow = rand() % 3;
		int aiCol = rand() % 3;
		if (checkSpace(board, aiRow, aiCol))
		{
			//space open
			cout << aiRow << " " << aiCol << endl;

			if (goFirst == 1)
			{
				board[aiRow][aiCol] = PLAYX;
			}
			else if (goFirst == 0)
			{
				board[aiRow][aiCol] = PLAYO;
			}
			else
			{
				cerr << "Invalid value for goFirst" << endl;
			}
			break;
		}
	}
}

void oppoMove(vector<vector<int>>& board, int goFirst)
{
	int oppoRow, oppoCol;

	while (true)
	{
		cin >> oppoRow;
		cin >> oppoCol;
		if (checkSpace(board, oppoRow, oppoCol))
		{
			if (goFirst == 0)
			{
				board[oppoRow][oppoCol] = PLAYX;
			}
			else if (goFirst == 1)
			{
				board[oppoRow][oppoCol] = PLAYO;
			}
			else
			{
				cerr << "Invalid value for goFirst" << endl;
			}
			break;
		}
	}

}
