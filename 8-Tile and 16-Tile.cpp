//8-Tile and 16-Tile
#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <cmath>
#include "Node.h"
#include "options.h"
#include "BFS.h"
#include "DFS.h"
#include "IDDFS.h"
#include "Astar.h"
#include "IDAstar.h"
using namespace std;

 //may be unnecessary, useful for troubleshooting
void readVector(vector <Node> r) {
     for (auto it = r.begin() ; it != r.end(); ++it) {
        Node n = *it;
		cout << n.board << ", ";
    } 
    cout << endl;
}



int main () {
	string boards9[] = { 
	"160273485", 
	"462301587", 
	"821574360", 
	"840156372", 
	"530478126", 
	"068314257", 
	"453207186", 
	"128307645", 
	"035684712", 
	"684317025", 
	"028514637", 
	"618273540", 
	"042385671", 
	"420385716",  
	"054672813", 
	"314572680", 
	"637218045", 
	"430621875", 
	"158274036", 
	"130458726"};

	string boards16e[] = {"16235A749C08DEBF", "0634217859ABDEFC", "012456379BC8DAEF", "51246A38097BDEFC", "12345678D9CFEBA0"};
	string boards16h[] = {"71A92CE03DB4658F", "02348697DF5A1EBC", "39A1D0EC7BF86452", "EAB480FC19D56237", "7DB13C52F46E80A9"};

    string goal9 = "123456780";
    string goal16 = "123456789ABCDEF0";

//modify here to set goal and initial boards
    string start = boards9[2];
    string goal = goal9;
    	
//	    cout << breadthFirstSearch(start, goal) << endl << endl;
		cout << depthFirstSearch(start, goal, 28, 28) << endl << endl;	
//		cout << IDDFS(start, goal) << endl << endl; 
//		cout << aStarSearch(start, goal, manhattanDistanceHeuristic) << endl << endl;
//		cout << aStarSearch(start, goal, outOfPlaceHeuristic) << endl << endl;
//		cout << IDAStarSearch(start, goal, manhattanDistanceHeuristic) << endl << endl;
//		cout << IDAStarSearch(start, goal, outOfPlaceHeuristic) << endl << endl;

    return 0;
}
