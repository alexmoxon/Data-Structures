/*
 * @file mstapp.h - File that contains all the functions used in creating
 * our MST Graph.
 *
 * @author - Alex Moxon
 *
 * @date - April 25th 2019
 *
 */

#ifndef __MSTAPP_H__
#define __MSTAPP_H__

#include "graph.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class MSTapp
{
public:

    MSTapp();
    ~MSTapp();

    void readGraph();

    Graph getMyGraph()
    { 
        return myGraph; 
    };
    Graph myGraph;

private:

    bool root;
};

#endif