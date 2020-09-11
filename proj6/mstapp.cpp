/*
 * @file mstapp.cpp - Contains the main(), which takes in
 * commandline input & calls the appropriate minUeap function.
 *
 * @author - Alex Moxon
 *
 * @date - April 25th 2019
 *
 */


#include "mstapp.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;


/**
* @brief Constructor for MSTapp myApp
*/
MSTapp::MSTapp() : root(false)
{

}


/**
* @brief Destructor for MSTapp myApp
*/
MSTapp::~MSTapp()
{

}


//Universal string for commandline input
string uInput;


/**
* @brief Function used to read commandline input
* and call the appropriate function.
*/
void MSTapp::readGraph()
{
    string input;
    stringstream stss(uInput);

    while(getline(stss,input,' '))
    {
        if(root == false)
        {
            myGraph.addVertex(input);
        }
        else
        {
            int weight;
            string from, to, weigh2;

            stringstream stss2(uInput);
            stss2>>from>>to>>weigh2;
            weight = atoi(weigh2.c_str());

            if(weight >= 1 && weight <= 99)
            {
                myGraph.addEdge(from,to,weight);
                myGraph.addEdge(to,from,weight);
            }
        }
    }

    root = true;
}



/**
 * @brief Main function of the program. Constructs our Heap and Queue
 * by taking in commandline input and passing it to readGraph().
 *
 * @return 0 when end of commandline input
 */
int main()
{

   MSTapp myApp;
   string data;

   while(getline(cin,data))
   {
      uInput = data;

      if(data=="")
      {
        break;
      }
      else
      {
         myApp.readGraph();
      }
   }

   //allows instance objects and functions to be public or private
   myApp.myGraph.mst(myApp.myGraph.info());

   return 0;
}
