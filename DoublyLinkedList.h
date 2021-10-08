#pragma once
#include "Node.h"
#include <initializer_list>
#include <iostream>

//templated linked list to define any data type
template <typename T>
class DoublyLinkedList
{
public:
	//two constructors
	DoublyLinkedList();
	DoublyLinkedList(std::initializer_list<T> list);
	//a destructor for garbage collection
	~DoublyLinkedList();

	//checks if a node exists and returns that node
	Node<T>* NodeExists(int key);
	//looks for a specific node (direction: true = right | false = left)
	Node<T>* FindNode(int key, bool direction = true);
	//appends a node to the end of the list by passing the key and value
	void Append(T v, int k = -1);
	//appends the node at the end of the list with a predefined node
	void AppendNode(Node<T>* node);
	//prepends the node to the beginning of the list with the key and value
	void Prepend(T v, int k = -1);
	//prepends the node to the beginning of the list with a predefined node
	void PrependNode(Node<T>* node);
	//inserts the node in the middle of the list by specifing a key to look for
	void Insert(T v, int keyToFind, int k = -1);
	//inserts the node in the middle of the list by specifing an index value
	void InsertAt(T v, int index, int k = -1);
	//this returns the largest key in the linked list
	int FindLargestKey();
	//this returns the smallest key in the linked list
	int FindSmallestKey();
	//this prints all the values in the linked list
	void PrintList();
	//this will delete a node by specifing the key
	void Delete(int key);
	//this will delete a node by specifing where it is in the list
	void DeleteAt(int index);
	//this deletes the node
	void DeleteNode(Node<T>* node);
	//returns the amount of nodes in the list
	int Length();

private:
	//stores the head and tail for doubly linked list
	//this makes it so you can traverse the list in both directions.
	Node<T>* head;
	Node<T>* tail;
};

//generic consturctor that initializes the head and tail
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	head = nullptr;
	tail = nullptr;
}

