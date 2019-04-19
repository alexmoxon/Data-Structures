/*
 * @file rbtree.cpp - Functions ran with command line input,
 * used in the implementation of Red-Black Tree.
 *
 * @author - Alex Moxon
 *
 * @date - April 17th 2019
 *
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include "rbtree.h"


using std::cout;
using std::setw;
using std::endl;
using std::vector;


/*
 * @brief - Red-Black Tree constructor, initializes member variables.
 *    
 * @param - none
 *
 * @return - none
 *
 */
RBTree::RBTree() {

    nil = new Node();
    root = nil; 
}


/*
 * @brief - Red-Black Tree destructor.
 *    
 * @param - none
 *
 * @return - none
 *
 */
RBTree::~RBTree() {

    nodeDestroy(root);
    delete nil; 
}


/*
 * @brief - Default constructor for Nodes, used by nil.
 *    
 * @param - none
 *
 * @return - none
 *
 */
RBTree::Node::Node() {

	key = new string("nil");
	value = new string("");
	color = 'B';
	left = this;
	right = this;
	parent = this;
}


/*
 * @brief - Destructor for Node
 *    
 * @param - none
 *
 * @return - none
 *
 */
RBTree::Node::~Node() {

    delete key;
    delete value;
}


/*
 * @brief - Constructor used by all internal nodes
 *    
 * @param - _key -> the key value of the new node
 * @param - _value -> the data/value of the new node
 *
 * @return - none
 *
 */
RBTree::Node::Node(const string& _key, const string& _value) {

    key = new string(_key);
    value = new string(_value);
}


/*
 * @brief - Insert helper function. Initializes new node for
 * each element that'll be inserted into the tree.
 *    
 * @param - key -> the key value of the new node
 * @param - value -> the data/value of the new node
 *
 * @return - none
 *
 */
void RBTree::rbInsert(const string& key, const string& value) {

	Node* newNode = new Node(key, value);
	rbInsert(newNode);
}


/*
 * @brief - Inserts node into the RBTree
 *    
 * @param - Node* z -> Newly constructed node, to be inserted in the RBTree
 *
 * @return - none
 *
 */
void RBTree::rbInsert(Node* z) {

    Node *y = nil; 
    Node *x = root;

    while(x != nil) {

        y = x; 

        if(*(z->key) < *(x->key)) {

            x = x->left;
        }

        else{

            x = x->right;
        }
    }

    z->parent = y;

    if(y == nil) {

        root = z;
    }

    else if(*(z->key) < *(y->key)) {

        y->left = z;
    }

    else{

        y->right = z; 
    }

    z->left = nil;
    z->right = nil; 
    z->color = 'R';

    rbInsertFixup(z); 
}


/*
 * @brief - Called after the insert of a new node into the tree. This 
 * function reshapes the tree after a new node input.
 *    
 * @param - Node* z -> Newly constructed node, to be inserted in the RBTree
 *
 * @return - none
 *
 */
void RBTree::rbInsertFixup(Node* z) {

    Node *y;

    while(z->parent->color == 'R') {

        if(z->parent == z->parent->parent->left) {

            y = z->parent->parent->right;

            if(y->color == 'R') {

                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R'; 
                z = z->parent->parent; 
            }

            else {

                if(z == z->parent->right) {

                    z = z->parent;
                    leftRotate(z);
                }

                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(z->parent->parent);
            }
        }

        else {

            y = z->parent->parent->left;

            if(y->color == 'R') {

                z->parent->color = 'B';
                y->color = 'B'; 
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }

            else {

                if(z == z->parent->left) {

                    z = z->parent;
                    rightRotate(z);
                }

                z->parent->color = 'B'; 
                z->parent->parent->color = 'R';
                leftRotate(z->parent->parent);
            }
        }
    }

    root->color = 'B';
}


/*
 * @brief - If RBTree is unbalanced, this function will reorder it properly.
 *    
 * @param - Node* x -> Node to be rotated from the right, to left side of tree.
 *
 * @return - none
 *
 */
