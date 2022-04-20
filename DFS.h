#ifndef DFS_H_ // #include guards
#define DFS_H_

//#include <vector>
//#include <iostream>
//#include <queue>
//#include "BFS.h"
using namespace std;

//since the board states are recursive and endless, we are using a depth-limited search, starting at 20 and increasing to 25

string depthFirstSearch(string initialBoard, string goalBoard, int baseDepth, int finalDepth) {
	cout << "Using DFS to find from " << initialBoard << " to " << goalBoard << endl;

//in off chance the initial board is the goal state
	if (isGoal(initialBoard, goalBoard)) {	//return the empty string of required moves
			cout << "Solution found. Number of moves: 0. Number of nodes expanded: 0" << endl;
			return "";
	}
//initialize depth iterator as base depth
	int depth = baseDepth;
	int nodesExpanded = 0; 
//create while loop to cover depths
	while (depth <= finalDepth) {
//		nodesExpanded = 0;
//initialize Frontier of unexplored nodes
		vector <Node> Frontier;
//frontier in DFS is treated as a stack, add initial board
		Frontier.push_back(Node(initialBoard, ""));
//tracks nodes expanded, starts at 0 for each loop
		//nodesExpanded = 0; 

		while (!Frontier.empty()) {	//while there are still nodes to expand
			Node current = Frontier.back();
//if the current node is the goal state, return a success
			if (current.board == goalBoard) {
				cout << "Solution found. Number of moves: " << current.moves.length() << ". Number of nodes expanded: " << nodesExpanded << endl;
				return current.moves;
			}
//otherwise, pop back of the Frontier to remove this node from it
			Frontier.pop_back(); //removes end of Frontier after it has been taken as the current Node
//create the list of the current node's children
			queue <Node> children = expand(current);
			nodesExpanded++;
//for each child
			while (!children.empty()) {
				Node child = children.front();
//if this child's depth hasn't exceeded the depth limit, add that child to the stack
//if we tracked whether the node had already been explored, that system alone would be insufficient (since multiple routes can reach each node, potentially in shorter lengths)
//therefore, we don't track and instead merely track depth
				if (child.moves.length() <= depth) {
					Frontier.push_back(child);
				}
				children.pop();
			}
			
//			cin >> o;
		}
		//no solutions found so extend depth possible
		depth++;
	}
	//after depth has been explored, cancel out and return a failstate
	cout << "DFS failed, no solution found within " << finalDepth << " steps. Nodes expanded: " << nodesExpanded << endl; 
	return ""; 
}


#endif	//DFS_H_
