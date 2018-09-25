/*
	Ziyi Situ
	Net ID: tz4752
	11/23/2016
	CS 3240
	File name: Dictionary.h
	Assignment 3 - Boggle Solver

	The Dictionary class can be used to represent as a dictionary to add
	words into a Dictionary object and look up words from it.

	Dictionary();
		post: A Dictionary with numWords equal to 0 and a Node including 
		a Node pointers array all elements pointing to NULL, and a boolean
		array all elements set 0.

	Dictionary(ifstream &file);
		pre: The ifstream object containing words is ready for reading.
		post: The call Dictionary object uses the addWord method to add 
		words to the dictionary.

	void addWord(string word);
		pre: A string object is copied into function as a parameter.
		post: The call Dictionary object adds the word to the Dictionary.

	bool isWord(string word);
		pre: A string object is copied into function as a parameter.
		post: Returns true if the the string object is on the Dictionary,
		otherwise false.

	bool isPrefix(string word);
		pre: A string object is copied into function as a parameter.
		post: Returns true if the the string object is on the Dictionary,
		otherwise false.

	int wordCount();
		post: Returns the words on the Dictionary.
*/

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int const SIZE = 26;

struct Node {
	// pointers to the Nodes representing the 26 characters
	Node *next[SIZE];
	// indicates if the path from to this Node is a word
	bool exist[SIZE];
};

class Dictionary
{
public:
	Dictionary();
	Dictionary(ifstream &file);
	void addWord(string word);
	bool isWord(string word);
	bool isPrefix(string word);
	int wordCount();

private:
	Node* root;
	int numWords;
};
#endif // !DICTIONARY_H
