#ifndef NODE_H_ // #include guards
#define NODE_H_

#include <iostream>
using namespace std;

struct Node {
	public:
	string board;
	string moves;

	Node (string b, string m) {
		board = b;
		moves = m;
	}
};

//a second node useful for A* with any heuristic measurement
struct NodeH {
	public:
	string board;	//the actual board string
	string moves;	//the string of movements to reach that board
	int heuristic;	//gives the approximate value from this board to the goal state

	NodeH (string b, string m, int h = 50) { //unset heuristics become set very high as to not be accidentally passed if uninitialized from 0
		board = b;
		moves = m;
		heuristic = h;
	}
};
#endif //8_15_OPTIONS_ _
