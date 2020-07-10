//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Derek Bomboy 
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab6-2 
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include "CSVparser.hpp"


using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================


// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// forward declarations
double strToDouble(string str, char ch);
void displayBid(Bid bid);
 
struct Node {
    Bid dataVal;
    Node* right;
    Node* left;
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

  private:
    bool hasRoot;
    Node* root;
    void addNode(Node* node, Bid bid);
    Node* removeNode(Node* node, string bidId);
    void RecurseBinTree(Node* node, int mode);
    public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Node* Search(string bidId);
    Bid bidSearch(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
  hasRoot = false;
  root = NULL;
  return;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    RecurseBinTree(root, 1);
}

/**
 * recursively Traverse the tree in order
 */
void BinarySearchTree::RecurseBinTree(Node* node, int mode = 0){
  if(node !=NULL){
    if(node->left){
      RecurseBinTree(node->left); 
    }
    if(mode == 0 ){
      displayBid(node->dataVal);
    }
    else{
      delete node;
    }
    if(node->right){
      RecurseBinTree(node->right);
    }
   }
   else{
    return;
   }
}

void BinarySearchTree::InOrder() {
    RecurseBinTree(root);
}
/**
 * Insert a bid into binary search tree
 */
void BinarySearchTree::Insert(Bid bid) {
  Node *curr = new Node;
  Node *tempL = new Node;
  Node *tempR = new Node;
  if(!hasRoot){ //adds root Node if none exists
    root = curr;
    root->dataVal = bid;
    root->left = NULL;
    root->right = NULL;
    hasRoot = true;
  }
  else{
    curr = root;
    while(true){ //finds the proper place to put the node
      if(strToDouble(bid.bidId, 'm') < strToDouble(curr->dataVal.bidId, 'M')){
        if(curr->left == 0){
          curr->left = tempL;
          addNode(tempL, bid);
          break;
        }
        else{
          curr = curr->left;
        }
      }
     else{
       if(curr->right == 0){
        curr->right = tempR;
        addNode(tempR, bid);
        break;
       }
       else{
        curr = curr->right;
       }
     }
      }
    }
   return;
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
  Node* node = new Node;
  Node* temp = new Node;
  node = Search(bidId);
  if(node == 0){//Could not find the node to be deleted
    cout << "Bid ID: " << bidId << " not found could not remove." << endl;
    return;
  }
  if(node->left == 0 && node->right == 0){ //deletes a leaf
    delete node;
  }
  else if(node->left != 0 && node->right != 0){ //deletes a 2 child parent node
    temp = node->right;
    while(temp->left!=0){
      temp=temp->left;
    }
    delete node;
    node = temp;
    temp = NULL;
  }
  else if(node->right == 0 && node->left != 0){ //deletes a single child parent
    temp = node->left;
    delete node;
    node = temp;
    temp = NULL;
  }
  else if(node->left == 0 && node->right != 0){ //deletes a single child parent
    temp = node->right;
    delete node;
    node = temp;
    node = NULL;
  }
  else{
    cout << "Bid ID: " << bidId << " not found could not remove." << endl;
    return;
  }
  cout << "Bid ID: " << bidId << " removed" << endl;
}

/**
 * Search for a node
 */
Node* BinarySearchTree::Search(string bidId) {
  Node* crr = new Node;
  crr = root;
  int i = 0;
  while(true){
      if(crr == NULL){
        break;
      }
      else{
        if(crr->dataVal.bidId.compare(bidId) == 0){
          break;
        }
        else if(strToDouble(bidId, 'M') > strToDouble(crr->dataVal.bidId, 'M')){
          crr = crr->right;
        }
        else if(strToDouble(bidId, 'M') < strToDouble(crr->dataVal.bidId, 'M')){
          crr = crr->left;
        }
      }
      i++;
    }
    
    return crr;
}
/**
 *returns bid from a searched for node
 */

Bid BinarySearchTree::bidSearch(string bidId){
  Bid bid;
  Node* temp = Search(bidId);
  if(temp != 0){
     bid = Search(bidId)->dataVal;
  }
  return bid;
}
/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    node->dataVal = bid;
    node->left = NULL;
    node->right = NULL;
    return;
}
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;
            // push this bid to the end
             bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst= new BinarySearchTree();

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->bidSearch(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
