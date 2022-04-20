#ifndef OPTIONS_8_15_ // #include guards
#define OPTIONS_8_15_

#include <vector>
#include <queue>
#include <map>
#include "Node.h"
#include <iostream>
using namespace std;



//Code Atlas, where I keep all my maps//

//a map, used as a lookup table to determine immediately available moves for a 9-Board
map<int, vector<string>> options9Board = {
    {0, {"R","D"} },
    {1, {"R","L","D"} },
    {2, {"L","D"} },
    {3, {"U","R","D"}},
    {4, {"U","R","L","D"} },
    {5, {"U","L","D"} },
    {6, {"U","R"}},
    {7, {"U","R","L"} },
    {8, {"U","L"} }
};

//a map, same as above, for a 16-Board
map<int, vector<string>> options16Board = {
    {0, {"R","D"} },
    {1, {"R","L","D"} },
    {2, {"R","L","D"} },
    {3, {"L","D"} },

    {4, {"U","R","D"}},
    {5, {"U","R","L","D"} },
    {6, {"U","R","L","D"} },
    {7, {"U","L","D"} },

    {8, {"U","R","D"}},
    {9, {"U","R","L","D"} },
    {10, {"U","R","L","D"} },
    {11, {"U","L","D"} },

    {12, {"U","R"}},
    {13, {"U","R","L"} },
    {14, {"U","R","L"} },
    {15, {"U","L"} }
};

//a map, used to determine position of swapped time based on move
map<string, int> tileSwap9Board = {
    { "U", -3 },
    { "R", 1 },
    { "L", -1 },
    { "D", 3}
};

//a map, used to determine position of swapped time based on move
map<string, int> tileSwap16Board = {
    { "U", -4 },
    { "R", 1 },
    { "L", -1 },
    { "D", 4}
};

//a map, used to quickly determine the opposite move from a previous move, to eliminate that move option
map<string, string> opposites = {
    { "U", "D" },
    { "R", "L" },
    { "L", "R" },
    { "D", "U"}
};



//determines if a given board of a given size matches the goal state given
bool isGoal (string board, string solution) {
	if(board == solution) return true;
	else return false;
}

//a function to locate the zero in the board of a given size to determine actions
int findZero (string board) {
	for (int i = 0; i < board.length(); i++) {
		if (board[i] == '0') return i;
	}
	//if no 0 is found, throw error

	return -1;
}

int tileSwap(string board, string it) {
	if (board.length() == 9) return tileSwap9Board[it];
	else if (board.length() == 16) return tileSwap16Board[it];
}

void swapTiles (string &board, int zero, int swap) {
	char temp = board[swap];
	board[swap] = board[zero];
	board[zero] = temp; 
}

string childCheck (string board, int zero, int swap) {
	string newboard = board;
	swapTiles(newboard, zero, swap);
	return newboard;
}

bool isReached (vector <string> reached, string board) {
	for (vector<string>::iterator it = reached.begin() ; it != reached.end(); ++it) {
		if (*it == board) return true;
	}
	return false;
}

bool isReached (vector <NodeH> reached, string board) {
	for (auto it = reached.begin() ; it != reached.end(); ++it) {
		NodeH n = *it;
		if (n.board == board) return true;
	}
	return false;
}

//takes an initial board state and applies the move sequence upon it, returning the resulting board state
string solutionTest(string initialBoard, string moveSequence) {//take an input string and apply the moveSequence to determine the final Board State
	string endBoard = initialBoard;
	for (string::iterator it = moveSequence.begin(); it!=moveSequence.end(); ++it) {
		int zero = findZero(endBoard);
//		cout << "zero is at " << zero << endl;
        string mod; 
        mod += *it;
		int move = zero + tileSwap(endBoard, mod);
//		cout << "Moving " << *it << " to " << move << endl;
		swapTiles(endBoard, zero, move);
	}
	return endBoard;
}

void removeOption (vector <string> &options, string rem) {
    for (vector<string>::iterator it = options.begin() ; it != options.end(); ++it) {
        if (*it == rem) {
            options.erase(it);
            break; //options only occur once, so this function ends as soon as necessary
        }
    }
}

//given the position of zero and the previous options, this function returns a list of possible options [U,D,L,R only]
vector <string> findOptions (Node node) {
		//get zero's position
		int zero = findZero(node.board);
//		cout << "zero is at " << zero << endl;
    vector <string> options;
		//get vector of options
		if (node.board.length() == 9)
			options = options9Board[zero];
		else if (node.board.length() == 16)
			options = options16Board[zero];

//		cout << "initial options are ";
//      readVector(options);
//		cout << endl;

		//remove opposite from options if opposite isn't null
		if (node.moves != "") { //if the moves list isn't empty, i.e. a previous move exists
		    string back;
		    back += node.moves.back();
			removeOption(options, opposites[back]);
		}
		return options;
}

//given the position of zero and the previous options, this function returns a list of possible options [U,D,L,R only]
vector <string> findOptions (NodeH node) {
		//get zero's position
		int zero = findZero(node.board);
//		cout << "zero is at " << zero << endl;
    vector <string> options;
		//get vector of options
		if (node.board.length() == 9)
			options = options9Board[zero];
		else if (node.board.length() == 16)
			options = options16Board[zero];

//		cout << "initial options are ";
//      readVector(options);
//		cout << endl;

		//remove opposite from options if opposite isn't null
		if (node.moves != "") { //if the moves list isn't empty, i.e. a previous move exists
		    string back;
		    back += node.moves.back();
			removeOption(options, opposites[back]);
		}
		return options;
}



//takes a node and returns the available children
queue <Node> expand (Node node) {
	vector <string> opt = findOptions(node);
	queue <Node> children;
		
//find the board's zero, to be used for each option
	int zero = findZero(node.board);

//add children while removing options
		while (!opt.empty()) {
		//find the location to be moved to 
		int move = zero + tileSwap(node.board, opt.front());

//add child option to children
		children.push(Node(childCheck(node.board, zero, move), node.moves + opt.front()));
		opt.erase(opt.begin());		//delete first element 
	}
	return children;
}

queue <NodeH> expand (NodeH node) {
	vector <string> opt = findOptions(node);
	queue <NodeH> children;
		
//find the board's zero, to be used for each option
	int zero = findZero(node.board);

//add children while removing options
	while (!opt.empty()) {
		//find the location to be moved to 
		int move = zero + tileSwap(node.board, opt.front());

//add child option to children
		children.push(NodeH(childCheck(node.board, zero, move), node.moves + opt.front()));
		opt.erase(opt.begin());		//delete first element 
	}
	return children;
}

#endif // OPTIONS_8_15_
