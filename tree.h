//---------------------------------------------------------------------------
//File name: tree.h
//Author: Jacob Luciani
//Purpose: Header file for a binary search tree, function declarations for
//         construction, traversal (in/pre/postorder), and destruction.
//---------------------------------------------------------------------------

#ifndef TREE_HEADER
#define TREE_HEADER

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <algorithm>

#include "node.h"

//Loops through input from a file and adds each word to a tree that it creates and returns as a pointer
Node *buildTree(FILE *input);

//Searches the tree for proper place and adds single word to existing node or newly created node as needed
void addToTree(Node *tree, char *word);

//adds word to a specific node, checking if it would be a duplicate
void addToNode(Node *tree, char *word);

//Prints formatted info about one node in the tree with indentation according to "level"
void printNode(Node *tree, int level, FILE *output);

//Print functions print tree to output file using in/pre/postorder and prints information for each node in the tree
void printInorder(Node *tree, int level, FILE *output);
void printPreorder(Node *tree, int level, FILE *output);
void printPostorder(Node *tree, int level, FILE *output);

//Traverses tree and releases heap memory for nodes of tree
void freeTree(Node *tree);

#endif