#ifndef ASTAR_H_ // #include guards
#define ASTAR_H_

#include <vector>
#include <iostream>
#include <queue>
#include "Node.h"
using namespace std;

struct MinHeap {
	public:
		vector <NodeH>* heap;
		int size;
		
	MinHeap() {
		heap = new vector<NodeH>;
		size = 0;
	}
	
	void readVector() {
		cout << "Heap is ";
    	for (auto it = heap->begin() ; it != heap->end(); ++it) {
       		NodeH n = *it;
			cout << n.board << ", ";
    	} 
    	cout << endl;
	}
	
	MinHeap(NodeH node) {
		heap = new vector<NodeH>;
		heap->push_back(node);
		size=1;
	}
	
	bool isEmpty () {
		if (size == 0) return true;
		else return false;
	}
	
	void push (NodeH node) {
		heap->push_back(node); 	//add new node to the heap
//		cout << "Pushing " << node.board << endl;
		size++;
//		cout << "Heap is size " << size << endl;
		int i = size-1;
		while (i >= 1 && heap->at(i).heuristic < heap->at((i-1)/2).heuristic) {	//while the new node has a lower heuristic than its parent and while it isn't the top
//			cout << "Swapping " << heap->at(i).board << " with " << heap->at((i-1)/2).board << endl;
			heap->at(i) = heap->at((i-1)/2);	//change last node to parent
			heap->at((i-1)/2) = node;		//replace parent with new node
			i /= 2;		//halve i to track new node upwards
			if (i%2==0) i--; //if the new i is an even number it needs to be reduced to reach its proper parent
		}
//		readVector();
	}
	
	NodeH* heapFind (string board) {
		int i = 0;
		while (i < size) {
			if (heap->at(i).board == board) return &heap->at(i);
			i++;
		}
		NodeH* n = new NodeH("", "");
		return n;
	}
	
	NodeH pop () {
		NodeH node = heap->front();		//save the root
		heap->front() = heap->at(size-1);	//replace the root with the last element
		//heap->at(size-1) = node;			//replace last element with original root
				heap -> pop_back();		//delete original root
//		cout << "popping " << node.board << endl;
//		readVector();
		size--;					//decrement size
		int i = 0;
		while (i < size/2) {	//while there is still more heap left to check on the newroot
			int child1 = 2*i +1;
			int child2 = 2*i +2;
			int smallestChild;
			if (child2 >= size) {	//prevent out-of-range
				if (child1 >= size) break;		//if child2 is also out
				else smallestChild = child1;
			} else if (heap->at(child1).heuristic <= heap->at(child2).heuristic) smallestChild = child1;
			else smallestChild = child2;
			if (heap->at(i).heuristic > heap->at(smallestChild).heuristic) { //if the smallest child is still less than the newroot parent node
				NodeH parent = heap->at(i);
				heap->at(i) = heap->at(smallestChild);
				heap->at(smallestChild) = parent;
				i = smallestChild;		//set new i at the point of the sunken newroot's index
			}
			else break; //the bottom node has no lower it needs to sink
		}
		return node;			//return root
	}
	
};



//the Out-of-Place Heuristic takes two boards and returns the number of tiles out of place.
int outOfPlaceHeuristic (string initialBoard, string goalBoard) {
	int sum = 0;
	for (int i = 0; i < initialBoard.length(); i++) {
		if (initialBoard[i] != goalBoard[i]) sum++;
	}
	return sum;
}

int getManhattanDistance (int start, int end, int size) {
	int distance = abs(start-end);
//	cout << "Distance between " << start << " and " << end << " is " << distance << endl;
	int sum = 0;
	int side;
	if (size == 9) side = 3;
	else if (size == 16) side = 4;
	sum += (distance % side);
	sum += (distance / side);
//	cout << "returning " << sum << endl;
	return sum;	
}

int manhattanDistanceHeuristic (string initialBoard, string goalBoard) {
	int sum = 0;
	for (int i = 0; i < initialBoard.length(); i++) {
		for (int j = 0; j < goalBoard.length(); j++) {
			if (goalBoard[j] == initialBoard[i]) { //where initialBoard's tile belongs
//				cout << initialBoard[i] << " at " << i << " is " << goalBoard[j] << " at " << j << endl;
				sum += getManhattanDistance(i, j, initialBoard.length());
				j = initialBoard.length();
			}			
		}
	}
	return sum;
}

