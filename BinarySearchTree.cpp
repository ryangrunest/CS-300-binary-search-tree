//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Ryan Grunest
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid
{
  string bidId; // unique identifier
  string title;
  string fund;
  double amount;
  Bid()
  {
    amount = 0.0;
  }
};

// Internal structure for tree node
struct Node
{
  Bid bid;
  Node *left;
  Node *right;

  // default constructor
  Node()
  {
    left = nullptr;
    right = nullptr;
  }

  // initialize with a bid
  Node(Bid aBid) : Node()
  {
    bid = aBid;
  }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree
{

private:
  Node *root;

  void addNode(Node *node, Bid bid);
  void inOrder(Node *node);
  void postOrder(Node *node);
  void preOrder(Node *node);
  Node *removeNode(Node *node, string bidId);

public:
  BinarySearchTree();
  virtual ~BinarySearchTree();
  void InOrder();
  void PostOrder();
  void PreOrder();
  void Insert(Bid bid);
  void Remove(string bidId);
  Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree()
{
  root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree()
{
  // recurse from root deleting every node
  while (root != nullptr)
  {
    root = removeNode(root, root->bid.bidId);
  }
  // delete root node
  delete root;
  root = nullptr;
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder()
{
  inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder()
{
  postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder()
{
  preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid)
{
  if (root == nullptr)
  {
    root = new Node(bid);
  }
  else
  {
    // Otherwise, add the bid to the appropriate position in the tree
    addNode(root, bid);
  }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId)
{
  root = removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId)
{
  // Start from the root node
  Node *current = root;

  // Traverse the tree until the bid is found or the end is reached
  while (current != nullptr)
  {
    if (bidId == current->bid.bidId)
    {
      // If the bidId matches, return the bid
      return current->bid;
    }
    else if (bidId < current->bid.bidId)
    {
      // If the bidId is smaller, go to the left subtree
      current = current->left;
    }
    else
    {
      // If the bidId is larger, go to the right subtree
      current = current->right;
    }
  }

  // If the bid is not found, return an empty bid
  return Bid();
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node *node, Bid bid)
{
  if (bid.bidId < node->bid.bidId)
  {
    // If the left child is null, create a new node
    if (node->left == nullptr)
    {
      node->left = new Node(bid);
    }
    else
    {
      // Otherwise, recurse into the left subtree
      addNode(node->left, bid);
    }
  }
  else
  {
    // If the bid's ID is greater than or equal to the current node's bid ID, go right
    if (node->right == nullptr)
    {
      node->right = new Node(bid);
    }
    else
    {
      // Otherwise, recurse into the right subtree
      addNode(node->right, bid);
    }
  }
}

/**
 * Traverse the tree in order (left, root, right)
 */
void BinarySearchTree::inOrder(Node *node)
{
  if (node != nullptr)
  {
    // Traverse the left subtree
    inOrder(node->left);

    // Output the bid information
    cout << node->bid.bidId << ": " << node->bid.title << " | "
         << node->bid.amount << " | " << node->bid.fund << endl;

    // Traverse the right subtree
    inOrder(node->right);
  }
}

/**
 * Traverse the tree in post-order (left, right, root)
 */
void BinarySearchTree::postOrder(Node *node)
{
  if (node != nullptr)
  {
    // Traverse the left subtree
    postOrder(node->left);

    // Traverse the right subtree
    postOrder(node->right);

    // Output the bid information
    cout << node->bid.bidId << ": " << node->bid.title << " | "
         << node->bid.amount << " | " << node->bid.fund << endl;
  }
}

/*
 * Traverse the tree in pre-order
 */
void BinarySearchTree::preOrder(Node *node)
{
  if (node != nullptr)
  {
    // Output the bid information
    cout << node->bid.bidId << ": " << node->bid.title << " | "
         << node->bid.amount << " | " << node->bid.fund << endl;

    // Traverse the left subtree
    preOrder(node->left);

    // Traverse the right subtree
    preOrder(node->right);
  }
}

/**
 * Remove a bid from some node (recursive)
 */
Node *BinarySearchTree::removeNode(Node *node, string bidId)
{
  if (node == nullptr)
  {
    return node; // Base case: node is null
  }

  // Traverse the tree to find the node to remove
  if (bidId < node->bid.bidId)
  {
    // If the bidId is smaller, go left
    node->left = removeNode(node->left, bidId);
  }
  else if (bidId > node->bid.bidId)
  {
    // If the bidId is larger, go right
    node->right = removeNode(node->right, bidId);
  }
  else
  {
    // Node with the matching bidId found
    if (node->left == nullptr && node->right == nullptr)
    {
      // Case 1: Node has no children (leaf node)
      delete node;
      node = nullptr;
    }
    else if (node->left == nullptr)
    {
      // Case 2: Node has only a right child
      Node *temp = node;
      node = node->right;
      delete temp;
    }
    else if (node->right == nullptr)
    {
      // Case 3: Node has only a left child
      Node *temp = node;
      node = node->left;
      delete temp;
    }
    else
    {
      // Case 4: Node has two children
      // Find the minimum node in the right subtree
      Node *temp = node->right;
      while (temp->left != nullptr)
      {
        temp = temp->left;
      }
      // Copy the data from the minimum node to the current node
      node->bid = temp->bid;
      // Remove the minimum node from the right subtree
      node->right = removeNode(node->right, temp->bid.bidId);
    }
  }

  return node; // Return the updated node
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid)
{
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
void loadBids(string csvPath, BinarySearchTree *bst)
{
  cout << "Loading CSV file " << csvPath << endl;

  // initialize the CSV Parser using the given path
  csv::Parser file = csv::Parser(csvPath);

  // read and display header row - optional
  vector<string> header = file.getHeader();
  for (auto const &c : header)
  {
    cout << c << " | ";
  }
  cout << "" << endl;

  try
  {
    // loop to read rows of a CSV file
    for (unsigned int i = 0; i < file.rowCount(); i++)
    {

      // Create a data structure and add to the collection of bids
      Bid bid;
      bid.bidId = file[i][1];
      bid.title = file[i][0];
      bid.fund = file[i][8];
      bid.amount = strToDouble(file[i][4], '$');

      // cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

      // push this bid to the end
      bst->Insert(bid);
    }
  }
  catch (csv::Error &e)
  {
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
double strToDouble(string str, char ch)
{
  str.erase(remove(str.begin(), str.end(), ch), str.end());
  return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char *argv[])
{

  // process command line arguments
  string csvPath, bidKey;
  switch (argc)
  {
  case 2:
    csvPath = argv[1];
    bidKey = "98223";
    break;
  case 3:
    csvPath = argv[1];
    bidKey = argv[2];
    break;
  default:
    csvPath = "eBid_Monthly_Sales.csv";
    bidKey = "98223";
  }

  // Define a timer variable
  clock_t ticks;

  // Define a binary search tree to hold all bids
  BinarySearchTree *bst;
  bst = new BinarySearchTree();
  Bid bid;

  int choice = 0;
  while (choice != 9)
  {
    cout << "Menu:" << endl;
    cout << "  1. Load Bids" << endl;
    cout << "  2. Display All Bids" << endl;
    cout << "  3. Find Bid" << endl;
    cout << "  4. Remove Bid" << endl;
    cout << "  9. Exit" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {

    case 1:

      // Initialize a timer variable before loading bids
      ticks = clock();

      // Complete the method call to load the bids
      loadBids(csvPath, bst);

      // cout << bst->Size() << " bids read" << endl;

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

      bid = bst->Search(bidKey);

      ticks = clock() - ticks; // current clock ticks minus starting clock ticks

      if (!bid.bidId.empty())
      {
        displayBid(bid);
      }
      else
      {
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
