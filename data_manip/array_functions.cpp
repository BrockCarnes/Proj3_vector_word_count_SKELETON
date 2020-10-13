/*
 * array_functions.cpp
 *
 *  Created on: October 10, 2020
 *      Author: Brockton
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "../includes/utilities.h"
#include "../includes/array_functions.h"

	void KP::clear(std::vector<constants::entry>  &entries){
		entries.clear();
	}


	//how many unique words are in the vector
	int KP::getSize(std::vector<constants::entry>  &entries){
		return entries.size();
	}

	//get data at a particular location, if i>size() then get the last value in the vector
	//(this is lazy, should throw an exception instead)
	std::string KP::getWordAt(std::vector<constants::entry>  &entries, int i){
		int n = entries.size();
		//Taking care of problem instance without exception?
		if (i > n){
			return entries[n-1].word;
		}
		else{
			return entries[i].word;
		}
	}

	int KP::getNumbOccurAt(std::vector<constants::entry>  &entries,int i){
		return entries[i].number_occurences;
	}

	/*loop through whole file, one line at a time
	 * call processLine on each line from the file
	 * returns false: myfstream is not open
	 *         true: otherwise*/
	bool KP::processFile(std::vector<constants::entry>  &entries,std::fstream &myfstream){
		//Problem inst
		if(!myfstream.is_open()){
			return false;
		}
		//Question 53 Piazza
		std::string line;
		while(getline(myfstream, line)) {
			KP::processLine(entries, line); //Solution to 53
		}

		return true;
	}

	/*take 1 line and extract all the tokens from it
	feed each token to processToken for recording*/
	//GIVEN CODE
	void KP::processLine(std::vector<constants::entry>  &entries,std::string &myString){
		std::stringstream ss(myString);
		std::string tempToken;
		while(getline(ss, tempToken, constants::CHAR_TO_SEARCH_FOR)){
			processToken(entries, tempToken);
			}
	}

	/*Keep track of how many times each token seen*/
	void KP::processToken(std::vector<constants::entry>  &entries,std::string &token) {
		//Question 40 - Piazza
		std::string t = token;
		strip_unwanted_chars(t);

		std::string tempUncapped = t;
		toUpper(t);

		//Problem instance
		if (t.size() == 0) return;

		// int i = 0;
		// while(i<entries.size()){
		for ( int i = 0; i < entries.size(); i++ ) {
			if (entries[i].word_uppercase == t) {
				entries[i].number_occurences++;
				return;
			}
		}
		//ref obj
		constants::entry entry2 = constants::entry();
		entry2.number_occurences = 1;
		entry2.word = tempUncapped;
		entry2.word_uppercase = t;
		entries.push_back(entry2);
		return;
	}

	//Question 43 -Piazza

	bool compareCountAsc(constants::entry  en1, constants::entry en2) {
		return (en1.word_uppercase < en2.word_uppercase);
	}

	bool compareCountDes(constants::entry  en1, constants::entry en2) {
		return (en1.word_uppercase > en2.word_uppercase);
	}

	bool compareCountOcc(constants::entry  en1, constants::entry en2) {
		return (en1.number_occurences < en2.number_occurences);
	}

	/*
	 * Sort myEntryArray based on so enum value.
	 * Please provide a solution that sorts according to the enum
	 * The presence of the enum implies a switch statement based on its value
	 * See the course lectures and demo project for how to sort a vector of structs
	 */
	void KP::sort(std::vector<constants::entry>  &entries, constants::sortOrder so) {

		switch(so) {
		case constants::NONE:
			return;
			break;
		case constants::ASCENDING:
			std::sort(entries.begin(),entries.end(), compareCountAsc);
			return;
			break;
		case constants::DESCENDING:
			std::sort(entries.begin(), entries.end(), compareCountDes);
			return;
			break;
		case constants::NUMBER_OCCURRENCES:
			std::sort(entries.begin(), entries.end(), compareCountOcc);
			return;
			break;
		}
	}
