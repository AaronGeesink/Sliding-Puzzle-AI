#include <iostream>
#include <vector>
#include <ios>
#include <limits>
#include <unordered_map>
#include <queue>
using namespace std;

// Function definitions
int handleIntegerInput(int maxSelection);
void createDefaultPuzzle(vector<vector<int>>& initialState, vector<vector<int>>& goalState);
void createCustomPuzzle(vector<vector<int>>& initialState, vector<vector<int>>& goalState);
bool puzzleIsValid(vector<vector<int>>& puzzle);
void printPuzzle(vector<vector<int>>& puzzle);
string puzzleToString(vector<vector<int>>& puzzle);

void uniformCostSearch(vector<vector<int>>& initialState, vector<vector<int>>& goalState);


struct BoardStateNode {
	vector<vector<int>> state; // state of this node
	int depth; // depth that this node was expanded
};

int main() {

	int input = 0; // Stores user input for menu selection
	vector<vector<int>> initialState; // The state we will expand
	vector<vector<int>> goalState; // The goal state we wish to reach

	cout << "Welcome to the Sliding Puzzle Solver. Please select a puzzle type:\n";
	cout << "1. Use a default puzzle\n";
	cout << "2. Create a custom puzzle\n";
	input = handleIntegerInput(2);
	
	/* This section creates the initial state and goal state for the puzzle to be solved. */

	if (input == 1) { // Create a default puzzle
		createDefaultPuzzle(initialState, goalState);
	}
	else if (input == 2) { // Create a custom puzzle
		createCustomPuzzle(initialState, goalState);
	}

	cout << "\nPuzzle Info\n";
	cout << "Initial State:\n";
	printPuzzle(initialState);
	cout << "Goal State:\n";
	printPuzzle(goalState);

	cout << "\nPlease select an algorithm to use:\n";
	cout << "1. Uniform Cost Search\n";
	cout << "2. A* with Misplaced Tile Heuristic\n";
	cout << "3. A* with Manhattan Distance Heuristic\n";
	input = handleIntegerInput(3);

	if (input == 1) { // Uniform Cost Search
		uniformCostSearch(initialState, goalState);
	}
	else if (input == 2) { // A* with Misplaced Tile Heuristic

	}
	else if (input == 3) { // A* with Manhattan Distance Heuristic

	}

	return 0;
}

/*
A helper function to easily obtain and validate user input for integers.
Allows for inputs from 1 to maxSelection
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

/*
Creates a default 3x3 puzzle.
The user can select between 8 puzzles of increasing difficulty.
*/
void createDefaultPuzzle(vector<vector<int>> &initialState, vector<vector<int>> &goalState) {
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
		case 1: initialState = {{1,2,3}, {4,5,6}, {7,8,0}}; break; // depth 0
		case 2: initialState = {{1,2,3}, {4,5,6}, {0,7,8}}; break; // depth 2
		case 3:	initialState = {{1,2,3}, {5,0,6}, {4,7,8}}; break; // depth 4
		case 4:	initialState = {{1,3,6}, {5,0,2}, {4,7,8}}; break; // depth 8
		case 5:	initialState = {{1,3,6}, {5,0,7}, {4,8,2}}; break; // depth 12
		case 6:	initialState = {{1,6,7}, {5,0,3}, {4,8,2}}; break; // depth 16
		case 7:	initialState = {{7,1,2}, {4,8,5}, {6,3,0}}; break; // depth 20
		case 8:	initialState = {{0,7,2}, {4,6,1}, {3,5,8}}; break; // depth 24
		default: cout << "Fatal error. terminating program.\n"; exit(1); // should never reach this
	}
	goalState = {{1,2,3}, {4,5,6}, {7,8,0}};
}

void createCustomPuzzle(vector<vector<int>> &initialState, vector<vector<int>> &goalState) {
	
}

void printPuzzle(vector<vector<int>> &puzzle) {
	for(int i = 0; i < puzzle.size(); i++) {
		for(int j = 0; j < puzzle[i].size(); j++)
			cout << puzzle[i][j] << " ";
		cout << endl;
	}
}

string puzzleToString(vector<vector<int>> &puzzle)
{
	string puzzleString = "";
	for(int i = 0; i < puzzle.size(); i++) {
		for(int j = 0; j < puzzle[i].size(); j++)
			puzzleString.append(to_string(puzzle[i][j]));
	}
	return puzzleString;
}

