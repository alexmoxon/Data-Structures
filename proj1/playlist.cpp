/**
 * @file playlist.cpp   Implementation of a Playlist for music.
 *
 * @brief
 *    Implementation of a Playlist for music. A doubly linked list is
 *    used to store the song names.
 *
 *    Note: main() is in this file.
 *
 * @author Judy Challinger & Alex Moxon
 * @date 02/09/19
 */

#include <iostream>
#include <string>

#include "playlist.h"
#include "doublylinkedlist.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
// you may add more private functions for functional decomposition

/**
 * Process a playlist command.
 *
 * Gets an entire line from std::cin, extracts the first word as the command,
 * and calls the appropriate processing function. Invalid commands are
 * ignored.
 *
 * @return false if command is "quit", otherwise true
 */

void Playlist::processCommand()
{

  string c;
  getline(cin, c);

  //Saves user input for Playlist Command as a string from beg. to first space
  string command = c.substr(0, c.find(' '));
  //Deletes string command from c string, leaving song string left
  c.erase(0, c.find(' ') + 1);

  //Saves string of everything after first space
  string song = c.substr();

  //If-else that processes command string and passes them to the DLL
  if (command == "appendSong")
  {
    dll.append(song);
  }

  else if (command == "insertBefore")
  {
    dll.insertBefore(song);
  }

  else if (command == "insertAfter")
  {
    dll.insertAfter(song);
  }

  else if (command == "removeSong")
  {
    dll.remove(song);
  }

  else if (command == "gotoFirstSong")
  {
    dll.begin();
  }

  else if (command == "gotoLastSong")
  {
    dll.end();
  }

  else if (command == "nextSong")
  {
    dll.next();
  }

  else if (command == "prevSong")
  {
    dll.prev();
  }

  else if (command == "playCurrent")
  {
    cout << "\n";
    cout << "playing current: ";
    if (!dll.empty())
    {
      string temp = dll.getData();
      cout << temp;
      cout << "\n";
    }
    else
    {
      cout << "\n";
    }
  }

  else if (command == "playForward")
  {
    cout << "\n";
    cout << "playing forward: ";
    cout << "\n";

    if (!dll.empty())
      cout << dll.getData();
    cout << "\n";

    while (dll.next())
    {
      cout << dll.getData();
      cout << "\n";
    }
  }

  else if (command == "playReverse")
  {
    cout << "\n";
    cout << "playing reverse: ";
    cout << "\n";

    if (!dll.empty())
      cout << dll.getData();
    cout << "\n";

    while (dll.prev())
    {
      cout << dll.getData();
      cout << "\n";
    }
  }

  else if (command == "gotoSong")
  {
    dll.find(song);
  }
  else if (command == "quit")
  {
    return;
  }
}

/**
 * The Playlist main loop will process command lines until finished.
 */
void Playlist::mainLoop()
{
  while (!cin.eof())
    processCommand(); // process all commands
}

/**
 * The main entry point for the program.
 */

int main()
{
  Playlist myPlaylist;
  myPlaylist.mainLoop();

  return 0;
}
