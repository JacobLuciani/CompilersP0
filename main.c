//---------------------------------------------------------------------------
//File name: main.c
//Author: Jacob Luciani
//Purpose: Processes input into a binary search tree (BST), prints out 
//         results of three traversals of BST (in/pre/postorder)
//---------------------------------------------------------------------------

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "node.h"

using namespace std;

//Takes in command line arguments and determines source of information, to be used for naming output and processing input
char *getBaseName(int argc, char *argv[]);

//Takes in input source base name and returns working file pointer associated with data
//handles and converges different program states/types of input
FILE *processArgs(char *baseName);

//prompts user for string input to be put in temp file for processing
void getInput(FILE *input);

//process command line arguments and return a pointer to a file containing data to be turned into a BST
FILE *processArgs(int argc, char *argv[]);

int main(int argc, char *argv[]) {
	
	//holds the "base" name related to the source of input, to be used for output naming
	char *baseName;
	baseName = getBaseName(argc, argv);

	//File pointers to input and output files
	FILE *input;
	FILE *outputInorder;
	FILE *outputPreorder;
	FILE *outputPostorder;
	
	input = processArgs(baseName);
	
	//variable holds the different output file names while they are being opened
	char *outputFileName;
	outputFileName = (char *) malloc(sizeof(baseName) + 10);
	
	//Opens output files for each or in/pre/postorder using the base name and standardized extensions
	sprintf(outputFileName, "%s.inorder%c", baseName, '\0');
	outputInorder = fopen(outputFileName, "w");
	
	sprintf(outputFileName, "%s.preorder%c", baseName, '\0');
	outputPreorder = fopen(outputFileName, "w");
	
	sprintf(outputFileName, "%s.postorder%c", baseName, '\0');
	outputPostorder = fopen(outputFileName, "w");
		
	free(outputFileName);
	
	//create and build tree from input in file
	Node *binaryTree;
	binaryTree = buildTree(input);
	
	//Print formatted tree traversals to files
	printf("Printing inorder to %s.inorder\n", baseName);
	printInorder(binaryTree, 0, outputInorder);
	
	printf("Printing preorder to %s.preorder\n", baseName);
	printPreorder(binaryTree, 0, outputPreorder);
	
	printf("Printing postorder to %s.postorder\n", baseName);
	printPostorder(binaryTree, 0, outputPostorder);
	
	//clean up resources before termination
	fclose(input);
	fclose(outputInorder);
	fclose(outputPreorder);
	fclose(outputPostorder);
	freeTree(binaryTree);
	free(baseName);
	
	return EXIT_SUCCESS;
}

//Takes in command line arguments and determines the base name to be used for the output based on the data source
//If input is from files, output files are named after the file, keyboard/piped input results in "output" for file names
char *getBaseName(int argc, char *argv[]) {
	
	char *fileName;
	
	if (argc > 1) { //file passed as argument
		
		//allocated space for filename to be stored
		fileName = (char *) malloc(sizeof(argv[1]));
		
		sprintf(fileName, "%s%c", argv[1], '\0');
		
	} else { //no file passed, keyboard/piped input
		fileName = (char *) malloc(7);
		
		sprintf(fileName, "output%c", '\0');
	}
	
	return fileName;
}

//Takes in input source base name and returns working file pointer associated with data
//handles and converges different program states/types of input
FILE *processArgs(char *baseName) {
	
	char *inputFileName;
	FILE *input;
	
	//if the base name is output, data is being passed via keyboard
	//otherwise, it is a file
	if (strcmp(baseName, "output") != 0) { //file passed as argument
		
		//allocated space for filename to be stored
		inputFileName = (char *) malloc(sizeof(baseName) + 8);
		
		//add implicit extension
		sprintf(inputFileName, "%s.sp2020", baseName);

		//open file pointer to given filename
		input = fopen(inputFileName, "r");
		
		//check if file could be opened, if not print error message and terminate
		if (input == NULL) {
			printf("Input file name %s could not be opened. Terminating.\n", inputFileName);
			
			free(inputFileName);
			exit(1);
		}
				
		//free variable storing file name with extension
		free(inputFileName);	
	} else {
		//check if data has been piped in from a file
		//if not, open file and request input from user to be put in file
		//otherwise, set input to stdin and move on
		if (isatty(STDIN_FILENO)) { //input to be typed in by keyboard
			input = fopen("tempInput.sp2020", "w+");
			getInput(input);
		} else { //input piped in
			input = stdin;
		}
	}
	
	
	//check if input file has any content, error if none
	char word[128];
	
	if (fscanf(input, "%s", word) == EOF) {
		printf("Empty input file. Terminating.\n");
		exit(1);
	}
	
	//return to start of file after checking for content and return file pointer
	fseek(input, 0, SEEK_SET);
	return input;
}

//prompts user for input and stores it in file given by input pointer
void getInput(FILE *input) {
	
	printf("Input needed. Please enter input strings, enter '!' to end input: \n");
	
	//variable holds each "word" of input individually
	char word[128];
	
	//clears out word to allow do-while loop to print before reading the next word
	sprintf(word, "%c", '\0');
	
	//prints then reads next word of input from user
	//allows the loop to stop before writing the simulated EOF to the file pointer
	do {
		fprintf(input, "%s ", word);
		scanf("%s", word);
	} while (strcmp(word, "!") != 0);
		
	//return file pointer to start of file
	fseek(input, 0, SEEK_SET);
}