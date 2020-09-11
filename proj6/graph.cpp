/*
 * @file graph.cpp - File contains all the functions used in creating
 * and maintaining the MST graph. Also contains the private classes 
 * (edge and vertex), used in building/altering our graph. 
 *
 * @author - Alex Moxon
 *
 * @date - April 25th 2019
 *
 */

#include "graph.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


/**
* @brief Constructor for the Graph class 
*/
Graph::Graph()
{
   start = false;
   total = 0;
   minQ = NULL;
}


/**
* @brief Destructor for the Graph class 
*/
Graph::~Graph()
{
   for(auto it = vertices.begin(); it != vertices.begin(); it++)
   {
      Vertex *tmp = it->second;
      delete tmp;
   }
   for(auto itt = adjList.begin(); itt != adjList.end(); itt++)
   {
      vector<Neighbor*> *tmp2 = itt->second;
      for(auto ittt = tmp2->begin(); ittt != tmp2->end(); ittt++)
      {
         Neighbor *tmp3 = *ittt;
         if(tmp3)
            delete tmp3;
      }
   }
   delete minQ;
}



/**
* @brief Default Constructor for the Graph class 
*/
Graph::Vertex::Vertex()
{
   pi = "NIL";
   key = 100;
}



/**
 * @brief Vertex Constructor w/ parameters, for the Graph class
 *
 * @param p - predecessor of new vertex
 * @param k - key of the new vertex
 *
 */
Graph::Vertex::Vertex(string p, int k)
{
   pi = p;
   key = k;
}


/**
* @brief Destructor for the Graph class 
*/
Graph::Vertex::~Vertex()
{

}


/**
* @brief Default Constructor for the Neighbor class 
*/
Graph::Neighbor::Neighbor()
{

}


/**
 * @brief Neighbor Constructor w/ parameters, for the Neighbor class
 *
 * @param name - name of new neighbor
 * @param weight - weight of the new neighbor
 *
 */
Graph::Neighbor::Neighbor(string name, int weight)
{
   this->name = name;
   this->weight = weight;
}


/**
* @brief Destructor for the Neighbor class 
*/
Graph::Neighbor::~Neighbor()
{

}


/**
* @brief Creates the first instance of minQ, of vertices size 
*/
void Graph::initQ()
{
   start = true;
   minQ = new MinPriorityQ((int)vertices.size());
}


/**
 * @brief Checks to see if given id arguement is a member of the queue
 *
 * @param vertex - name of vertex
 * @param flag - find, end or being iteration
 *
 * @return The iterators location in the map
 */
map<string,Graph::Vertex*>::iterator Graph::vAtt(string vertex, char flag)
{
	if(flag == 'b')
	{
		return vertices.begin();
	}
	else if(flag == 'e')
	{
		return vertices.end();
	}
	else if (flag == 'f')
	{
		return vertices.find(vertex);
	}
	else
	{
		return vertices.end();
	}
}


/**
 * @brief Function used for inserting vertices into the queue
 *
 * @param vertex - name of vertex to source
 * @param init - Initial weight of the queue
 *
 * @return 
 */
void Graph::fillQ(string vertex, int init)
{
   auto it = vertices.end();
   auto begin = vertices.end();
   auto end = vertices.end();

   minQ->decreaseKey(vertex, init);
   begin = vAtt(vertex, 'b');
   end = vAtt(vertex, 'e');

   for(it = begin; it != end; ++it)
   {
      Vertex *newV = it->second;
      minQ->insert(it->first, newV->key);
   }

   minQ->buildMinHeap();
}



/**
 * @brief Function used in finding adjacency list from 
 * passed argument vertex.
 *
 * @param vertex - Name of the vertex
 *
 * @return Adjacency list of the vertex
 */
vector<Graph::Neighbor*>* Graph::findAdj(string vertex)
{
   auto it = adjList.find(vertex);
   vector<Neighbor*> *adj = it->second;
   return adj;
}



/**
 * @brief Function used to calculate the distance between two vertexs
 *
 * @param u - name of vertex
 * @param v - name of the other vertex
 *
 * @return returns the distance between the two or 0 if error
 */
