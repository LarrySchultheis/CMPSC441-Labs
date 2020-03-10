//Larry Schultheis
//CMPSC 441
//Lab 8

#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int terminal_test(vector<vector<int>>& board);
bool checkSpace(vector<vector<int>>& board, int row, int col);
void aiMove(vector<vector<int>>& board, int goFirst);
void oppoMove(vector<vector<int>>& board, int goFirst);
pair<int, int> minimax_decision(vector<vector<int>>& board);
int max_value(vector<vector<int>>& board);
int min_value(vector<vector<int>>& board);

const int EMPTY = 0;
const int PLAYX = 1;
const int PLAYO = 2;

int wentFirst;
int minUtil = 1000;
int maxUtil = -1000;

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
	wentFirst = goFirst;

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

		int gameCheck = terminal_test(board);
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
int terminal_test(vector<vector<int>>& board)
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

	//check rows
	for (int i = 0; i < row; i++)
	{
		if (board[i][0] == PLAYX && board[i][1] == PLAYX && board[i][2] == PLAYX)
		{
			if (wentFirst == 0)
				oppoWin = true;
			else if (wentFirst == 1)
				aiWin = true;
			break;
		}

		if (board[i][0] == PLAYO && board[i][1] == PLAYO && board[i][2] == PLAYO)
		{
			if (wentFirst == 0)
				aiWin = true;
			else if (wentFirst == 1)
				oppoWin = true;
			break;
		}
	}

	//check columns
	for (int i = 0; i < column; i++)
	{
		if (board[0][i] == PLAYX && board[1][i] == PLAYX && board[2][i] == PLAYX)
		{
			if (wentFirst == 0)
				oppoWin = true;
			else if (wentFirst == 1)
				aiWin = true;
			break;
		}

		if (board[0][i] == PLAYO && board[1][i] == PLAYO && board[2][i] == PLAYO)
		{
			if (wentFirst == 0)
				aiWin = true;
			else if (wentFirst == 1)
				oppoWin = true;
			break;
		}
	}

	//check diagonals
	if ((board[0][0] == PLAYX && board[1][1] == PLAYX && board[2][2] == PLAYX)
		|| (board[0][2] == PLAYX && board[1][1] == PLAYX && board[2][0] == PLAYX) )
	{
		if (wentFirst == 0)
			oppoWin = true;
		else if (wentFirst == 1)
			aiWin = true;
	}

	if ((board[0][0] == PLAYO && board[1][1] == PLAYO && board[2][2] == PLAYO)
		|| (board[0][2] == PLAYO && board[1][1] == PLAYO && board[2][0] == PLAYO))
	{
		if (wentFirst == 0)
			aiWin = true;
		else if (wentFirst == 1)
			oppoWin = true;
	}

	//return game state
	if (oppoWin)
		return -1;
	else if (aiWin)
		return 1;
	else if (gameOver)
		return 0;
	else
		return 3;
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
		//int aiRow = rand() % 3;
		//int aiCol = rand() % 3;

		pair<int, int> newMove = minimax_decision(board);
		int newX = newMove.first, newY = newMove.second;

		if (checkSpace(board, newX, newY))
		{
			//space open
			cout << newX << " " << newY << endl;

			if (goFirst == 1)
			{
				board[newX][newY] = PLAYX;
			}
			else if (goFirst == 0)
			{
				board[newX][newY] = PLAYO;
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
		else
			cerr << "Space is already occupied" << endl;
	}
}

// minimax decision
// Returns action with maximum value with coordinates (newR, newC)
// This function has been partially completed for you
pair<int, int> minimax_decision(vector<vector<int>>& board)
{
	int row = board.size();
	int column = board[0].size();

	int newR = -1, newC = -1;

	int returnVal = -100;
	int currentVal = returnVal;

	// for each action a which is row i and column j
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {

			if (board[i][j] == EMPTY)
			{
				// fill in this part
				// simulate the action by AI to get the resulting board state -this is RESULT(state,a) in the pseudo-code

								// call min_value on the resulting board to get the value of the board and
				// keep track of the row newR and column newC of the action with maximum return value				

				// undo the simulated action by setting the board back to original state

				maxUtil = -1000;
				minUtil = 1000;



				vector<vector<int>> b(row, vector<int>(column, EMPTY));
				for (int i = 0; i < b.size(); i++)
				{
					for (int j = 0; j < b[0].size(); j++)
					{
						b[i][j] = board[i][j];
					}
				}

				//if (wentFirst == 0)
				//{
				//	//opponent
				//	board[i][j] = PLAYO;
				//}
				//else if (wentFirst == 1)
				//{
				//	//AI
				//	board[i][j] = PLAYX;
				//}
				//else
				//	cerr << "Invalid value for wentFirst" << endl;

				currentVal = min_value(board);

				if (currentVal > returnVal)
				{
					newR = i;
					newC = j;
					returnVal = currentVal;
				}

				for (int i = 0; i < b.size(); i++)
				{
					for (int j = 0; j < b[0].size(); j++)
					{
						board[i][j] = b[i][j];
					}
				}
			}
		}
	}
	return pair<int, int>(newR, newC);

}


// max value, returns a utility value of 
// 1 = AI wins / 0 = tie / -1 = opponent wins
int max_value(vector<vector<int>>& board)
{
	int row = board.size();
	int column = board[0].size();

	if (terminal_test(board) == 1)
	{
		//AI wins
		return 1;
	}
	if (terminal_test(board) == -1)
	{
		//oppo wins
		return -1;
	}
	if (terminal_test(board) == 0)
	{
		//tie
		return 0;
	}


	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (board[i][j] == EMPTY)
			{
				if (wentFirst == 0)
				{
					board[i][j] = PLAYO;
				}
				else if (wentFirst == 1)
				{
					board[i][j] = PLAYX;
				}
				maxUtil = max(maxUtil, min_value(board));
			}
		}
	}
	return maxUtil;
}



// min value, returns a utility value of 
// 1 = AI wins / 0 = tie / -1 = opponent wins
int min_value(vector<vector<int>>& board)
{
	int row = board.size();
	int column = board[0].size();

	if (terminal_test(board) == 1)
	{
		//AI wins
		return 1;
	}
	if (terminal_test(board) == -1)
	{
		//oppo wins
		return -1;
	}
	if (terminal_test(board) == 0)
	{
		//tie
		return 0;
	}


	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (board[i][j] == EMPTY)
			{
				if (wentFirst == 0)
				{
					board[i][j] = PLAYX;
				}
				else if (wentFirst == 1)
				{
					board[i][j] = PLAYO;
				}
				minUtil = min(minUtil, max_value(board));

			}
		}
	}
	return minUtil;

}
