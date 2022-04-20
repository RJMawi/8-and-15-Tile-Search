#ifndef IDASTAR_H_ // #include guards
#define IDASTAR_H_

#include <vector>
#include <iostream>
#include <queue>
#include <limits>
#include "Astar.h"
using namespace std;

 //may be unnecessary, useful for troubleshooting
void readVector(vector <NodeH> r) {
     for (auto it = r.begin() ; it != r.end(); ++it) {
        NodeH n = *it;
		cout << n.board << ", ";
    } 
    cout << endl;
}



NodeH searchIDAStar (vector <NodeH> &path, string goalBoard, int bound, int heuristic(string, string), int &t, int &expanded) {
	NodeH node = path.back();
//	cout << "Node is " << node.board << ", " << node.moves << ", " << node.heuristic << endl;
	if (node.heuristic > bound) {
		t = node.heuristic; 
		
		//return failure node
		return NodeH("No luck", "");	
	}
	//if the board is the best
	if (isGoal(node.board, goalBoard)) return node;
	int min = numeric_limits<int>::max();
	queue <NodeH> children = expand(node);
	expanded++;
	//while there's still children to 
	while (!children.empty()) {
		NodeH child = children.front();
		child.heuristic = child.moves.length() + heuristic(child.board, goalBoard);
		if (!isReached(path, child.board)) {
			path.push_back(child);
			int tee;
			NodeH found = searchIDAStar(path, goalBoard, bound, heuristic, tee, expanded);
			if (found.board != "No luck") return found;
			if (tee < min) min = tee;
			path.pop_back();
		}
		children.pop();	
	}
	//return min
	t = min; 
	//return failure node
	return NodeH("No luck", "");
}



string IDAStarSearch (string initialBoard, string goalBoard, int heuristic (string, string)) {
	cout << "Using Iterative Deepening A* to find from " << initialBoard << " to " << goalBoard << endl;
	if (isGoal(initialBoard, goalBoard)) {	//return the empty string of required moves
		cout << "Solution found. Number of moves: 0. Number of nodes expanded: 0" << endl;
		return "";
	}
	//cout << "Original board heuristic is 0+ " << heuristic(initialBoard, "") << endl;
	int bound = heuristic(initialBoard, goalBoard);
	vector <NodeH> path;
	path.push_back(NodeH(initialBoard, "", bound));
//	cout << "Original bound is " << bound << endl;
	bool i = true;
	int j = 0;
	int nodesExpanded = 0;
	while (i==true) {
		int t;
		NodeH found = searchIDAStar(path, goalBoard, bound, heuristic, t, nodesExpanded);
		if (found.board == "No luck") { //if that iteration couldn't complete
			if (t == numeric_limits<int>::max()) {		//if min from search wasn't changed, fail state, nothing further to search for
				cout << "A* failed, no solution found." << endl; 
				return "";	
			} else {	//if this iteration failed but can still work forward with new threshold
				bound = t;
//				cout << "New bound is " << bound << endl;
//				readVector(path);
				//cout << "Nodes expanded: " << nodesExpanded << endl;
				//if (nodesExpanded > 1000) i = false;
//				cin >> j;
//				if (j != 0) i = false;
			}
		} else {	//solution found and returned as node
			cout << "Solution found. Number of moves: " << found.moves.length() << ". Number of nodes expanded: " << nodesExpanded << endl;
			return found.moves;
		}
	}
	
}
/*

bound := h(root)
    path := [root]
    loop
        t := search(path, 0, bound)
        if t = FOUND then return (path, bound)
        if t = 8 then return NOT_FOUND
        bound := t
    end loop
end procedure

function search(path, g, bound)
    node := path.last
    f := g + h(node)
    if f > bound then return f
    if is_goal(node) then return FOUND
    min := 8
    for succ in successors(node) do
        if succ not in path then
            path.push(succ)
            t := search(path, g + cost(node, succ), bound)
            if t = FOUND then return FOUND
            if t < min then min := t
            path.pop()
        end if
    end for
    return min
end function

*/
/*

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
*/
#endif	//IDASTAR_H_
