/**
 * @file doublelinkedlist.h   Declaration of a linklist for music.
 *
 * @brief
 *    Implementation of Playlist for music, where a doubly linked list is
 *    used to store the song names.
 *
 * @author Alex Moxon
 * @date 02/05/19
 */
#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>
#include "playlist.h"
using std::string;

class DoublyLinkedList
{
public:
  DoublyLinkedList();
  ~DoublyLinkedList();
  void append(const string &s);
  void insertBefore(const string &s);
  void insertAfter(const string &s);
  void remove(const string &s);
  bool empty();
  void begin();
  void end();
  bool next();
  bool prev();
  bool find(const string &s);
  const string &getData();

  class Node
  {
  public:
    Node();
    Node(string &s);
    ~Node();

    Node *next_;
    Node *prev_;
    string *data_;
  };

private:
  Node *head_;
  Node *tail_;
  Node *current_;
};

#endif // CSCI_311_DOUBLYLINKEDLIST_H
