/*
	Ziyi Situ
	Net ID: tz4752
	11/23/2016
	CS 3240
	File name: BoggleSolver.cpp
	Assignment 3 - Boggle Solver

	The driver tests the Dictionary class, SolveBoard function and its
	helper functions to ensure they all work as required.
*/

#include "Dictionary.h"
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <ctime>

const int ROW_SIZE = 4;
const int COL_SIZE = 4;
bool verbose = false;  // decision to show board or not
int numWords = 0;      // the words found
int NumOfPath = 0;     // show the path of a word found on the board
void SolveBoard(string board[][COL_SIZE], Dictionary& dict, 
				Dictionary& wordsFound, bool printBoard);
void SearchForWord(Dictionary& dict, Dictionary& wordsFound, string &word,
				   bool printBoard, int path[][COL_SIZE], 
				   string board[][COL_SIZE], int r, int c);
void printShowBoard(string board[][COL_SIZE], int path[][COL_SIZE],
					string word, int numWords);

int main() 
{
	srand(time(0));
	ifstream myFile;
	Dictionary wordsFound;
	Dictionary dict(myFile);
	string word;         // input to test the methods of Dictionary
	string inputStr;     // to hold the input for board
	char getCharacters;  // choice to fill a board with characters
	char chooseBoard;    // input to show board or not
	string board[ROW_SIZE][COL_SIZE] =
		{ "a", "u", "c", "o",
		  "n", "l", "n", "i",
		  "o", "s", "a", "e",
		  "m", "a", "i", "e" };
		
	cout << dict.wordCount() << " words loaded." << endl << endl;
	
	while (false) {
		cout << "Enter string: ";
		cin >> word;

		if (dict.isWord(word)) {
			cout << word << " is a valid word" << endl;
		} else {
			cout << word << " is NOT a valid word" << endl;
		}

		if (dict.isPrefix(word)) {
			cout << word << " is a valid prefix" << endl;
		} else {
			cout << word << " is NOT a valid prefix" << endl;
		}

		cout << endl;
	}
	
	cout << "A. Enter the characters.\n";
	cout << "B. Get random characters.\n";
	cout << "C. Use default characters.\n";
	cout << "Enter a choice: ";
	cin >> getCharacters;
	while (tolower(getCharacters) != 'a' 
		&& tolower(getCharacters) != 'b'
		&& tolower(getCharacters) != 'c') {
		cout << "Error: Input invalid.\n";
		cout << "A. Enter the characters.\n";
		cout << "B. Get random characters.\n";
		cout << "C. Use default characters.\n";
		cout << "Enter a choice: ";
		cin >> getCharacters;
	}

	cout << "Enter Board" << endl;
	cout << "-----------" << endl;
	switch (getCharacters) {
	case 'a':
	case 'A':
		cin.ignore();
		for (int i = 0; i < ROW_SIZE; i++) {
			cout << "Row[" << i << "]: ";
			getline(cin, inputStr);
			int j = 0, k = 0;
			while (isalpha(inputStr[k]) && k < COL_SIZE) {
				board[i][j] = tolower(inputStr[k]);
				j++;
				k++;
			}
		}
		break;

	case 'b':
	case 'B':
		for (int i = 0; i < ROW_SIZE; i++) {
			cout << "Row[" << i << "]: ";
			for (int j = 0; j < COL_SIZE; j++) {
				board[i][j] = rand() % 26 + 'a';
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
		break;

	case 'c':
	case 'C':
		for (int i = 0; i < ROW_SIZE; i++) {
			cout << "Row[" << i << "]: ";
			for (int j = 0; j < COL_SIZE; j++)
				cout << board[i][j] << " ";
			cout << endl;
		}
		break;
	}

	cout << "Show Board (y/n)?: ";
	cin >> chooseBoard;
	while (tolower(chooseBoard) != 'y' && tolower(chooseBoard) != 'n') {
		cout << "Error: Show Board (y/n)?: ";
		cin >> chooseBoard;
	}
	if (tolower(chooseBoard) == 'y')
		verbose = true;
	
	SolveBoard(board, dict, wordsFound, verbose);

	return 0;
}






/*
	This function starts from each of the element of board, branches to
	eight adjacent directions to form a word. The words found except the
	repetitive ones will be displayed, and the word board and the path 
	board will be showed to indicate the printed word if printBoard is 
	true.
	pre: board, dict, wordsFound and a copy of printBoardare passed into
	as parameters.
	post: The words formed from the characters on the board and also 
	matched the dict are displayed, as well as the word board and the 
	path board will be showed to indicate the printed word if printBoard
	is true.
*/

void SolveBoard(string board[][COL_SIZE], Dictionary& dict, 
				Dictionary& wordsFound, bool printBoard) {
	string word = "";
	int path[ROW_SIZE][COL_SIZE];  // path board to show a word found

	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++)
			path[i][j] = 0;
	}
	
	for (int r = 0; r < ROW_SIZE; r++) {
		for (int c = 0; c < COL_SIZE; c++)
			SearchForWord(dict, wordsFound, word, printBoard, path, 
						  board, r, c);
	}	
}






