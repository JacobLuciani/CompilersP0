//---------------------------------------------------------------------------
//File name: tree.c
//Author: Jacob Luciani
//Purpose: Contains implementation for a binary search tree's construction,
//         traversal (in/pre/postorder), and destruction.
//---------------------------------------------------------------------------

#include "tree.h"

//Loops through input from a file and adds each word to a tree that it creates and returns as a pointer
Node *buildTree(FILE *input) {
		
	char word[128];
	
	//allocate space for root of tree
	Node *tree;
	tree = (Node *) malloc(sizeof(Node));
		
	//loop through input file, adding each word found to the tree
	while (fscanf(input, "%s", word) != EOF) {
		addToTree(tree, word);

	}
		
	return tree;
}

//Searches the tree for proper place and adds single word to existing node or newly created node as needed
void addToTree(Node *tree, char *word) {
	
	//holds the first two letters of the input word, which decides what node it will be a part of
	char group[3];
	
	//compares word's group to the current node
	strncpy(group, word, 2);
	group[2] = '\0';
	
	//if the node has no existing group, it is a new node and is to be populated with the current word
	if (strcmp(tree->group, "") == 0) {
		//sets node's group based on input word
		strncpy(tree->group, word, 2);
	}
	
	int comparison;
	
	//compares the current node to the word
	comparison = strcmp(tree->group, group);
	
	//if the node is a match, add word to this node
	//otherwise, look for appropriate branch of tree
	if (comparison == 0) {
		addToNode(tree, word);
	} else if (comparison > 0) { //no match, word needs to go to the left of the current node
		
		//if there is no left branch, allocate a node on the heap and assign it as the left branch
		if (tree->leftBranch == NULL) {
			Node *leftBranch;
			leftBranch = (Node *) malloc(sizeof(Node));
			tree->leftBranch = leftBranch;
		}
		
		//recursive step - add the word to the left branch
		addToTree(tree->leftBranch, word);
		
	} else { //no match, word needs to go to the right of the current node
		
		//if there is no right branch, allocate a node on the heap and assign it as the right branch
		if (tree->rightBranch == NULL) {
			Node *rightBranch;
			rightBranch = (Node *) malloc(sizeof(Node));
			tree->rightBranch = rightBranch;
		}
		
		//recursive step - add the word to the right branch
		addToTree(tree->rightBranch, word);
		
	}
}

//Searches the tree for proper place and adds single word to existing node or newly created node as needed
void addToNode(Node *tree, char *word) {
	
	//convert input word to string
	string sWord(word);
	
	//search for word in node's elements to prevent duplication
	if (find(tree->members.begin(), tree->members.end(), word) == tree->members.end()) {
		//if no match is found, add word to current node
		tree->members.push_back(sWord);
	}
	
}

//adds word to a specific node, checking if it would be a duplicate
void printNode(Node *tree, int level, FILE *output) {
	
	//check level to prevent single space caused by %*c when * gets value 0
	if (level == 0) {
		fprintf(output, "Level %d: Group: %s Members:", level, tree->group);
	} else {
		//print out node info, indented two spaces per level on the tree
		fprintf(output, "%*cLevel %d: Group: %s Members:", level * 2, ' ', level, tree->group);
	}
	
	//print out all members of the node on the same line
	for (int i = 0; i < tree->members.size(); i++) {
		fprintf(output, " %s", tree->members[i].c_str());
	}
	fprintf(output, "\n");
	
	
}

//Traverses tree in order and prints information for each node in the tree to output file
void printInorder(Node *tree, int level, FILE *output) {
	//if the node exists, recursively print the node in order (left-root-right)
	if (tree != NULL) {
		printInorder(tree->leftBranch, level + 1, output);
		printNode(tree, level, output);
		printInorder(tree->rightBranch, level + 1, output);
	}
}

//Traverses tree in preorder and prints information for each node in the tree to output file
void printPreorder(Node *tree, int level, FILE *output) {
	//if the node exists, recursively print the node in preorder (root-left-right)
	if (tree != NULL) {
		printNode(tree, level, output);
		printPreorder(tree->leftBranch, level + 1, output);
		printPreorder(tree->rightBranch, level + 1, output);
	}
}

//Traverses tree in postorder and prints information for each node in the tree to output file
void printPostorder(Node *tree, int level, FILE *output) {
	//if the node exists, recursively print the node in postorder (left-right-root)
	if (tree != NULL) {
		printPostorder(tree->leftBranch, level + 1, output);
		printPostorder(tree->rightBranch, level + 1, output);
		printNode(tree, level, output);
	}
}

//Traverses tree and releases heap memory for nodes of tree
void freeTree(Node *tree) {
	if (tree != NULL) {
		freeTree(tree->leftBranch);
		freeTree(tree->rightBranch);
		free(tree);
	}
}