void RBTree::leftRotate(Node* x) {

    Node *y = x->right;
    x->right = y->left;

    if(y->left != nil) {

        y->left->parent = x; 
    }
    
    y->parent = x->parent; 

    if(x->parent == nil) {

        root = y;
    }

    else if(x == x->parent->left) {

        x->parent->left = y;
    }

    else {

        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y; 
}


/*
 * @brief - If RBTree is unbalanced, this function will reorder it properly.
 *    
 * @param - Node* x -> Node to be rotated from the left, to right side of tree.
 *
 * @return - none
 *
 */
void RBTree::rightRotate(Node* x) {

    Node *y = x->left;
    x->left = y->right;

    if(y->right != nil) {

        y->right->parent = x; 
    }
    
    y->parent = x->parent; 

    if(x->parent == nil) {

        root = y;
    }

    else if(x == x->parent->right) {

        x->parent->right = y;
    }

    else {

        x->parent->left = y;
    }
    
    y->right = x;
    x->parent = y; 
}


/*
 * @brief - Takes in key parameter and looks for nodes with same key.
 *    
 * @param - key -> key value of node data we want to find.
 *
 * @return - results -> returns node with same key & its data.
 *
 */
vector<const string*> RBTree::rbFind(const string& key) {

    vector<const string*> results;
    Node *x = rbTreeSearch(root, key);

    if(x != nil) {

    	results.push_back(x->value);
    	Node* y = rbTreePredecessor(x);

    	while((y != nil) && (*(y->key) == key)) {

    		results.push_back(y->value);
    		y = rbTreePredecessor(y);
    	}

    	y = rbTreeSuccessor(x);

    	while((y != nil) && (*(y->key) == key)) {

    		results.push_back(y->value);
    		y = rbTreeSuccessor(y);
    	}
    }

    return results;
}


/*
 * @brief - Searches RBTree for the node data of the requested key value.
 * If no key found, function returns nil.
 *    
 * @param - Node* x -> Node to be searched for
 * @param - key -> Data to be searched for
 *
 * @return - Either the requested node or nil if not found.
 *
 */
RBTree::Node* RBTree::rbTreeSearch(Node* x, const string& key) {

    if((x == nil) || (key == *(x->key))) {

        return x;
    }

    if(key < *(x->key)) {

        return rbTreeSearch(x->left, key); 
    }

    else {

        return rbTreeSearch(x->right, key); 
    }

}


/*
 * @brief - Deletes all instances of matching key-value pair
 *    
 * @param - key -> Data to be deleted from RBTree
 * @param - value -> Value of the data to be deleted from RBTree
 *
 * @return - none
 *
 */
void RBTree::rbDelete(const string& key, const string& value) {

	vector<Node*> results;
	Node* x = rbTreeSearch(root, key);

	if(x != nil) {

		if(*(x->value) == value) {

			results.push_back(x);
		}

		Node* y = rbTreePredecessor(x);

		while((y != nil) && (*(y->key) == key)) {

			if(*(y->value) == value) {

				results.push_back(y);
				y = rbTreePredecessor(y);
			}
		}
	}

	Node* toDelete;

	while(!(results.empty())) {

		toDelete = results.back();
		rbDelete(results.back());
		results.pop_back();
		delete toDelete;
	}
}


/*
 * @brief - Deletes the node and deletes it from tree
 *    
 * @param - Node* z -> Node to be deleted from tree
 *
 * @return - none
 *
 */
void RBTree::rbDelete(Node* z) {

	Node* y = z;
	Node* x;

	char yoc = y->color;

	if(z->left == nil) {

		x = z->right;
		rbTransplant(z, z->right);
	}

	else if(z->right == nil) {

		x = z->right;
		rbTransplant(z, z->left);
	}

	else{

		y = rbTreeMaximum(z->left);
		yoc = y->color;
		x = y->left;

		if(y->parent == z) {

			x->parent = y;
		}

		else{

			rbTransplant(y, y->left);
			y->left = z->left;
			y->left->parent = y;
		}

		rbTransplant(z,y);
		y->right = z->right;
		y->right->parent = y;
		y->color = z->color;
	}

	if(yoc == 'B') {

		rbDeleteFixup(x);
	}
}


/*
 * @brief - Reforms and maintains Red-Black Tree properties after a delete
 *    
 * @param - Node* x -> Node to start fixup upon
 *
 * @return - none
 *
 */
void RBTree::rbDeleteFixup(Node* x) {

    Node *w;

    while(x != root && x->color == 'B') {

        if(x == x->parent->left) {

            w = x->parent->right;

            if(w->color == 'R') {

                w->color = 'B'; 
                x->parent->color = 'R';
                leftRotate(x->parent);
                w = x->parent->right;
            }

            if(w->left->color == 'B' && w->right->color == 'B') {

                w->color = 'R'; 
                x = x->parent;
            }

            else {

                if(w->right->color == 'B') {

                    w->left->color = 'B'; 
                    w->color = 'R'; 
                    rightRotate(w);
                    w = x->parent->right; 
                }

                w->color = x->parent->color;
                x->parent->color = 'B'; 
                w->right->color = 'B';
                leftRotate(x->parent);
                x = root; 
            }
        }

        else {

            w = x->parent->left;

            if(w->color == 'R') {

                w->color = 'B';
                x->parent->color = 'R';
                rightRotate(x->parent);
                w = x->parent->left; 
            }

            if((w->right->color == 'B') && (w->left->color == 'B')) {

            	w->color = 'R';
            	x = x->parent;
            }

            else {

            	if(w->left->color == 'B') {

            		w->right->color = 'B';
            		w->color = 'R';
            		leftRotate(w);
            		w = x->parent->left;
            	}

            	w->color = x->parent->color;
            	x->parent->color = 'B';
            	w->left->color = 'B';
            	rightRotate(x->parent);
            	x = root;
            }
        }
    }

    x->color = 'B';
}


/*
 * @brief - Transplants subtree v at u's location
 *
 * @param - Node* u -> Location to transplant tree onto
 * @param - Node* v -> Subtree root to transplant
 *
 * @return - none
 *
 */
void RBTree::rbTransplant(Node* u, Node* v) {

    if(u->parent == nil) {

        root = v;
    }

    else if(u == u->parent->left) {

        u->parent->left = v; 
    }

    else {

        u->parent->right = v; 
    }

    v->parent = u->parent; 
}


/*
 * @brief - Returns a pointer to the smallest node in the tree
 *    
 * @param - Node* x -> Smallest current node on the tree
 *
 * @return - x -> Left child of the current node passed in (smallest on tree)
 *
 */
RBTree::Node* RBTree::rbTreeMinimum(Node* x) {

    while(x->left != nil) {

        x = x->left;
    }

    return x;
}


/*
 * @brief - Returns a pointer to the largest node in the tree
 *    
 * @param - Node* x -> Largest current node on the tree
 *
 * @return - x -> Right child of the current node passed in (largest on tree)
 *
 */
RBTree::Node* RBTree::rbTreeMaximum(Node* x) {

    while(x->right != nil) {

        x = x->right;
    }

    return x;
}


/*
 * @brief - Returns a pointer to the successor of the given node
 *    
 * @param - Node* x -> Node whose successor we want to find
 *
 * @return - y -> Successor of the given node
 *
 */
RBTree::Node* RBTree::rbTreeSuccessor(Node* x) {

    Node *y;

    if(x->right != nil) {

        return rbTreeMinimum(x->right);
    }
    
    y = x->parent;

    while(y != nil && x == y->right) {

        x = y;
        y = y->parent;
    }

    return y; 
}


/*
 * @brief - Returns a pointer to the predecessor of the given node
 *    
 * @param - Node* x -> Node whose predecessor we want to find
 *
 * @return - y -> predecessor of the given node
 *
 */
RBTree::Node* RBTree::rbTreePredecessor(Node* x) {

    Node *y;

    if(x->left != nil) {

        return rbTreeMaximum(x->left);
    }
    
    y = x->parent;

    while(y != nil && x == y->left) {

        x = y;
        y = y->parent;
    }

    return y; 
}


/*
 * @brief - Recursively destroys all nodes in tree
 *    
 * @param - Node* x -> Node we'd like to delete
 *
 * @return - x -> deallocation of RBTree
 *
 */
void RBTree::nodeDestroy(Node* x) {
    
    if(x != nil) {

        nodeDestroy(x->left);
        nodeDestroy(x->right); 
        delete x; 
    }
}



/*
 * Calls reverseInOrderPrint(), starts at 
 * root with depth of 0.  
*/

/*
 * @brief - Calls reverseInOrderPrint() function, starting at 0
 *    
 * @param - None
 *
 * @return - Prints out the RBTree
 *
 */
void RBTree::rbPrintTree() {

    reverseInOrderPrint(root, 0); 
}


/*
 * @brief - Prints out elements in the tree. Dr. Challinger wrote this.
 *    
 * @param - Node* x -> Node we'd like to start the print function from.
 * @param - depth -> Depth of current node on tree, for formatting.
 *
 * @return - An inorder RBTree, printed sideways.
 *
 */
void RBTree::reverseInOrderPrint(Node *x, int depth) {

	if (x != nil) {

		reverseInOrderPrint(x->right, depth + 1);
		cout << setw(depth*4+4) << x->color << " ";
		cout << *(x->key) << " " << *(x->value) << endl;
		reverseInOrderPrint(x->left, depth + 1);

	}
}