int Graph::weights(string u, string v)
{
   vector<Neighbor*> *adj = findAdj(u);
   for(auto it = adj->begin(); it != adj->end(); ++it)
   {
      Neighbor *dist = *it;
      if(dist && dist->name == v)
      {
         return dist->weight;
      }
   }
   return 0;
}



/**
 * @brief Function used to get the key of the passed string
 *
 * @param v - Name of the vertex
 *
 * @return Key of the vertex or 0 if error
 */
int Graph::keyV(string v)
{
   auto it = vAtt(v,'f');
   Vertex *tmp = it->second;
   return tmp->key;
}


/**
 * @brief Function used to update the parent vertex
 *
 * @param u - Name of Vertex one
 * @param v - Name of Vertex two
 * @param weight - Weight of the distance between the two
 *
 * @return 
 */
void Graph::updateParent(string u, string v, int weight)
{
   auto it = vAtt(v,'f');
   Vertex *tmp = it->second;

   //Update Predecesoor or Parent
   tmp->pi = u;
   tmp->key = weight;
}


/**
 * @brief Function used to add the vertex to the map and make a pair w/ Element
 *
 * @param name - Name of the Vertex
 *
 * @return 
 */
void Graph::addVertex(string name)
{
   itr2 = vAtt(name, 'e');
   itr = vAtt(name,'f');

   if(vertices.size() == 0)
   {
      data1 = name;
   }
   if(itr == itr2)
   {
      Vertex *newV = new Vertex();
      vertices.insert(make_pair(name, newV));
   }
}


/**
 * @brief Function used in adding the edges to the map of adj list
 *
 * @param from - Name of the starting Vertex
 * @param to - Name of the ending Vertex
 * @param weight - Weight of the edge
 *
 * @return returns the distance between the two or 0 if error
 */
void Graph::addEdge(string from, string to, int weight)
{

   auto it = adjList.find(from);
   auto aEnd = adjList.end();
   auto vEnd = vertices.end();

   vEnd = vAtt(to,'e');
   itr = vAtt(from,'f');
   itr2 = vAtt(to,'f');

   if(itr != vEnd && itr2 != vEnd)
   {
      if(it == aEnd)
      {
         Neighbor *newE = new Neighbor(to, weight);
         vector<Neighbor*> *sNeighbor = new vector<Neighbor*>;
         sNeighbor->emplace_back(newE);
         adjList.insert(make_pair(from, sNeighbor));
      }
      else
      {
         vector<Neighbor*> *sNeighbor = it->second;
         bool vertex_found = false;
         for(auto i = sNeighbor->begin(); i != sNeighbor->end(); ++i)
         {
            Neighbor *newE = *i;
            if(newE->name == to)
            {
               vertex_found = true;
               break;
            }
         }
         if(!vertex_found)
         {
            Neighbor *newE = new Neighbor(to, weight);
            sNeighbor->emplace_back(newE);
         }
      }
      //Beginning of minQ
      if(!start)
      {
         initQ();
      }
   }
}


/**
 * @brief Function used in the implementation of Prim's algorithm
 *
 * @param start - name of root vertex
 *
 * @return 
 */
void Graph::mst(string start)
{
   itr = vAtt(start,'f');
   Vertex *root = itr->second;
   root->key = 0;
   fillQ(start, 0);

   while(minQ->minHeapSize() >= 1)
   {
      string u = minQ->extractMin();
      vector<Neighbor*> *adj = findAdj(u);

      for(auto it = adj->begin(); it != adj->end(); ++it)
      {
         Neighbor *v = *it;
         int udistv = weights(u, v->name);
         int vKey = keyV(v->name);

         if((minQ->isMember(v->name) == true) && (udistv < vKey))
         {
            updateParent(u, v->name, udistv);
            minQ->decreaseKey(v->name, udistv);
         }
      }
      print(u);
   }
   cout<<total<<endl;
}


/**
 * @brief Function used in implementing Prim's algorithm for a MST
 *
 * @param startVertex - Name of the root vertex
 *
 * @return 
 */
void Graph::print(string startVertex)
{
   auto it = vAtt(startVertex,'f');

   Vertex *tmp = it->second;

   cout << it->first <<" "<< tmp->pi <<" ";
   cout << tmp->key << endl;

   total = total + tmp->key;
}