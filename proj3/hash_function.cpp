/**
 * @file hash_function.cpp    Hash function implementation not completed yet.
 *
 * @brief
 *    Hash function implementation that still needs work but all other aspects 
 * of the code function properly.
 *
 * @author Alex Moxon
 * @date 3/12/19
 */

#include <string>
#include <iostream>
#include "hash.h"

using std::string;



/**
 * Was looking into rolling hashes online and stumbled upon
 * content based slicing. The hash function works by hashing the input
 * in a window that continously  moves throught the input. Didn't figure
 * out home to implement it before the due date but I will finish it tomorrow
 * when i'm not getting bombarded by my bellig roomates.Cheers!
 */

int Hash::hf(string ins) {

	unsigned int hashVal = 0;

	for (int i = 0; i < (int)ins.length(); i++) {

		hashVal += (11 * hashVal) + ins[0];
		hashVal %= HASH_TABLE_SIZE;
	}

	return hashVal;
}



/*
int Hash::hf(string ins) {

	int hash = ((int)ins[0] % HASH_TABLE_SIZE);

	for (int i = 0; i < (int)ins.length(); i++)

		hash ^= (15 ^ ins[i]) + ins[i];

	return hash % HASH_TABLE_SIZE;
}
*/


/*

int
Hash::hf (string ins) {

	unsigned int hash = 13;

	for (int i = 0; i < (int)ins.length(); i++) {

		hash = (hash ^ ins[i]) * 33;
	}

	return (hash % HASH_TABLE_SIZE);
}
*/