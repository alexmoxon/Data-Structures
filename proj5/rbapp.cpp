/*
 * @file rbapp.cpp - instantiates RBapp and calls mainLoop() function until 
 * end of user input.
 *
 * @author - Alex Moxon
 *
 * @date - April 17th 2019
 *
 */

#include "rbtree.h" 
#include "rbapp.h"
#include <string> 
#include <iostream> 

using std::string;
using std::cin;
using std::cout;
using std::endl;
using namespace std; 


//Splitting first word off input string
string first_word(string& str);
//Splits the input string at first instance of a space to get key and data
void splitString(string& in, string& out1, string& out2); 


/*
 * @brief - Main loop which initializes our RBTree and calls mainloop() function
 *    
 * @param - none
 *
 * @return - 0
 *
 */
int main(void) {

    RBapp rbapp;
    rbapp.mainLoop();
    
    return 0; 
}


/*
 * @brief - RBTree main loop function that processes command line input
 *    
 * @param - none
 *
 * @return - none
 *
 */
void RBapp::mainLoop(void) {

    string input = "";

    do {

    } while (getline(cin, input) && processCommand(input));
}


/*
 * @brief - RBTree main loop function that processes command line input
 *    
 * @param - input -> String taken from command line input
 *
 * @return - bool -> For mainLoop() used if quit command has been passed.
 *
 */
bool RBapp::processCommand(string& input) {

    string cmd = "", keyyo = "";
    splitString(input, cmd, keyyo);

    if (cmd == "insert") {

        processInsert(keyyo);
    }

    else if (cmd == "find") {

        processFind(keyyo);
    }

    else if (cmd == "delete") {

        processDelete(keyyo);
    }

    else if (cmd == "print") {

        processPrint();
    }

    else if (cmd == "quit") {

        return false;
    }

    return true;
}


/*
 * @brief - Takes input and splits at first instance of a space, into two
 * seperate strings (key and data). Then inserts the key and data into 
 * the RBTree
 *    
 * @param - str -> String taken from command line input, minus command
 *
 * @return - none
 *
 */
void RBapp::processInsert(string& str) {

    string key = "", data = "";
    splitString(str, key, data);
    myRBT.rbInsert(key, data);

}


/*
 * @brief - Calls the print function for our RBTree
 *    
 * @param - none
 *
 * @return - Prints RBTree sideways
 *
 */
void RBapp::processPrint() {

    myRBT.rbPrintTree();
}


/*
 * @brief - Calls the search function in rbtree.cpp to find a specific node
 *    
 * @param - keyyo -> key-value pair in RBTree
 *
 * @return - Prints out data of all the nodes with matching key-values
 *
 */
void RBapp::processFind(string& keyyo) {

    string key = "";
    key = keyyo;

    vector<const string*> results = myRBT.rbFind(key);

    for (auto str_ptr : results) {

        cout << key << " " << *(str_ptr) << endl;
    }
}


/*
 * @brief - Calls the delete function with the nodes with 
 * a matching key and data value in RBTree
 *    
 * @param - str -> String that we split, getting key and data values to delete
 *
 * @return - None
 *
 */
void RBapp::processDelete(string& str) {

    string key = "", data = "";
    splitString(str, key, data);
    myRBT.rbDelete(key, data);

}


/*
 * @brief - Trims a string to the first word only.
 * If the string has no spaces, returns as-is
 *
 * @param - str -> the input string to trim
 *
 * @return - the first word of the string
 *
 */
string first_word(string& str) {

    string out1 = "", out2 = "";
    splitString(str, out1, out2);
    return out1;
}


/*
 * @brief - Takes an input string and splits it at the first space
 * into two substrings. If no spaces, entire string is put into out1
 *
 * @param - in -> the input string to trim
 * @param - out1 -> the first substring to return (key_value)
 * @param - out2 -> the second substring to return (data)
 *
 * @return - A split string into key_value and data
 *
 */
 void splitString(string& in, string& out1, string& out2) {

    unsigned int i = 0;
    out1 = "";
    out2 = "";

    while (i < in.length() && in.substr(i,1) != " ") {

        out1 += in.substr(i,1);
        i++;
    }

    i++;

    if (i < in.length()) {

        out2 = in.substr(i);
    }
 }