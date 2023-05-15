#include <iostream>
#include <vector>
#include <ios> //used to get stream size
#include <limits> //used to get numeric limits
using namespace std;

// Function definitions
int handleIntegerInput(int maxSelection);
void createDefaultPuzzle(vector<vector<int>>& currentState, vector<vector<int>>& goalState);
int createCustomPuzzle(vector<vector<int>>& currentState, vector<vector<int>>& goalState);
bool puzzleIsValid(vector<vector<int>>& puzzle, int size);
void printPuzzle(vector<vector<int>>& puzzle, int size);


struct BoardState {
	vector<vector<int>> state;
	int searchDepth;
};

int main() {

	int input = 0; // Stores user input for menu selection
	vector<vector<int>> currentState; // The state we will expand
	vector<vector<int>> goalState; // The goal state we wish to reach
	int puzzleSize = 0; // NxN size of the puzzle

	cout << "Welcome to the Sliding Puzzle Solver. Please select a puzzle type:\n";
	cout << "1. Use a default puzzle\n";
	cout << "2. Create a custom puzzle\n";
	input = handleIntegerInput(2);
	
	/* This section creates the initial state and goal state for the puzzle to be solved. */

	if (input == 1) { // Create a default puzzle
		createDefaultPuzzle(currentState, goalState);
		puzzleSize = 3;
	}
	else if (input == 2) { // Create a custom puzzle
		puzzleSize = createCustomPuzzle(currentState, goalState);
	}

	cout << "\nPuzzle Info\n";
	cout << "Initial State:\n";
	printPuzzle(currentState, puzzleSize);
	cout << "Goal State:\n";
	printPuzzle(goalState, puzzleSize);

	cout << "\nPlease select an algorithm to use:\n";
	cout << "1. Uniform Cost Search\n";
	cout << "2. A* with Misplaced Tile Heuristic\n";
	cout << "3. A* with Manhattan Distance Heuristic\n";
	input = handleIntegerInput(3);

	if (input == 1) { // Uniform Cost Search
		
	}
	else if (input == 2) { // A* with Misplaced Tile Heuristic

	}
	else if (input == 3) { // A* with Manhatten Distance Heuristic

	}

	return 0;
}

/*
A helper function to easily obtain and validate user input for integers.
Allows for inputs from 1 to maxSelection
Input:
	maxSelection, the maximum input allowed
Output:
	int, the integer selection
*/
int handleIntegerInput(int maxSelection) {
	int input = 0;
	bool validInput = false;
	while (!validInput) {
		cout << "Input: ";
		cin >> input;
		if (cin.fail()) {
			cout << "Please type a valid input\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
		}
		else if (input < 1 || input > maxSelection) {
			cout << "Please type a valid input\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
		}
		else
			validInput = true;
	}
	return input;
}

void createDefaultPuzzle(vector<vector<int>> &currentState, vector<vector<int>> &goalState) {
	int input = 0;
	cout << "\nPlease select puzzle difficulty (higher depth is more difficult)\n";
	cout << "1. Depth 0\n";
	cout << "2. Depth 2\n";
	cout << "3. Depth 4\n";
	cout << "4. Depth 8\n";
	cout << "5. Depth 12\n";
	cout << "6. Depth 16\n";
	cout << "7. Depth 20\n";
	cout << "8. Depth 24\n";

	input = handleIntegerInput(8);
	switch(input) {
		case 1: currentState = {{1,2,3}, {4,5,6}, {7,8,0}}; break; // depth 0
		case 2: currentState = {{1,2,3}, {4,5,6}, {0,7,8}}; break; // depth 2
		case 3:	currentState = {{1,2,3}, {5,0,6}, {4,7,8}}; break; // depth 4
		case 4:	currentState = {{1,3,6}, {5,0,2}, {4,7,8}}; break; // depth 8
		case 5:	currentState = {{1,3,6}, {5,0,7}, {4,8,2}}; break; // depth 12
		case 6:	currentState = {{1,6,7}, {5,0,3}, {4,8,2}}; break; // depth 16
		case 7:	currentState = {{7,1,2}, {4,8,5}, {6,3,0}}; break; // depth 20
		case 8:	currentState = {{0,7,2}, {4,6,1}, {3,5,8}}; break; // depth 24
		default: cout << "Fatal error. terminating program.\n"; exit(1); // should never reach this
	}
	goalState = {{1,2,3}, {4,5,6}, {7,8,0}};
}

int createCustomPuzzle(vector<vector<int>> &currentState, vector<vector<int>> &goalState) {
	return 0;
}

void printPuzzle(vector<vector<int>> &puzzle, int size) {
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++)
			cout << puzzle[i][j] << " ";
		cout << endl;
	}
}
