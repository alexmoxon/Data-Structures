/*
 * @file minpriority.h - File contains the helper functions
 * for the implementation and maintainance of the minHeap.
 *
 * @author - Alex Moxon
 *
 * @date - April 25th 2019
 *
 */


#ifndef __MINPRIORITYQ_H__
#define __MINPRIORITYQ_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MinPriorityQ
{
public:

    MinPriorityQ(int);
    ~MinPriorityQ();

    void insert(string, int);
    void decreaseKey(string, int);
    void buildMinHeap();

    unsigned int minHeapSize();
    bool isMember(string id);
    string extractMin();

private:
	class Element
	{
	public:
		string id;
        int key;
    };

    vector<Element> minHeap;
    void minHeapify(int);

    int parent(int);
    int left(int);
    int right(int);
    int hSize;
};

#endif