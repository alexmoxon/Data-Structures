/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 * 
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 *
 * @author Alex Moxon
 * @date 2/14/19
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>
#include <climits>
#include <random>
#include "CensusData.h"

using std::default_random_engine;


/** 
 * Insertion Sort function used to sort census-data file by strings (city)
 * or by ints (population) type, one record at a time.
 *
 * @param type = type of data to sort by.
 */
void CensusData::insertionSort(int type) 
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		Record* key = data[i];
		int j = i - 1;

		if (type == POPULATION)
		{
			while (j >= 0 && key->population < data[j]->population)
			{
				data[j+1] = data[j];
				j--;
			}
			data[j+1] = key;
		}
		else
		{
			while (j >= 0 && *(key->city) < *(data[j]->city))
			{
				data[j+1] = data[j];
				j--;
			}
			data[j+1] = key;
		}
	}
}


/**
 * Compares two pointers of Records to determine desired sorting type.
 *
 *@param type = type of data to sort by.
 *@param r1 = pointer to Records on the left side of comparison.
 *@param r2 = pointer to Records on the right side of comparison.
 */
bool CensusData::isSmaller(int type, Record* r1, Record* r2)
{
	if (type == 0)
	{
		if (r1->population < r2->population)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (*r1->city < *r2->city)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


/**
 * Quick sort helper function used to generate vector of size Records.
 *
 *@param type = type of data to sort by.  
 */
void CensusData::quickSort(int type) 
{
	int r = data.size() - 1;
	quickSort(type, 0, r);
}


/**
 * Quick sort helper function used to establish random pivot point for 
 * recursive calls to Quick sort function
 *
 *@param type = type of data to sort by.
 *@param p = integer defining the beginning of data vector.
 *@param r = integer defining the end of data vector.
 */
void CensusData::quickSort(int type, int p, int r)
{
	if (p < r)
	{
		int q = randomPartition(type, p, r);
		quickSort(type, p, q-1);
		quickSort(type, q+1, r);
	}
}

/**
 * Function used to sort data vector into two partitions.
 * One partition of data Records smaller than r == (int @ end of vector)
 * and one partition of data Records larger than r.
 *
 *@param type = type of data to sort by.
 *@param p = integer defining the beginning of data vector.
 *@param r = integer defining the end of data vector.
 */
int CensusData::partition(int type, int p, int r)
{
	Record* key = data[r];
	int i = p-1;

	for (int j = p; j < r; j++)
	{
		if (isSmaller(type, data[j], key))
		{
			i++;
			Record* temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}

	Record* temp2 = data[i+1];
	data[i+1] = data[r];
	data[r] = temp2;
	return (i+1);
}


/**
 * Helper function used to establish random pivot point of vector data.
 * Data used to put vector into bigger and smaller partitions based on pivot.
 *
 *@param type = type of data to sort by.
 *@param p = integer defining the beinning of data vector.
 *@param r = integer defining the end of data vector.
 */
int CensusData::randomPartition(int type, int p, int r)
{

	// Seeding random number engine
	std::default_random_engine ranNum(time(0));

	// Setting scope of the random number generated
	std::uniform_int_distribution<int> dist(p,r);

	int i = dist(ranNum);
	Record* temp = data[r];

	data[r] = data[i];
	data[i] = temp;

	return partition(type, p, r);
}



/**
 * Merge sort helper function used to generate vector from desired sort type.
 *
 *@param type = type of data to sort by.
 */
void CensusData::mergeSort(int type) 
{
	if (type == 0)
	{
		mergeSort(type, 0, data.size() - 1);
	}
	else if (type == 1)
	{
		mergeSort(type, 0, data.size() - 1);
	}
}


/**
 * Merge sort helper function used for handeling partitioning of data vector.
 * Calls itself until base cases are established, then calls Merge function.
 *
 *@param type = type of data to sort by.
 *@param p = integer defining the beginning of data vector.
 *@param r = integer defining the end of data vector.
 */
void CensusData::mergeSort(int type, int p, int r)
{
	if (p < r)
	{
		int q = (p+r)/2;
		mergeSort(type, p, q);
		mergeSort(type, q + 1, r);
		merge(type, p, q, r);
	}
}


/**
 * Merge function used to combine partitioned vectors back together in 
 * correct order.
 *
 *@param type = type of data to sort by.
 *@param p = integer defining the beinning of data vector.
 *@param q = integer defining the middle of data vector.
 *@param r = integer defining the end of data vector.
 */
void CensusData::merge(int type, int p, int q, int r)
{

	int n1 = q - p + 1;
	int n2 = r - q;

	unsigned int a = 0;
	unsigned int b = 0;

	// Creating temp vectors of left and right of q
	vector<Record*> leftSide(n1);
	vector<Record*> rightSide(n2);

	for (int j = 0; j < n1; j++)
	{
		leftSide[j] = data[p+j];
	}
	for (int j = 0; j < n2; j++)
	{
		rightSide[j] = data[q+j+1];
	}


	for (int i = p; i <= r; i++)
	{
		if (a >= leftSide.size())
		{
			data[i] = rightSide[b];
			b++;
		}
		else if (b >= rightSide.size())
		{
			data[i] = leftSide[a];
			a++;
		}
		else
		{
			if (type == 0)
			{
				if (leftSide[a]->population <= rightSide[b]->population)
				{
					data[i] = leftSide[a];
					a++;
				}
				else
				{
					data[i] = rightSide[b];
					b++;
				}
			}
			else
			{
				if (*leftSide[a]->city <= *rightSide[b]->city)
				{
					data[i] = leftSide[a];
					a++;
				}
				else
				{
					data[i] = rightSide[b];
					b++;
				}
			}
		}
	}
}