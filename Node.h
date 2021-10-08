#pragma once
//included for the use of NULL
#include <cstddef>

//template to add any data type
template <typename T>
//class node holds key, data, next ptr, and previous ptr.
class Node
{
public:
	//two constructors
	Node();
	//this constructor initializes the key and value
	Node(int k, T v);

	//these are the set and get methods for the four pieces of data. 
	void SetKey(int k);
	int GetKey();
	void SetData(T v);
	T GetData();
	void SetNext(Node<T>* n);
	Node<T>* GetNext();
	void SetPrevious(Node<T>* n);
	Node<T>* GetPrevious();


private:
	//this data is private for encapsulation
	int key;
	T data;
	Node<T>* next;
	Node<T>* previous;
};

template<typename T>
Node<T>::Node() {
	//initialze key and data to nothing and 0
	key = 0;
	data = NULL;
	next = nullptr;
	previous = nullptr;
}

template<typename T>
Node<T>::Node(int k, T v) {
	//initialze key and data to the incoming values
	key = k;
	data = v;
	next = nullptr;
	previous = nullptr;
}

template<typename T>
void Node<T>::SetKey(int k) {
	key = k;
}
template<typename T>
int Node<T>::GetKey() {
	return key;
}

template<typename T>
void Node<T>::SetData(T v) {
	data = v;
}
template<typename T>
T Node<T>::GetData() {
	return data;
}

template<typename T>
void Node<T>::SetNext(Node<T>* n) {
	next = n;
}
template<typename T>
Node<T>* Node<T>::GetNext() {
	return next;
}

template<typename T>
void Node<T>::SetPrevious(Node<T>* n) {
	previous = n;
}
template<typename T>
Node<T>* Node<T>::GetPrevious() {
	return previous;
}
