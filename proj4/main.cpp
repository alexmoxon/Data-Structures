/*
 *@brief main.cpp - Min-Priority Queue main/process input functions
 *
 * @author Alex Moxon
 *
 * @date: April 1st 2019
 *
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <string>
#include "minpriority.h"

using std::stringstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

/**
 * processCommand
 *
 * @brief
 *    calls functions on the minpriority queue based on command inputs
 *
 * @param commandLine The string that contains the input
 *
 * @return bool
 *    for mainLoop to determine if the quit command
 *    has been passed
 */
bool Minpriority::processCommand(string& data)
{
	string name, cmd;
	int key_val;

	stringstream sStream(data);

	sStream >> cmd;
	sStream.ignore();

	if (cmd == "a")
	{
		sStream >> name;
		sStream.ignore();
		sStream >> key_val;
		sStream.ignore();
		insert(name, key_val);
	}
	else if (cmd == "d")
	{
		sStream >> name;
		sStream.ignore();
		sStream >> key_val;
		sStream.ignore();
		decreaseKey(name, key_val);
	}
	else if (cmd == "x")
	{
		extractMin();
	}
	else if (cmd == "q")
	{
		return false;
	}
	return true;
}



/**
 * The Min priority queue main loop will process command lines until finished.
 */
void Minpriority::mainLoop()
{
	string data ="";
	while(processCommand(data) && cin.peek() != EOF)
	{
		getline(cin, data);
	}
}

/**
 * main
 *
 * @brief
 *    main loop
 *    initializes our minHeap and calls its mainLoop()
 *
 * @param none
 *
 * @return 0
 */
int main() {

  Minpriority minHeap;
  minHeap.mainLoop();

  return 0;
}