void uniformCostSearch(vector<vector<int>> &initialState, vector<vector<int>> &goalState) {
	queue<BoardStateNode> nodesToExpand; // queue of nodes to expand
	unordered_map<string, bool> repeatedStates; // an unordered_map used to keep track of repeated states
	int numberNodesExpanded = 0;
	int maxQueueSize = 1;

	BoardStateNode initialNode;
	initialNode.state = initialState;
	initialNode.depth = 0;

	nodesToExpand.push(initialNode);
	string initialKey = puzzleToString(initialState);
	repeatedStates.insert({initialKey, true});

	// function ends either when goal is found, or when full search tree is exhausted
	while(!nodesToExpand.empty()) {
		BoardStateNode currentNode = nodesToExpand.front();
		nodesToExpand.pop();

		int currentDepth = currentNode.depth + 1;
		numberNodesExpanded++;

		// Goal test
		if (currentNode.state == goalState) {
			cout << "\nGoal state!\n\n";
			cout << "Solution depth was " << currentNode.depth << endl;
			cout << "Number of nodes expanded: " << numberNodesExpanded << endl;
			cout << "Max queue size: " << maxQueueSize;
			return;
		}

		// Find the the location of the empty tile (labeled zero)
		int emptyRow = -1;
		int emptyCol = -1;
		for(int i = 0; i < currentNode.state.size(); i++) {
			for(int j = 0; j < currentNode.state[i].size(); j++)
				if (currentNode.state[i][j] == 0) {
					emptyRow = i;
					emptyCol = j;
				}
		}
		
		// Apply 4 operators: move left, move right, move up, move down.
		// Operator directions are based on the movement of the empty tile.

		// move left
		if (emptyCol > 0) {
			vector<vector<int>> consideredState = currentNode.state;
			consideredState[emptyRow][emptyCol] = consideredState[emptyRow][emptyCol-1];
			consideredState[emptyRow][emptyCol-1] = 0;

			// Enqueue the node only if it has not been seen before
			string newKey = puzzleToString(consideredState);
			if (repeatedStates.find(newKey) == repeatedStates.end()) {
				BoardStateNode newNode;
				newNode.state = consideredState;
				newNode.depth = currentDepth;
				nodesToExpand.push(newNode);
				repeatedStates.insert({newKey, true});
			}	
		}

		// move right
		if (emptyCol < initialState.size()-1) {
			vector<vector<int>> consideredState = currentNode.state;
			consideredState[emptyRow][emptyCol] = consideredState[emptyRow][emptyCol+1];
			consideredState[emptyRow][emptyCol+1] = 0;

			// Enqueue the node only if it has not been seen before
			string newKey = puzzleToString(consideredState);
			if (repeatedStates.find(newKey) == repeatedStates.end()) {
				BoardStateNode newNode;
				newNode.state = consideredState;
				newNode.depth = currentDepth;
				nodesToExpand.push(newNode);
				repeatedStates.insert({newKey, true});
			}	
		}

		// move up
		if (emptyRow > 0) {
			vector<vector<int>> consideredState = currentNode.state;
			consideredState[emptyRow][emptyCol] = consideredState[emptyRow-1][emptyCol];
			consideredState[emptyRow-1][emptyCol] = 0;

			// Enqueue the node only if it has not been seen before
			string newKey = puzzleToString(consideredState);
			if (repeatedStates.find(newKey) == repeatedStates.end()) {
				BoardStateNode newNode;
				newNode.state = consideredState;
				newNode.depth = currentDepth;
				nodesToExpand.push(newNode);
				repeatedStates.insert({newKey, true});
			}	
		}

		// move down
		if (emptyRow < initialState.size()-1) {
			vector<vector<int>> consideredState = currentNode.state;
			consideredState[emptyRow][emptyCol] = consideredState[emptyRow+1][emptyCol];
			consideredState[emptyRow+1][emptyCol] = 0;

			// Enqueue the node only if it has not been seen before
			string newKey = puzzleToString(consideredState);
			if (repeatedStates.find(newKey) == repeatedStates.end()) {
				BoardStateNode newNode;
				newNode.state = consideredState;
				newNode.depth = currentDepth;
				nodesToExpand.push(newNode);
				repeatedStates.insert({newKey, true});
			}	
		}

		if (nodesToExpand.size() > maxQueueSize)
			maxQueueSize = nodesToExpand.size();
	}

	// If this code is reached, there is no solution to the problem space given
	cout << "No solution exists!\n";
	cout << "Number of nodes expanded: " << numberNodesExpanded << endl;
	cout << "Max queue size: " << maxQueueSize;
}