//consturctor with initializer list
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> list) {
	//loop that iterates through the list and appending nodes.
	for (auto it = list.begin(); it != list.end(); ++it) {
		//check if it's the first value in the list
		if (it == list.begin()) {
			//initialize the head
			Node<T>* node = new Node<T>(0, *it);
			head = node;
			//set the tail to the head because it is the end of the list
			tail = head;
		}
		//if it's not the first value in the list
		else {
			//create new nodes
			this->Append(*it);
		}
	}
}
//destructor for linked list
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	//create node for the head
	Node<T>* node = head;
	//keep looping through the list until there's no more nodes
	while (node != nullptr) {
		//get the next node
		Node<T>* next = node->GetNext();
		//delete the current node
		delete node;
		//set the current node to the next node
		node = next;
	}
	//once finished, alert the programmer that all the nodes have been cleaned up
	std::cout << "Deleted all the nodes" << std::endl;
}
//method that checks if a node is in the list
//this is separate from find node because this is used to check
//that there are no duplicate keys
template<typename T>
Node<T>* DoublyLinkedList<T>::NodeExists(int key) {
	//create two pointers of nodes and set one to the head as a starting point
	Node<T>* temp = nullptr;
	Node<T>* ptr = head;
	//continue to traverse the list until there are no more nodes
	while (ptr != nullptr) {
		//check if the current node's key is the same as the search value
		if (ptr->GetKey() == key) {
			//if so save that node in temp and continue on
			temp = ptr;
		}
		ptr = ptr->GetNext();
	}
	//return the temp whether it be a node or nullptr.
	return temp;
}
//this method looks for a node and returns it to the programmer.
//you can go in any direction. This helps the programmer with efficiency if
//the programmer knows a node is towards the beginning or end of the list.
template<typename T>
inline Node<T>* DoublyLinkedList<T>::FindNode(int key, bool direction)
{
	//declares the node first
	Node<T>* ptr;
	if (direction) {
		//if the direction is right, set the start to the head
		ptr = head;
		while (ptr != nullptr) {
			//check if the key matches the search value
			if (ptr->GetKey() == key) {
				//found the node
				return ptr;
			}
			//continue to move right
			ptr = ptr->GetNext();
		}
	}
	else {
		//if the direction is left, set the start to the tail
		ptr = tail;
		while (ptr != nullptr) {
			//check if the key matches the search value
			if (ptr->GetKey() == key) {
				//found the node
				return ptr;
			}
			//continue to move left
			ptr = ptr->GetPrevious();
		}
	}
	std::cout << "ERROR: Could not locate the specified node!\n";
	return nullptr;
}
//append method creates a node with the given values and calls the appendnode
template<typename T>
void DoublyLinkedList<T>::Append(T v, int k) {
	//check if k is not defined or an invalid value
	if (k < 0) {
		//set k to the highest key value + 1
		k = this->FindLargestKey() + 1;
	}
	//create new node
	Node<T>* node = new Node<T>(k, v);
	//calls the append node method to attatch it to the end
	this->AppendNode(node);
}
//appendnode method takes an incoming node and attatches it to the end of the list
template<typename T>
void DoublyLinkedList<T>::AppendNode(Node<T>* node)
{
	//check if a node with a key already exists, if it does, don't append the node
	if (this->NodeExists(node->GetKey()) == nullptr) {
		//if the list doesn't have any nodes
		if (head == nullptr) {
			//set the node to the head
			head = node;
		}
		//if the list has one node
		else if (this->Length() <= 1) {
			//set the tail to the node
			tail = node;
			//set the left to the head
			tail->SetPrevious(head);
			//set the head's right to the tail
			head->SetNext(tail);
			//this results in two separate nodes (head and tail)
		}
		//if the head and tail are already separate nodes
		else {
			//reset the tail
			tail->SetNext(node);
			node->SetPrevious(tail);
			tail = node;
		}
	}
	else {
		std::cout << "ERROR: Could not append node! \nKey already used (try entering a new key or leaving the argument blank)" << std::endl;
	}
}
//prepend will create a node and call the prepend node and attatch it to the beginning.
template<typename T>
void DoublyLinkedList<T>::Prepend(T v, int k)
{
	//checks if the key has not been initialized
	if (k < 0) {
		//set the key to a unique value by taking the largest key and adding one
		k = this->FindLargestKey() + 1;
	}
	//create new node
	Node<T>* node = new Node<T>(k, v);
	//calls the prepend node to attatch it to the beginning of the list
	this->PrependNode(node);
}
//prepend node will take an existing node and attatch it to the beginning of the list
template<typename T>
void DoublyLinkedList<T>::PrependNode(Node<T>* node)
{
	//first checks if the node exists before attatching it
	if (this->NodeExists(node->GetKey()) == nullptr) {
		//check if the list is empty
		if (head == nullptr) {
			//set the node to the head
			head = node;
		}
		else {
			//set this node's pointers first
			node->SetNext(head);
			//reset the head
			head->SetPrevious(node);
			//update the head to the node
			head = node;
		}
	}
	else {
		std::cout << "ERROR: Could not prepend node! \nKey already used (try entering a new key or leaving the argument blank)" << std::endl;
	}
}
//insert will let you add a node anywhere in the list by specifing the key
template<typename T>
void DoublyLinkedList<T>::Insert(T v, int keyToFind, int k)
{
	//sets the start to the head
	Node<T>* ptr = head;
	//continues until there is no more nodes
	while (ptr != nullptr) {
		//checks if the node has been found
		if (ptr->GetKey() == keyToFind) {
			//if the new node has a key that has not been initialized
			if (k < 0) {
				//set the key to the largest key + 1
				k = this->FindLargestKey() + 1;
			}
			//now has precaution, check that the key has not been used
			if (this->NodeExists(k) == nullptr) {
				//create the new node
				Node<T>* node = new Node<T>(k, v);
				//checks if there is a node after it
				if (ptr->GetNext()) {
					node->SetNext(ptr->GetNext());
					ptr->GetNext()->SetPrevious(node);
				}
				//if not then it's the end
				else {
					tail = node;
				}
				//set the nodes previous pointer to the current
				node->SetPrevious(ptr);
				//set the current next pointer to the node
				ptr->SetNext(node);
				//exit the method so it doesn't continue
				return;
			}
			else {
				//error key already in use
				std::cout << "ERROR: Could not insert node!\nKey already in use (try entering a new key or leaving the argument blank)" << std::endl;
				std::cout << "The node found has a data of " << this->NodeExists(k)->GetData() << std::endl;
				return;
			}
		}

		ptr = ptr->GetNext();
	}
	
	//error could not find node
	std::cout << "ERROR: Could not find node to insert after!\n";

}
//insert at an index in the list
template<typename T>
void DoublyLinkedList<T>::InsertAt(T v, int index, int k)
{
	//first we check to see if the list is in range
	if (index >= this->Length()) {
		std::cout << "ERROR: Index out of range\n";
		return;
	}
	//if it passes than we set the ptr to the start
	Node<T>* ptr = head;
	//continue to loop through until we get to the correct node
	for (int i = 0; i < index; i++) {
		ptr = ptr->GetNext();
	}
	//then we check the key value if it has been initialized
	if (k < 0) {
		k = this->FindLargestKey() + 1;
	}
	//create the new node based off the key and value
	Node<T>* node = new Node<T>(k, v);
	//if the ptr has a node after it we are in the middle
	if (ptr->GetNext()) {
		//set the nodes next pointer to the same as the ptr's next
		node->SetNext(ptr->GetNext());
		//set the ptr's next previous to the node
		ptr->GetNext()->SetPrevious(node);
	}
	//if not we are at the end
	else {
		//set the tail to the node at the end
		tail = node;
	}
	//set the nodes previous to link the node at it's new position
	node->SetPrevious(ptr);
	ptr->SetNext(node);
}
//this method goes through the list and finds the largest key
//the purpose of this is to find a unique key
template<typename T>
int DoublyLinkedList<T>::FindLargestKey() {
	//get the start position
	Node<T>* ptr = head;
	//initialize the highest key to the bottom
	int highestKey = 0;
	//keep looping until there are no more pointers
	while (ptr != nullptr) {
		//keep checking for a new highest key
		if (ptr->GetKey() > highestKey) {
			//set the key to the highest key
			highestKey = ptr->GetKey();
		}
		ptr = ptr->GetNext();
	}
	//return the highest key
	return highestKey;
}

