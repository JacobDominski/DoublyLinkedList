#pragma once
#include "Node.h"
#include <initializer_list>
#include <iostream>

template <typename T>
class DoublyLinkedList
{
public:

	DoublyLinkedList();
	DoublyLinkedList(std::initializer_list<T> list);
	~DoublyLinkedList();

	Node<T>* NodeExists(int key);
	void Append(T v, int k = -1);
	void Prepend(T v, int k = -1);
	int FindLargestKey();
	void PrintList();

private:
	Node<T>* head;
};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	std::cout << "Linked List Created!" << std::endl;
	head = nullptr;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> list) {
	std::cout << "Initial Elements: " << std::endl;
	for (auto it = list.begin(); it != list.end(); ++it) {
		//check if it's the first one
		if (it == list.begin()) {
			//initialize the head
			head = new Node<T>(0, *it);
		}
		else {
			//create new nodes
			this->Append(*it);
		}
	}
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node<T>* node = head;
	while (node != nullptr) {
		Node<T>* next = node->GetNext();
		delete node;
		node = next;
	}
	std::cout << "Deleted all the nodes" << std::endl;
}

template<typename T>
Node<T>* DoublyLinkedList<T>::NodeExists(int key) {
	Node<T>* temp = nullptr;
	Node<T>* ptr = head;

	while (ptr != nullptr) {
		if (ptr->GetKey() == key) {
			temp = ptr;
		}
		ptr = ptr->GetNext();
	}

	return temp;
}

template<typename T>
void DoublyLinkedList<T>::Append(T v, int k) {
	//check if k is not defined or an invalid value
	if (k < 0) {
		//set k to the highest key value + 1
		k = this->FindLargestKey() + 1;
	}
	//create new node
	Node<T>* node = new Node<T>(k, v);
	//check if a node with a key already exists, if it does, don't append the node
	if (this->NodeExists(node->GetKey()) == nullptr) {
		if (head == nullptr) {
			head = node;
		}
		else {
			Node<T>* ptr = head;
			while (ptr->GetNext() != nullptr) {
				ptr = ptr->GetNext();
			}
			ptr->SetNext(node);
			node->SetPrevious(ptr);
		}
	}
	else {
		std::cout << "ERROR: Could not append node! \nKey already used (try entering a new key or leaving the argument blank)" << std::endl;
	}
}

template<typename T>
void DoublyLinkedList<T>::Prepend(T v, int k)
{
	if (k < 0) {
		k = this->FindLargestKey() + 1;
	}
	//create new node
	Node<T>* node = new Node<T>(k, v);

}

template<typename T>
int DoublyLinkedList<T>::FindLargestKey() {
	Node<T>* ptr = head;
	int highestKey = 0;

	while (ptr != nullptr) {
		if (ptr->GetKey() > highestKey) {
			highestKey = ptr->GetKey();
		}
		ptr = ptr->GetNext();
	}

	return highestKey;
}

template<typename T>
void DoublyLinkedList<T>::PrintList()
{
	Node<T>* ptr = head;
	int counter = 0;
	while (ptr != nullptr) {
		std::cout << "=> { key: " << ptr->GetKey() << ", data: " << ptr->GetData() << " } <=";
		if (counter % 3 == 2) {
			std::cout << std::endl;
		}
		ptr = ptr->GetNext();
		counter++;
	}
	std::cout << "\nThere are " << counter << " nodes in the linked list!" << std::endl;
}
