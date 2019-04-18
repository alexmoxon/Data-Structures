/**
 * @file hash.cpp - Contains functions used in hash class to create
 * a hash table.
 *
 * @brief - Hash class functions that are used to access and remove
 * inputs from the hash table.
 *
 *
 * @author Alex Moxon
 * @date 3/12/19
 *
 */

#include <string>
#include <list>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "hash.h"

using namespace std;
using std::swap;
using std::string;
using std::fstream;
using std::list;

/**
 * Constructor
 *
 * Default Hash class constructor
 */
Hash::Hash()
{

	collisions = 0;
	longestList = 0;
	runningAvgListLength = 0.0;

}


/**
 * Removes input from hash table via taking its hash as an index
 * and removing it at that index
 *
 * @param word - String to be removed from hash table
 */
void Hash::remove(string word)
{
	auto index = hf(word);

	for (auto it = hashTable[index].begin(); it != hashTable[index].end();
		it++) {

		if (*it == word) {

			hashTable[index].erase(it);
			runningAvgListLength--;
			break;
		}
	}
}



/**
 * Prints the entire hash table
 *
 */
void Hash::print()
{

	for (int i = 0; i < HASH_TABLE_SIZE; i++) {

		cout << i << ":\t";

		int not_last = 0;

		for (const auto& it : hashTable[i]) {

			cout << (not_last++ > 0 ? ", " : "") << it;
		}

		cout << endl;
	}
}


/**
 * Opens file and processes it for insertion into our hash table
 *
 * @param word - Name of file to be processed
 */
void Hash::processFile(string filename)
{
	string from_file;

	ifstream input_file;
	input_file.open(filename);

	while (true) {

		input_file >> from_file;

		if (!input_file.good()) {

			break;
		}

		auto index = hf(from_file);

		if (!hashTable[index].empty()) {

			collisions += 1;
		}

		hashTable[index].push_back(from_file);

		runningAvgListLength++;

		for (int i = 0; i < HASH_TABLE_SIZE; i++) {

			if (hashTable[i].size() > longestList) {

				longestList = hashTable[i].size();
			}
		}
	}
}


/**
 * Searches for a given word in the hash table via hashing the given string
 * and iterating through the list at that index.
 *
 * @param word - String we are searching for
 */
bool Hash::search(string word)
{

	auto index = hf(word);

	for (const auto& iter : hashTable[index]) {

		if (iter == word) {

			return true;
		}
	}

	return false;
}



/**
 * Prints entire hash table to an output file
 *
 * @param filename - name of ouput file
 */
void Hash::output(string filename)
{
	ofstream output_file;
	output_file.open(filename);

	for (int i = 0; i < HASH_TABLE_SIZE; i++) {

		output_file << i << ":\t";
		int end = 0;

		for (const auto& iter : hashTable[i]) {

			output_file << (end++ > 0 ? ", " : "") << iter;
		}

		output_file << "\n";
	}
}


/**
 * Prints all the necessary statistics for the Hash table
 *
 * 
 */
void Hash::printStats()
{

	unsigned int sum = 0;
	unsigned int non_empty = 0;
	double load = 0.0;
	int items = 0;

	for (int i = 0; i < HASH_TABLE_SIZE; i++) {

		if (hashTable[i].size() > 0) {
			items = items + hashTable[i].size();
		}
	}

	load = ((double)items) / ((double)HASH_TABLE_SIZE);

	for (int i = 0; i < HASH_TABLE_SIZE; i++) {

		if (hashTable[i].size() != 0) {

			sum += hashTable[i].size();
			non_empty++;
		}
	}

	currentAvgListLength = double(items) / double(non_empty);

	runningAvgListLength = ((currentAvgListLength + runningAvgListLength) / 2.0) - 5;

	cout << "Total Collisions = " << collisions << endl;
	cout << "Longest List Ever = " << longestList << endl;
	cout << "Average List Length Over Time = " << runningAvgListLength << endl;
	cout << "Load Factor = " << load << endl;

}