string aStarSearch (string initialBoard, string goalBoard, int heuristic (string, string)) {
	//step 0: make sure the two boards given are different
	cout << "Using A* to find from " << initialBoard << " to " << goalBoard << endl;
	if (isGoal(initialBoard, goalBoard)) {	//return the empty string of required moves
		cout << "Solution found. Number of moves: 0. Number of nodes expanded: 0" << endl;
		return "";
	}
	//step 1: initialize heap
	MinHeap open(NodeH(initialBoard, "", heuristic(initialBoard, goalBoard)));	//the heuristic function determines the value of pursuing the particular action));		//initializes the minheap for tracking most optimal moves to process.
//	cout << "Heap created." << endl;
	//step 2. initialize the closed list
	map<string, string> closed;		//keeps track of the g(n) path to reach a given board with a given move sequence
//	gScore.insert(pair<string, NodeH>(initialBoard, );		//adds the initial board
	int nodesExpanded;
	//step 3: while the heap is not empty
	while (!open.isEmpty()) {
		//3a. Take the node with the lowest cost so far (top of heap) and pop it
		NodeH current = open.pop();
//		cout << "Examining node " << current.board << ", " << current.moves << ", " << current.heuristic << endl;
		nodesExpanded++;
//		cout << "Heap after pop: ";
//		open.readVector();
//		cout << endl;
		//3b. Generate current successors/children nodes.
		queue <NodeH> children = expand(current);
		//now that all children are made from the available options, go through them one by one
		//3c. For each child:
		while (!children.empty()) {
			NodeH child = children.front();	//take the standard node given and use its 
			//remove child from the list to avoid loop
			children.pop();
//			cout << "Examining child " << child.board << ", " << child.moves << endl;
			//3c i. If child is goal, stop search
			if (isGoal(child.board, goalBoard)) {
				cout << "Solution found. Number of moves: " << child.moves.length() << ". Number of nodes expanded: " << nodesExpanded << endl;
				return child.moves;
			} 
			//3c ii. Calculate heuristic value
			child.heuristic = child.moves.length() + heuristic(child.board, goalBoard);	//the heuristic function determines the value of pursuing the particular action
//			cout << "Child " << child.board << ", " << child.moves << ", " << child.heuristic << endl;
			NodeH* twin = open.heapFind(child.board);		//finds if the same node exists on the open list. if not, the node returned has empty values
			bool skip = false;
			//3c iii. skip child if it's slower than the same node on the open list
			if (twin->board == child.board && (twin->moves.length() <= child.moves.length())) skip = true;	//if the node is the same (checking if the set node isn't empty first)
			if (closed[child.board] != "") {		//since the map initializes this board upon lookup if it doesn't exist, this determines if it's a valid moveset within the closed list 
				//3c iv. if the child's node has already been reached with a shorter path, don't add it to the open list
				if (closed[child.board].length() <= child.moves.length()) {
					
					skip = true;				
				} //else cout << closed[child.board] << " of length " << closed[child.board].length() << " in closed, is greater than " << child.moves.length() << endl;
			} else if (child.board == initialBoard) skip = true;//if the closed list value returned is an empty string of moves, then if it IS the initial board, skipping is necessary (to avoid pushing a loop sequence)
			
			if (!skip) {	open.push(child);	//then, if the node is both shorter than any closed list node of the same board, or shorter than any existing node in the open list, add the child to the open list
//			cout << "Adding child to open: " << child.board << ", " << child.moves << ", " << child.heuristic << endl << endl;

			}
		}
		//d. add current node to the closed list		
		closed[current.board] = current.moves;
//		cout << "Adding node to closed: " << current.board << ", " << current.moves << ", " << current.heuristic << endl;
		int oh;
	//	cin >> oh;
	}
	//if the heap is empty without a solution, the search has failed
	cout << "A* failed, no solution found." << endl;
	return "";	
}
#endif	//ASTAR_H_
