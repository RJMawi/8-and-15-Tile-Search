#ifndef BFS_H_ // #include guards
#define BFS_H_

#include <vector>
#include <queue>
#include <map>
#include "options.h"
using namespace std;

map <int, int> factorial = {
	{0, 1},
	{1, 1},
	{2, 2},
	{3, 6},
	{4, 24},
	{5, 120},
	{6, 720},
	{7, 5040},
	{8, 40320},
	{9, 362880}
};

int hashFunc9 (string board) {
    string b = board;
    int index = 0;
    vector <int> list;
    for (int i = 0; i < 8; i++) {
    //	cout << "boop" << endl;
    	int a = b[i] - 48; //get int value of character
    	int approx = a;
    	
    	for (vector<int>::iterator it = list.begin(); it != list.end(); ++it) {
    		if (*it < a) {
//    		    cout << *it << " is less than " << a << endl;   
    		    approx--;
    		}
    	//	cout << "index += " << approx << " * " << 8-i << "! = " << approx * factorial[8-i] << endl;
    	}
    	index+= approx * factorial[8-i];
//    	cout << "index now " << index << endl;
    	//cout << approx << " times " << factorial[8-i] << " is " << index << endl;
    	list.push_back(a);
    }
//    cout << "Index is " << index << endl;
    return index;
}


//			BREADTH-FIRST SEARCH
//BFS takes a base board and an empty string to start
//calculates available moves, and initiates each
//returns a solution string or a failure

string BFS_16(string initialBoard, string endBoard) {
	//create the Frontier as a queue of boards and move-sequences
	queue <Node> Frontier;
    Frontier.push(Node(initialBoard, "")); 
//create the reached list and add the initial board to it
	
	vector <string> reached;
	reached.push_back(initialBoard);
	//bool reached[362880];
	
	//reached[hashFunc9(initialBoard)] = true;
 
//initialize an int to track the number of Nodes expanded
	int nodesExpanded = 0;

//while the frontier contains board states to explore
	while (!Frontier.empty()) {
//		if (nodesExpanded%100==0) cout << "NODES: " << nodesExpanded << endl;
/*		if (nodesExpanded == 10000) {
			cout << "10000 nodes expanded, abort." << endl;
			break;
		}
*/		Node node (Frontier.front().board, Frontier.front().moves);
		Frontier.pop(); //removes front of Frontier after it has been taken as the current Node

		//cout << "Node is B:" << Node.board << ", M:" << Node.moves << endl;
		queue <Node> children = expand(node);
		nodesExpanded++;
		//now that all children are made from the available options, go through them one by one
		while (!children.empty()) {
			Node child = children.front();
			//if the child results in the endboard solution
			if (isGoal(child.board, endBoard)) {
				cout << "Solution found. Number of moves: " << child.moves.length() << ". Number of nodes expanded: " << nodesExpanded << endl;
				return child.moves;
			} 
			//if the child state hasn't been reached yet
			
			if (!isReached(reached, child.board)) {
			//if (!reached[hashFunc9(child.board)]) {
//			    cout << "Pushing child B: " << child.board << ", M: " << child.moves << endl;
			    Frontier.push(child);
			    reached.push_back(child.board);
			}
			//by this point, the current child is not a solution, and if it hasn't been reached yet, it's added to the frontier and reached. ergo:
			children.pop();
		}
		//once all children have been tested, the current node of the frontier is done
}
	//in case of failure. at this point, 
	//the frontier is empty and hasn't returned a solution string
	cout << "BFS failed, no solution found." << endl;
	return "";
}

string BFS_9(string initialBoard, string endBoard) {
	//create the Frontier as a queue of boards and move-sequences
	queue <Node> Frontier;
    Frontier.push(Node(initialBoard, "")); 
//create the reached list and add the initial board to it
	
	//vector <string> reached;
	//reached.push_back(initialBoard);
	bool reached[362880];
	
	reached[hashFunc9(initialBoard)] = true;
//    if (reached[hashFunc9(initialBoard)]) cout << "YO" << endl;
	
//initialize an int to track the number of Nodes expanded
	int nodesExpanded = 0;

//while the frontier contains board states to explore
	while (!Frontier.empty()) {
		Node node (Frontier.front().board, Frontier.front().moves);
		Frontier.pop(); //removes front of Frontier after it has been taken as the current Node

		//cout << "Node is B:" << Node.board << ", M:" << Node.moves << endl;
		queue <Node> children = expand(node);
		nodesExpanded++;
		//now that all children are made from the available options, go through them one by one
		while (!children.empty()) {
			Node child = children.front();
			//if the child results in the endboard solution
			if (isGoal(child.board, endBoard)) {
				cout << "Solution found. Number of moves: " << child.moves.length() << ". Number of nodes expanded: " << nodesExpanded << endl;
				return child.moves;
			} 
			//if the child state hasn't been reached yet
			
			//if (!isReached(reached, child.board)) {
			if (!reached[hashFunc9(child.board)]) {
//			    cout << "Pushing child B: " << child.board << ", M: " << child.moves << endl;
			    Frontier.push(child);
				reached[hashFunc9(child.board)] = true;
			    //reached.push_back(child.board);
			}
			//by this point, the current child is not a solution, and if it hasn't been reached yet, it's added to the frontier and reached. ergo:
			children.pop();
		}
		//once all children have been tested, the current node of the frontier is done
}
	//in case of failure. at this point, 
	//the frontier is empty and hasn't returned a solution string
	cout << "BFS failed, no solution found." << endl;
	return "";
}


string breadthFirstSearch(string initialBoard, string goalBoard) {
//in off chance the initial board is the goal state
	cout << "Using BFS to find from " << initialBoard << " to " << goalBoard << endl;
	if (isGoal(initialBoard, goalBoard)) {	//return the empty string of required moves
			cout << "Solution found. Number of moves: 0. Number of nodes expanded: 0" << endl;
			return "";
	}

	if (initialBoard.length()==9) return BFS_9(initialBoard, goalBoard);
	else if (initialBoard.length()==16) return BFS_16(initialBoard, goalBoard);
}
#endif	//BFS_H_
