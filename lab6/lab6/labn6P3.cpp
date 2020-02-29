//Larry Schultheis
//CMPSC 441
//Lab 6

#include <time.h>
#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

void showBoard(const vector<vector<int>>& board);
int calculateH(const vector<vector<int>>& board);
void move(vector<vector<int>>& board, int queenColumn, int queenDestRow);
int evaluateSuccessor(vector<vector<int>>& board, int queenColumn, int queenDestRow);
int getAvg(int numPoints, vector<int> nums);

const int EMPTY = 0;
const int QUEEN = 1;

struct value {
	int value;
	int dstRow;
	int col;
	int boardNum;
};

bool compareByH(const value &a, const value &b)
{
	return a.value < b.value;
}

int main()
{
	srand((unsigned)time(NULL));

	int row = 10;
	int column = 10;

	int trials = 100;
	int h;
	int wins = 0;
	int k = 3, count = 0;

	vector<vector<int>> successors;

	// declare and initialize the board
	vector<vector<int>> board1(row, vector<int>(column, EMPTY));
	vector<vector<int>> board2(row, vector<int>(column, EMPTY));
	vector<vector<int>> board3(row, vector<int>(column, EMPTY));


    value bestVals[3];

	// hill-climbing local search

	// Fill in this part ...
	while (trials > 0)
	{
		vector<value> trackVals;
		// start with a random state (board configuration), with one queen in each column

		count = 0;

		for (int i = 0; i < column; i++)
		{
			board1[rand() % row][i] = QUEEN;
		}
		for (int i = 0; i < column; i++)
		{
			board2[rand() % row][i] = QUEEN;
		}
		for (int i = 0; i < column; i++)
		{
			board3[rand() % row][i] = QUEEN;
		}

		for (int i = 0; i < k; i++)
		{
			bestVals[i].value = 1000;
		}

			int numSuccessors = 0;
			vector<int> tempSuccessors;

			bool flag = false;
			while (true)
			{
				//for each column
				for (int i = 0; i < board1[0].size(); i++)
				{
					//for each row
					for (int j = 0; j < board1.size(); j++)
					{
						//get h value of position
						h = evaluateSuccessor(board1, i, j);
						value v;
						v.value = h;
						v.col = i;
						v.dstRow = j;
						v.boardNum = 1;

						trackVals.push_back(v);
						numSuccessors++;
					}
				}

				for (int i = 0; i < board2[0].size(); i++)
				{
					//for each row
					for (int j = 0; j < board2.size(); j++)
					{
						//get h value of position
						h = evaluateSuccessor(board2, i, j);
						numSuccessors++;

						value v;
						v.value = h;
						v.col = i;
						v.dstRow = j;
						v.boardNum = 2;

						trackVals.push_back(v);
					}
				}

				for (int i = 0; i < board3[0].size(); i++)
				{
					//for each row
					for (int j = 0; j < board3.size(); j++)
					{
						//get h value of position
						h = evaluateSuccessor(board1, i, j);
						numSuccessors++;

						value v;
						v.value = h;
						v.col = i;
						v.dstRow = j;
						v.boardNum = 3;

						trackVals.push_back(v);

					}
				}
		
				// Sort all runs from smallest to largest h value
				// https://stackoverflow.com/questions/4892680/sorting-a-vector-of-structs
				sort(trackVals.begin(), trackVals.end(), compareByH);

				//Could not figure out break and move conditions
				int pmtaw = 0;
				for (int i = 0; i < 3; i++)
				{
					if (trackVals.at(i).boardNum == 1)
					{
						if (trackVals.at(i).value <= calculateH(board1))
						{
							move(board1, trackVals.at(i).col, trackVals.at(i).dstRow);
						}
						else pmtaw++;
					}
					else if (trackVals.at(i).boardNum == 2)
					{
						if (trackVals.at(i).value <= calculateH(board2))
						{
							move(board2, trackVals.at(i).col, trackVals.at(i).dstRow);	
						}
						else pmtaw++;
					}
					else if (trackVals.at(i).boardNum == 3)
					{
						if (trackVals.at(i).value <= calculateH(board3))
						{
							move(board3, trackVals.at(i).col, trackVals.at(i).dstRow);
						}
						else pmtaw++;
					}

					if (pmtaw >= 3)
						flag = true;
				}
				if (flag)
					break;
			}

			if (calculateH(board1) == 0 || calculateH(board2) == 0 || calculateH(board3) == 0)
			{

				wins++;
			}
		trials--;
	}


	

	// show the resulting solution
	//showBoard(board);
	//cerr << "Result: h = " << calculateH(board) << endl;

	cerr << "Number of solved problems out of 100: " << wins << endl;

	system("pause");
	return 0;
}

int getAvg(int numPoints, vector<int> nums)
{
	int sum = 0;
	for (int i = 0; i < numPoints; i++)
	{
		sum += nums.at(i);
	}
	return sum / numPoints;
}

// Shows the board on the screen
void showBoard(const vector<vector<int>>& board)
{
	int row = board.size();
	int column = board[0].size();

	cerr << "The current board:" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (board[i][j] == QUEEN)
				cerr << "Q" << " ";
			else
				cerr << "-" << " ";
		}
		cerr << endl;
	}

}

// Calculates the number of pairs of queens attacking one another
// Returns the h value of the current board
int calculateH(const vector<vector<int>>& board)
{
	int row = board.size();
	int column = board[0].size();

	int result = 0;

	for (int col1 = 0; col1 < column; col1++) {

		int row1, row2;

		for (int r = 0; r < row; r++)
		{
			if (board[r][col1] == QUEEN)
			{
				row1 = r;
				break;
			}
		}

		for (int col2 = col1 + 1; col2 < column; col2++) {

			for (int r = 0; r < row; r++)
			{
				if (board[r][col2] == QUEEN)
				{
					row2 = r;
					break;
				}
			}

			if (row2 == row1 || row2 - row1 == col2 - col1 || row1 - row2 == col2 - col1)
			{
				result++;
			}
		}
	}

	return result;
}


// Moves the queen in column queenColumn to the row queenDestRow of the same column



void move (vector<vector<int>>& board, int queenColumn, int queenDestRow)
{

	int row = board.size();
	int column = board[0].size();

	for (int r = 0; r < row; r++)
	{
		if (r == queenDestRow)
		{
			board[r][queenColumn] = QUEEN;
		}
		else
		{
			board[r][queenColumn] = EMPTY;
		}
	}
}

// Calculates the number of pairs of queens attacking one another, if 
// the queen in column queenColumn were moved to the row queenDestRow of the same column
// Returns the h value of the board if the queen were moved to the new row
int evaluateSuccessor(vector<vector<int>>& board, int queenColumn, int queenDestRow)
{

	int row = board.size();
	int column = board[0].size();

	// Remember the current row number of the queen in the column queenColumn
	int queenCurrentRow;

	for (int r = 0; r < row; r++)
	{
		if (board[r][queenColumn] == QUEEN)
		{
			queenCurrentRow = r;
			break;
		}
	}

	// Move the queen to the new row to get a successor state
	move(board, queenColumn, queenDestRow);

	// Calculate the h value of the successor state
	int result = calculateH(board);

	// Move the queen back to its previous row
	// Return to the current state
	move(board, queenColumn, queenCurrentRow);

	return result;
}