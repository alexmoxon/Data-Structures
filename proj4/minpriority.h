/*
 * @brief minpriority.h Declaration of Min-Priority Queue
 *
 * @author Alex Moxon
 *
 * @date: March 30th 2019
 *
 */

#ifndef __MINPRIORITY_H
#define __MINPRIORITY_H

#include <iostream>
#include <vector>
#include <string>

using std::string;

class Minpriority {

public:
	Minpriority();
	~Minpriority();
	void insert(string name, int key_val);
	void decreaseKey(string name, int key_val);
	void mainLoop();
	bool isMember(string name);

private:
	class Element {

	public:
		string id;
		int key;
	};

	std::vector<Element*> minHeap;

	void buildMinHeap();
	bool processCommand(string& data);
	void minHeapify(int i);
	int parent(int i);
	int left(int i);
	int right(int i);
	int heap_size;
	string extractMin();

};

#endif