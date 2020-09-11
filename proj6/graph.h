/*
 * @file graph.h - File contains helper functions for 
 * the implementation and maintainance of our MST
 *
 * @author - Alex Moxon
 *
 * @date - April 25th 2019
 *
 */

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "minpriority.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Graph
{
public:

  Graph();
  ~Graph();

  void addVertex(string name);
  void addEdge(string from, string to, int weight);
  void mst(string start);

  string info() 
  {
    return data1; 
  };

private:

  class Vertex
  {
  public:

    Vertex();
    Vertex(string p, int k);
    ~Vertex();

    string pi;
    int key;

  };

  class Neighbor
  {
  public:

    Neighbor();
    Neighbor(string name, int weight);
    ~Neighbor();

    string name;
    int weight;

  };

  MinPriorityQ *minQ;
  map<string, Vertex*> vertices;
  map<string, vector<Neighbor*>*> adjList;

  vector<Neighbor*> *findAdj(string vertex);

  void initQ();
  void fillQ(string vertex, int init);

  map<string, Vertex*>::iterator itr, itr2;
  map<string, Vertex*>::iterator vAtt(string vertex, char flag);

  int total;
  bool start;
  string data1;

  int weights(string u, string v);
  int keyV(string v);

  void updateParent(string u, string v, int weight);
  void print(string startVertex);

};

#endif