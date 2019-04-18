/*
 * @brief minpriority.cpp - all the functions needed to access and change the minHeap
 *
 * @author Alex Moxon
 *
 * @date: March 30th 2019
 *
 */

#include <string>
#include <vector>
#include "minpriority.h"

using std::swap;

/**
 * @brief
 *    initialize our heap to 0
 *
 * @param none
 *
 * @return none
 */
Minpriority::Minpriority()
{
	heap_size = 0;
}

/**
 * @brief
 *    Heap constructor
 *
 * @param none
 *
 * @return none
 */
Minpriority::~Minpriority()
{

}

/**
 * @brief
 *    returns the parent of the given key
 *
 * @param int i - key for where to put our data in the min-heap.
 *
 * @return - parent key
 */
int Minpriority::parent(int i)
{
	return((i + 1) / 2) - 1;
}

/**
 * @brief
 *    returns the left value of the given key
 *
 * @param int i - key for where to put our data in the min-heap.
 *
 * @return - key to the left
 */
int Minpriority::left(int i)
{
	return(2 * (i + 1)) - 1;
}

/**
 * @brief
 *    returns the right value of the given key
 *
 * @param int i - key for where to put our data in the min-heap.
 *
 * @return key to the right
 */
int Minpriority::right(int i)
{
	return(2 * (i + 1));
}

/**
 * @brief
 *    rebuilds the min-heap once data is implemented or taken away.
 *
 * @param 
 *
 * @return
 */
void Minpriority::buildMinHeap()
{
	for (int i = (minHeap.size() / 2); i >= 0; i--)
	{
		minHeapify(i);
	}
}

/**
 * @brief
 *    inserts name into min-heap with the given key_value.
 *
 * @param string name - name to be inserted into the min-heap
 * @param int key_val - value on min-heap where the name will be inserted at
 * @return
 */
void Minpriority::insert(string name, int key_val)
{
	Element *ele = new Element;

	ele->key = key_val;
	ele->id = name;
	heap_size++;

	minHeap.push_back(ele);
	decreaseKey(name, key_val);
}

/**
 * @brief
 *    removes name in min-heap with the given key_value.
 *
 * @param string name - name to be removed from the min-heap
 * @param int key_val - value on min-heap where the name will be removed at
 * @return
 */
void Minpriority::decreaseKey(string name, int key_val)
{
	int pos = 0;
	Element *ele = nullptr;

	if (!minHeap.empty())
	{
		for (unsigned int i = 0; i <= minHeap.size() - 1; i++)
		{
			if (minHeap[i]->id == name)
			{
				pos = i;

				if (key_val < minHeap[i]->key)
				{
					ele = minHeap[i];
					minHeap[pos]->key = key_val;

					while (pos > 0 && minHeap[parent(pos)]->key
					 > minHeap[pos]->key)
					{
						swap(minHeap[parent(pos)], minHeap[pos]);
						pos = parent(pos);
					}
				}
				else
				{
					return;
				}
			}
		}
	}
	if (ele != nullptr)
	{
		ele->key = key_val;
		buildMinHeap();
	}
}

/**
 * @brief
 *    searches the min-heap and extracts the minimum key value in the queue.
 *
 * @param
 * 
 * @return - extracts and prints the minimum priority element.
 */
string Minpriority::extractMin()
{

	if (heap_size == 0)
	{
		return "empty";
	}

	Element *ele = minHeap[0];
	string name = minHeap[0]->id;

	minHeap[0] = minHeap[heap_size - 1];
	minHeap.pop_back();

	buildMinHeap();
	heap_size--;

	delete ele;
	return name;
}

/**
 * @brief
 *    checks to see if name if already a member of the min-heap
 *
 * @param string name - name to be inserted into the min-heap
 * 
 * @return - true if name is part of heap
 */
bool Minpriority::isMember(string name)
{

	for (std::vector<Element*>::iterator iter = minHeap.begin(); 
		iter != minHeap.end(); iter++)
	{
		if (name == (*iter)->id)
		{
			return true;
		}
	}

	return false;
}

/**
 * @brief
 *    re-sorts the min-heap after an element has been added
 *
 * @param int i - number of elements in the heap
 * 
 * @return
 */
void Minpriority::minHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int min;

	if (l <= heap_size && minHeap[l]->key < minHeap[i]->key)
	{
		min = l;
	}

	else
	{
		min = i;
	}

	if (r <= heap_size && minHeap[r]->key < minHeap[min]->key)
	{
		min = r;
	}

	if (min != i)
	{
		swap(minHeap[i], minHeap[min]);
		minHeapify(min);
	}
}