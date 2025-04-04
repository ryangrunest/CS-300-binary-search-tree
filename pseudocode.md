# Pseudocode for BinarySearchTree.cpp

## Overview
This program implements a Binary Search Tree (BST) to store and manage bids. It includes functionality to load bids from a CSV file, display bids, search for a specific bid, and remove a bid. The program also provides a menu-driven interface for user interaction.

---

## Data Structures

### `Bid`
- A structure to hold bid information:
  - `bidId`: Unique identifier for the bid.
  - `title`: Title of the bid.
  - `fund`: Fund associated with the bid.
  - `amount`: Amount of the bid.

### `Node`
- A structure representing a node in the BST:
  - `bid`: A `Bid` object stored in the node.
  - `left`: Pointer to the left child node.
  - `right`: Pointer to the right child node.

### `BinarySearchTree`
- A class implementing the BST:
  - **Private Members**:
    - `root`: Pointer to the root node of the tree.
    - Helper methods for recursive operations:
      - `addNode(Node* node, Bid bid)`: Adds a bid to the tree.
      - `inOrder(Node* node)`: Traverses the tree in in-order.
      - `postOrder(Node* node)`: Traverses the tree in post-order.
      - `preOrder(Node* node)`: Traverses the tree in pre-order.
      - `removeNode(Node* node, string bidId)`: Removes a node with the specified bid ID.
  - **Public Members**:
    - `BinarySearchTree()`: Constructor to initialize the tree.
    - `~BinarySearchTree()`: Destructor to clean up the tree.
    - `InOrder()`: Public method to perform in-order traversal.
    - `PostOrder()`: Public method to perform post-order traversal.
    - `PreOrder()`: Public method to perform pre-order traversal.
    - `Insert(Bid bid)`: Inserts a bid into the tree.
    - `Remove(string bidId)`: Removes a bid from the tree.
    - `Search(string bidId)`: Searches for a bid by its ID.

---

## Functions

### `displayBid(Bid bid)`
- Outputs the details of a bid to the console.

### `loadBids(string csvPath, BinarySearchTree* bst)`
- Loads bids from a CSV file into the BST:
  1. Open the CSV file.
  2. Parse each row to create a `Bid` object.
  3. Insert the bid into the BST.

### `strToDouble(string str, char ch)`
- Converts a string to a double after removing a specified character (e.g., `$`).

---

## Main Function

### `main(int argc, char* argv[])`
1. **Process Command-Line Arguments**:
   - If 1 argument is provided, use it as the CSV file path and set a default bid key.
   - If 2 arguments are provided, use the first as the CSV file path and the second as the bid key.
   - Otherwise, use default values for the CSV file path and bid key.

2. **Initialize Variables**:
   - `ticks`: Timer variable for performance measurement.
   - `bst`: Pointer to a `BinarySearchTree` object.
   - `bid`: A `Bid` object for storing search results.

3. **Display Menu**:
   - Loop until the user chooses to exit:
     - **Option 1**: Load bids from the CSV file into the BST.
       - Measure and display the time taken to load the bids.
     - **Option 2**: Display all bids in the BST using in-order traversal.
     - **Option 3**: Search for a bid by its ID.
       - Measure and display the time taken for the search.
       - Display the bid details if found, or an error message if not found.
     - **Option 4**: Remove a bid by its ID.
     - **Option 9**: Exit the program.

4. **Clean Up**:
   - Delete the `BinarySearchTree` object.

5. **Exit**:
   - Display a goodbye message and terminate the program.

---

## BinarySearchTree Methods

### `Insert(Bid bid)`
- If the tree is empty, create a new root node.
- Otherwise, call `addNode` to recursively find the correct position for the bid.

### `addNode(Node* node, Bid bid)`
- If the bid's ID is less than the current node's ID:
  - If the left child is null, create a new node.
  - Otherwise, recurse into the left subtree.
- If the bid's ID is greater or equal:
  - If the right child is null, create a new node.
  - Otherwise, recurse into the right subtree.

### `Search(string bidId)`
- Start from the root and traverse the tree:
  - If the bid ID matches the current node, return the bid.
  - If the bid ID is smaller, go to the left subtree.
  - If the bid ID is larger, go to the right subtree.
- If the bid is not found, return an empty bid.

### `Remove(string bidId)`
- Call `removeNode` to recursively find and remove the node with the specified bid ID.

### `removeNode(Node* node, string bidId)`
- Traverse the tree to find the node to remove.
- Handle four cases:
  1. Node has no children: Delete the node.
  2. Node has only a right child: Replace the node with its right child.
  3. Node has only a left child: Replace the node with its left child.
  4. Node has two children:
     - Find the smallest node in the right subtree.
     - Copy its data to the current node.
     - Remove the smallest node from the right subtree.

### Traversal Methods (`InOrder`, `PostOrder`, `PreOrder`)
- Call the corresponding private recursive method (`inOrder`, `postOrder`, `preOrder`) starting from the root.
- Each recursive method processes the nodes in the specified order and outputs their bid information.

---

## Notes
- The program uses the `CSVparser` library to parse CSV files.
- The `strToDouble` function is used to handle bid amounts stored as strings with special characters (e.g., `$`).
- The menu-driven interface allows users to interact with the BST and perform various operations.