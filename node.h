//---------------------------------------------------------------------------
//File name: node
//Author: Jacob Luciani
//Purpose: Header file for node struct used to build a binary search tree
//         based on the first two letters of a word
//---------------------------------------------------------------------------

#ifndef NODE_HEADER
#define NODE_HEADER

#include <vector>
#include <string>

//c++ used for access to vectors
using namespace std;

typedef struct Node {
	
	//pointers to branches of the BST
	struct Node *leftBranch;
	struct Node *rightBranch;
	
	//group is the first two letters, determines which members belong to this node
	char group[2];
	
	//vector holds words that fall under this node
	vector<string> members;
} Node;

#endif