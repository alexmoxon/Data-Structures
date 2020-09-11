/*
 * @file minpriority.cpp - File creates the minHeap and contains all 
 * the functions needed to parse and maintain the minHeap
 *
 * @author - Alex Moxon
 *
 * @date - April 25th 2019
 *
 */

#include "minpriority.h"

#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;


/**
* @brief Constructor for MinPriorityQ minHeap
*/
MinPriorityQ::MinPriorityQ(int hSize)
{
   minHeap.reserve(hSize);
   this->hSize = 0;
}


/**
* @brief Destructor for MinPriorityQ minHeap
*/
MinPriorityQ::~MinPriorityQ()
{

}


/**
 * @brief Insert element into minheap, sort
 *
 * @param id - Heap ID
 * @param key - Heap key
 */
void MinPriorityQ::insert(string id, int key)
{
   Element x;
   x.id = id;
   x.key = key;
   minHeap.push_back(x);
   hSize++;
   minHeap.resize(hSize);
}


/**
 * @brief Return parent of a node by index
 *
 * @param i - Index to get parent of
 *
 * @return Key of the parent
 */
int MinPriorityQ::parent(int i)
{
   return floor(i/2);
}


/**
 * @brief Return the left child of a node by index
 *
 * @param i - Index to get left child of
 *
 * @return Key of the left child
 */
int MinPriorityQ::left(int i)
{
   return 2*i;
}


/**
 * @brief Return the right child of a node by index
 *
 * @param i Index to get right child of
 *
 * @return Key of the right child
 */
int MinPriorityQ::right(int i)
{
   return ((2*i) + 1);
}


/**
 * @brief Used to maintain min-heap property, every node is greater then its
 * children, unless its children are null
 *
 * @param i Node to test, and fix if required
 */
void MinPriorityQ::minHeapify(int i)
{
   int l, r, small;
   small = 0;
   l = left(i);
   r = right(i);

   if(l <= hSize && ((minHeap[l-1].key) < (minHeap[i-1].key)))
   {
      small = l;
   }
   else
   {
      small = i;
   }
   if(r <= hSize && ((minHeap[r-1].key) < (minHeap[small-1].key)))
   {
      small = r;
   }
   if( small != i)
   {
      swap(minHeap[i-1], minHeap[small-1]);
      minHeapify(small);
   }
}


/**
 * @brief Generate a min-heap from an array of ints
 */
void MinPriorityQ::buildMinHeap()
{
   for(int i = floor(hSize/2); i > 0; i--)
   {
      minHeapify(i);
   }
}


/**
 * @brief Return the first value of the min-heap (containing the smallest key)
 *
 * @return ID of the element with the minimum key
 */
string MinPriorityQ::extractMin()
{

   int length = (int)minHeap.size();
   if(length <= 0 )
   {
      return "empty";
   }
   Element min = minHeap[0];
   minHeap[0] = minHeap[length-1];
   hSize = hSize - 1;
   minHeap.resize(hSize);
   minHeapify(1);
   return min.id;
}


/**
 * @brief Decrease the key of a value, search by ID
 *
 * @param id ID to search for
 * @param newKey Replace ID's key with this
 */
void MinPriorityQ::decreaseKey(string id, int newKey)
{
   int i,j;
   j = hSize - 1;
   for(i = 0; i < hSize; i++)
   {

      if(minHeap[i].id == id)
      {
         if(newKey < minHeap[i].key)
         {
            j = i;
            minHeap[j].key = newKey;
         }
      }
   }
   buildMinHeap();
}


/**
 * @brief Return the size of the Vector minHeap
 *
 * @return size of minHeap
 */
unsigned int MinPriorityQ::minHeapSize()
{
   return minHeap.size();
}


/**
 * @brief Checks to see if given id arguement is a member of the queue
 *
 * @param id Id of the member we're searching for
 *
 * @return true if in queue, false if not
 */
bool MinPriorityQ::isMember(string id)
{
   for(int i = 0; i < hSize; i++)
   {
      if((minHeap[i].id == id))
      {
         return true;
      }
   }
   return false;
}