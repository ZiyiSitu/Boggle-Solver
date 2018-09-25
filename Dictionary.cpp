/*
	Ziyi Situ
	Net ID: tz4752
	11/23/2016
	CS 3240
	File name: Dictionary.cpp
	Assignment 3 - Boggle Solver
*/

#include "Dictionary.h"

Dictionary::Dictionary() {
	numWords = 0;
	root = new Node;
	for (int i = 0; i < SIZE; i++) {
		root->next[i] = NULL;
		root->exist[i] = false;
	}
}






Dictionary::Dictionary(ifstream &file) {
	string line;  // to read the words from file line by line
	
	numWords = 0; 
	root = new Node;
	for (int i = 0; i < SIZE; i++) {
		root->next[i] = NULL; 
		root->exist[i] = false;		
	}
	file.open("dictionary.txt");
	while (getline(file, line)) {
		if (line != "")
			addWord(line);				
	}
}






void Dictionary::addWord(string word) {
	Node *currNode = root;
	int id;

	for (int index = 0; index < word.size(); index++) {
		id = word[index] - 'a';  // represents a character
		if (currNode->next[id] == NULL) {			
			currNode->next[id] = new Node;
			
			for (int i = 0; i < SIZE; i++) {
				currNode->next[id]->next[i] = NULL;
				currNode->next[id]->exist[i] = false;
			}
		}

		currNode = currNode->next[id]; 
	}
	currNode->exist[id] = true;
	numWords++;
}






bool Dictionary::isWord(string word) {
	Node *currNode = root;
	int id;
	bool result = false;

	for (int index = 0; index < word.size(); index++) {
		id = word[index] - 'a';
		if (currNode->next[id] == NULL)
			return result;
		else
			currNode = currNode->next[id];
	}
	if (currNode->exist[id] == true)
		result = true;
	return result;
}






bool Dictionary::isPrefix(string word) {
	Node *currNode = root;
	int id;
	bool result = false;

	for (int index = 0; index < word.size(); index++) {
		id = word[index] - 'a';
		if (currNode->next[id] == NULL)
			return result;
		else
			currNode = currNode->next[id];
	}
	return result = true;
}






int Dictionary::wordCount() {
	return numWords;
}
