/**
 * @file playlist.h   Declaration of a Playlist for music.
 *
 * @brief
 *    Implementation of Playlist for music, where a doubly linked list is
 *    used to store the song names.
 *
 * @author Judy Challinger & Alex Moxon
 * @date 02/09/19
 */

#ifndef CSCI_311_PLAYLIST_H
#define CSCI_311_PLAYLIST_H

#include "doublylinkedlist.h"
using std::string;

class Playlist
{
public:
  void mainLoop(); // process commands until finished
private:
  DoublyLinkedList dll;  // playlist stored in doubly linked list
  void processCommand(); // read and process one playlist command
};
#endif // CSCI_311_PLAYLIST_H