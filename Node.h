#pragma once
#include <cstddef>

template <typename T>
class Node
{
public:

	Node();
	Node(int k, T v);
	
	void SetKey(int k);
	int GetKey();
	
	void SetData(T v);
	T GetData();
	
	void SetNext(Node<T>* n);
	Node<T>* GetNext();
	
	void SetPrevious(Node<T>* n);
	Node<T>* GetPrevious();
	

private:
	int key;
	T data;
	Node<T>* next;
	Node<T>* previous;
};

template<typename T>
Node<T>::Node() {
	//initialze key and data
	key = 0;
	data = NULL;
	next = nullptr;
	previous = nullptr;
}

template<typename T>
Node<T>::Node(int k, T v) {
	//initialze key and data
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