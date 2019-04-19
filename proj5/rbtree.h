/*
 * @file rbtree.h - Declaration of a red-black tree class.
 *
 * Note: The functions in this class should not do any I/O (except the
 * provided function rbPrintTree).
 *
 * @author Judy Challinger
 * @date 10/23/14
 */

#ifndef CSCI_311_RBTREE_H
#define CSCI_311_RBTREE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class RBTree {

public:

   RBTree();                                                // Constructor
   ~RBTree();                                               // Destructor

   void rbInsert(const string& key, const string& value);   // Insert into tree
   void rbDelete(const string& key, const string& value);   // Delete from tree
   vector<const string*> rbFind(const string& key);         // Find in tree
   void rbPrintTree();                                      // Prints out tree

private:

   // Node is a private nested class - used only by RBTree.
   class Node {
   public:
      Node(); // use this constructor to create the one nil Node
      Node(const string& key, const string& value);
      ~Node();
      Node *parent;
      Node *left;
      Node *right;
      char color;
      string *key;
      string *value;
   };

   Node *root;          // pointer to the root of the red-black tree
   Node *nil;           // pointer to the single nil node

   // private accessors - must all use nil
   Node* rbTreeMinimum(Node*);
   Node* rbTreeMaximum(Node*);
   Node* rbTreeSuccessor(Node*);
   Node* rbTreePredecessor(Node*);
   Node* rbTreeSearch(Node*, const string&);
   void reverseInOrderPrint(Node*, int);

   // private mutators
   void leftRotate(Node*);
   void rightRotate(Node*);
   void rbInsertFixup(Node*);
   void rbDeleteFixup(Node*);
   void rbTransplant(Node*, Node*);

   // private mutators overloaded from public interface
   void rbInsert(Node*);
   void rbDelete(Node*);

   // do not modify anything above this line!
   // you may add private functions below (although you shouldn't need to)

   void nodeDestroy(Node*);   // deallocates RBTree
};

#endif // CSCI_311_RBTREE_H
