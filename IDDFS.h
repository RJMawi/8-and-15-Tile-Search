#ifndef IDDFS_H_ // #include guards
#define IDDFS_H_

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

Node goalFoundIDDFS (vector<Node> range, string goal) {
	for(auto it = range.begin(); it != range.end(); ++it) { //for the entire range of found nodes
		Node n = *it;
		//cout << "Comparinga " << n.board << " to " << goal << endl;
		if (n.board == goal) return n; //return the goal board node if found
	}
	//if goal is not found
	return Node("","");
}

void transferQueue(queue<Node> &a, queue<Node> &b, vector<Node> &c) {
	while (!a.empty()) {
		b.push(a.front());
		c.push_back(a.front());
		a.pop();
	}
}

//expandOptions expands downward from 
vector <Node> expandOptions(Node node, int depth, int &nodesExpanded) {
	vector <Node> reached;
	queue <Node> previousReached;
	reached.push_back(node);
	previousReached.push(node);
//	cout << "Aye" << endl;
	for (int i = 0; i < depth; i++) {
		queue <Node> currentReached;
		
		//while the queue of previous depth isn't empty, expand each node within it one more step
		while (!previousReached.empty()) {
			Node currentNode = previousReached.front();
			currentReached.push(currentNode);
			//remove the node as explored
			previousReached.pop();
			//expand a node, find its children nodes
			queue <Node> opt = expand(currentNode);
			nodesExpanded++;
			//cout << "Expanded " << currentNode.board << endl;
			//while there are still options to expand, empty the option queue into the currentReached queue
			while (!opt.empty()) { 
				currentReached.push(opt.front());
				opt.pop();
			}		
		}
		//now that the queue of the previous depth is empty and we have a current queue of reached nodes,  
		transferQueue(currentReached, previousReached, reached);
		while (!currentReached.empty()) {	//while the current Reached queue is still populated, add each instance to the reached vector
			reached.push_back(currentReached.front());
			currentReached.pop();
		}
	}
	//once each depth level has been explored
//	cout << "Depth of " << depth << " explored. Possible solutions found: ";
	//readVector(reached);
	return reached;
}

string IDDFS (string initialBoard, string endBoard) {
	cout << "Using IDDFS to find from " << initialBoard << " to " << endBoard << endl;
	//if the initial board is the goal state
	if (isGoal(initialBoard, endBoard)) {	//return the empty string of required moves
			cout << "Solution found. Number of moves: 0. Number of nodes expanded: 0" << endl;
			return "";
	}
	//start at 1 level of depth
	Node in(initialBoard, "");
	int it = 1;
	int nodesExpanded = 0; //tracks nodes expanded, starts at 0 for each loop
	while (it < 25) {
		vector <Node> range = expandOptions(in, it, nodesExpanded);
		Node goal = goalFoundIDDFS(range, endBoard);
		//if the goal has a move sequence. i.e. is a real solution
		if (goal.moves != "") {
			cout << "Solution found. Number of moves: " << goal.moves.length() << ". Depth expanded: " << it << ". Number of nodes expanded: " << nodesExpanded << endl;
			return goal.moves;
		}
		//reset the nodesExpanded since the number will be reincremented with next depth level
		nodesExpanded = 0;
		cout << "Depth " << it << " reached. No solutions found." << endl;
		it++;
	}
	//after a depth of 25, cancel out and return a failstate
	cout << "IDDFS failed, no solution found. Nodes expanded: " << nodesExpanded << endl; 
	return ""; 
}
#endif	//IDDFS_H_
