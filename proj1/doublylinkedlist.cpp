/**
 * @file doublelinkedlist.cpp   Implementation of a Playlist for music.
 *
 * @brief
 *    Implementation of a Playlist for music. A doubly linked list is
 *    used to store the song names.
 *
 *    Note: main() is in this file.
 *
 * @author Judy Challinger & Alex Moxon
 * @date 02/08/19
 */

#include <iostream>
#include <string>
#include "playlist.h"
#include "doublylinkedlist.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

// Linked list constructor used to initliase nodes
DoublyLinkedList::DoublyLinkedList()
{

  head_ = NULL;
  tail_ = NULL;
  current_ = NULL;
}

// Linked list constructor used to store data
DoublyLinkedList::~DoublyLinkedList()
{
  Node *temp;
  while (head_ != NULL)
  {
    temp = head_;
    head_ = head_->next_;
    delete temp;
  }
}

// Song is added to the end of the playlist and set as current song
void DoublyLinkedList::append(const string &s)
{

  string song = s;
  Node *temp = new Node();
  temp = new Node(song);

  if (head_ == NULL)
  {
    head_ = temp;
    tail_ = temp;
    current_ = temp;
  }
  else
  {
    tail_->next_ = temp;
    temp->prev_ = tail_;
    tail_ = tail_->next_;
    current_ = tail_;
  }
}

// Function used to insert song before current song, then set newly inserted song to current song
void DoublyLinkedList::insertBefore(const string &s)
{
  string song = s;
  Node *temp = new Node();
  temp = new Node(song);
  Node *tempC = current_;

  if (empty())
  {
    tail_ = temp;
    head_ = temp;
    current_ = head_;
  }
  else
  {
    if (current_->prev_ == NULL)
    {
      current_->prev_ = temp;
      temp->next_ = current_;
      current_ = current_->prev_;
      head_ = current_;
    }
    else
    {
      tempC = tempC->prev_;
      current_->prev_ = temp;
      temp->next_ = current_;
      tempC->next_ = temp;
      temp->prev_ = tempC;
      current_ = temp;
    }
  }
}

// Function used to insert song after current song, then set newly inserted song to current song
void DoublyLinkedList::insertAfter(const string &s)
{
  string song = s;
  Node *temp = new Node();
  temp = new Node(song);
  Node *tempC = current_;

  if (empty())
  {
    tail_ = temp;
    head_ = temp;
    current_ = head_;
  }
  else
  {
    if (current_->next_ == NULL)
    {
      current_->next_ = temp;
      temp->prev_ = current_;
      current_ = current_->next_;
      tail_ = current_;
    }
    else
    {
      tempC = tempC->next_;
      current_->next_ = temp;
      temp->prev_ = current_;
      tempC->prev_ = temp;
      temp->next_ = tempC;
      current_ = temp;
    }
  }
}

// Function used to find and remove song from linked list
void DoublyLinkedList::remove(const string &s)
{

  string song = s;
  Node *temp = new Node();
  Node *tempT = new Node();
  Node *tempC = new Node();
  Node *tempN = new Node();

  tempT = tail_;
  temp = head_;

  if (!empty())
  {
    bool tempF = find(song);
    if (tempF == true)
    {
      if (current_ == head_)
      {
        temp = temp->next_;
        delete head_;
        head_ = temp;

        if (empty())
        {
          head_ = NULL;
          tail_ = NULL;
          current_ = NULL;
        }
        else
        {
          head_->prev_ = NULL;
          current_ = head_;
        }
      }
      else if (current_ == tail_)
      {
        tempT = tempT->prev_;
        delete tail_;
        tail_ = tempT;
        tempT->next_ = NULL;
        current_ = tail_;
      }
      else
      {
        tempC = current_;
        tempN = current_;
        tempN = tempN->next_;
        current_ = current_->prev_;
        current_->next_ = tempN;
        tempN->prev_ = current_;
        delete tempC;
        current_ = tempN;
      }
    }
  }
}

// Function used to determine whether playlist is empty or not
bool DoublyLinkedList::empty()
{
  if (head_ == NULL)
  {
    return true;
  }

  else
  {
    return false;
  }
}
// Function used to set current song to the first song on linked list
void DoublyLinkedList::begin()
{
  if (!empty())
  {
    current_ = head_;
  }
}

// Function used set current song to the last song on linked list
void DoublyLinkedList::end()
{
  if (!empty())
  {
    current_ = tail_;
  }
}

// Function used to move current song to next song, if one exists. Otherwise song stays the same
bool DoublyLinkedList::next()
{
  if (!empty())
  {
    if (current_->next_ != NULL)
    {
      current_ = current_->next_;
      return true;
    }
  }
  return false;
}

// Function used to move current song to previous song if one exists. Otherwise song stays the same
bool DoublyLinkedList::prev()
{
  if (!empty())
  {
    if (current_->prev_ != NULL)
    {
      current_ = current_->prev_;
      return true;
    }
  }
  return false;
}

// Function used to find song given by user input
bool DoublyLinkedList::find(const string &s)
{
  string song = s;
  Node *temp;
  temp = head_;
  bool flag = false;

  if (!empty())
  {
    while (temp != NULL)
    {
      if (*temp->data_ == song)
      {
        flag = true;
        current_ = temp;
        break;
      }
      else
      {
        temp = temp->next_;
      }
    }
  }
  return flag;
}

// Function used to get song data from linked list
const string &DoublyLinkedList::getData()
{
  if (head_ != NULL)
  {
    if (current_ != NULL)
    {
      return *current_->data_;
    }
    else
    {
      return NULL;
    }
  }
  else
  {
    return NULL;
  }
}

// Empty Node constructor to initialise data
DoublyLinkedList::Node::Node()
{
  next_ = NULL;
  prev_ = NULL;
  data_ = new string();
}
// Node destructor used to free memory
DoublyLinkedList::Node::~Node()
{
  delete data_;
}
// Node constructor used to initialise songs & nodes
DoublyLinkedList::Node::Node(string &s)
{
  prev_ = NULL;
  next_ = NULL;
  data_ = new string();
  (*data_).assign(s);
}