/*
	This recursion searches and prints all words presenting on boggle.
	pre: dict, wordsFound, word, a copy of printBoardare, path, board 
	and a copy of r and c are passed into as parameters.
	post: The words formed based from board[r][c] branching to 8 
	directions and also matched the dict are displayed, as well as the 
	word board and the path board will be showed to indicate the printed
	word if printBoard is true.
*/
void SearchForWord(Dictionary& dict, Dictionary& wordsFound, 
				   string &word, bool printBoard, int path[][COL_SIZE], 
				   string board[][COL_SIZE], int r, int c) {
	path[r][c] = ++NumOfPath;
	word += board[r][c];	// appends a charcter to the original string

	if (dict.isPrefix(word)) {
		if (!wordsFound.isWord(word)) {
			if (dict.isWord(word)) {
				wordsFound.addWord(word);
				numWords++;
				if (printBoard)
					printShowBoard(board, path, word, numWords);
				else
					cout << left << setw(8) << numWords 
						 << setw(20) << word << endl;
			}			
		}

		for (int row = r - 1; row <= r + 1 && row < ROW_SIZE; row++) {
			for (int col = c - 1; col <= c + 1 && col < COL_SIZE; col++) {
				if (row >= 0 && col >= 0 && !path[row][col])
					SearchForWord(dict, wordsFound, word, printBoard, 
								  path, board, row, col);
			}
		}
		// erases current character from string
		word = word.substr(0, word.length() - 1);
		path[r][c] = 0;   // marks path of current cell as 0
		NumOfPath--;      // decreases 1 from NumOfPath
	} else {
		word = word.substr(0, word.length() - 1);
		path[r][c] = 0;
		NumOfPath--;
	}
}






/*
	This recursion prints a word, and the word board and the path board
	will be showed to indicate the printed word if printBoard is true.
	pre: board, path a copy of word and numWords are passed into as 
	parameters.
	post: The word is displayed, and the word board and the path board
	will be showed to indicate the printed word if printBoard is true.
*/
void printShowBoard(string board[][COL_SIZE], int path[][COL_SIZE], 
					string word, int numWords) {
	cout << "Word: " << word << endl;
	cout << "Number of Words: " << numWords << endl;
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (path[r][c] != 0)
				cout << " '" << board[r][c] << "' ";
			else
				cout << "  " << board[r][c] << "  ";
		}

		cout << setw(10) << " ";

		for (int c = 0; c < 4; c++) {
			if (path[r][c] != 0)
				cout << "  " << path[r][c] << "  ";
			else
				cout << "  " << path[r][c] << "  ";
		}

		cout << endl;
	}
	cout << endl;
}