template<typename T>
inline int DoublyLinkedList<T>::FindSmallestKey()
{
	//get the start
	Node<T>* ptr = head;
	//set the lowest key to -1 to show there are no nodes
	int lowestKey = -1;
	//if there are nodes, set the key to the first one
	if (ptr != nullptr) {
		lowestKey = ptr->GetKey();
	}
	//continue until there are no more nodes
	while (ptr != nullptr) {
		//if there is a new low
		if (ptr->GetKey() < lowestKey) {
			//set the variable to the lowest key
			lowestKey = ptr->GetKey();
		}
		ptr = ptr->GetNext();
	}
	//return the lowest key
	return lowestKey;
}
//method that displays all the nodes in the list
template<typename T>
void DoublyLinkedList<T>::PrintList()
{
	//set the starting position
	Node<T>* ptr = head;
	//counter to keep track of where we are in the list
	int counter = 0;
	//continue until there are no more nodes
	while (ptr != nullptr) {
		//print the key and data
		std::cout << "=> { key: " << ptr->GetKey() << ", data: " << ptr->GetData() << " } <=";
		//if this is the third node create a new line
		if (counter % 3 == 2) {
			std::cout << std::endl;
		}
		//continue to the next node
		ptr = ptr->GetNext();
		counter++;
	}
	std::cout << "\nThere are " << counter << " nodes in the linked list!" << std::endl;
}
//delete method will delete a node based on the key 
template<typename T>
void DoublyLinkedList<T>::Delete(int key)
{
	//get the starting position
	Node<T>* ptr = head; 
	//continue until there are no more nodes
	while (ptr != nullptr) {
		//once the node to delete has been found
		if (ptr->GetKey() == key) {
			//delete node
			this->DeleteNode(ptr);
			return;
		}
		//continue to the next node
		ptr = ptr->GetNext();
	}

	std::cout << "ERROR: Could not delete node! Key not found." << std::endl;
}

//index starts at 0
template<typename T>
void DoublyLinkedList<T>::DeleteAt(int index)
{
	//starting point in the linked list
	Node<T>* ptr = head;
	//check if the index is greater than the length
	if (index >= this->Length()) {
		std::cout << "ERROR: Index out of range\n";
		return;
	}
	//continue until you find the node at that index
	for (int i = 0; i < index; i++) {
		ptr = ptr->GetNext();
	}
	//call the delete node with the specified node
	this->DeleteNode(ptr);
}
//delete node from the linked list
template<typename T>
void DoublyLinkedList<T>::DeleteNode(Node<T>* node)
{
	//check to see if there's a previous node
	if (node->GetPrevious()) {
		//if the node is in the middle of the list
		if (node->GetNext()) {
			//This sets the previous nodes next value to the ptr's next value
			node->GetPrevious()->SetNext(node->GetNext());
		}
		//if the node is the tail
		else {
			//set the tail to the new node after the old one is disconnected
			tail = node->GetPrevious();
			//set the new tails next to nullptr
			node->GetPrevious()->SetNext(nullptr);
		}
		//delete the disconnected node
		delete node;
	}
	//check to see if there's a next node
	else if (node->GetNext()) {
		//if the node is in the middle of the list
		if (node->GetPrevious()) {
			//this sets the next nodes previous value to the ptr's previous value
			node->GetNext()->SetPrevious(node->GetPrevious());
		}
		//if the node is the head
		else {
			//set the head to the original head's next node
			head = node->GetNext();
			//set that new head's previous pointer to null
			node->GetNext()->SetPrevious(nullptr);
		}
		//delete the disconnected node
		delete node;
	}
	else {
		//error
		std::cout << "ERROR: Could not delete node!\n";
	}
}
//length funciton returns the amount of nodes in the linked list
template<typename T>
int DoublyLinkedList<T>::Length()
{
	//get the starting position
	Node<T>* ptr = head;
	//create counter variable to keep track of the amount of nodes counted
	int counter = 0;
	//continue until there are no more nodes
	while (ptr != nullptr) {
		//increase the counter
		counter++;
		//go to the next node
		ptr = ptr->GetNext();
	}
	//return the counted variable
	return counter;
}
