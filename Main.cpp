#include <iostream>
#include "Node.h"
#include "DoublyLinkedList.h"

int main() {

	DoublyLinkedList<int> linklist = { 1, 2, 3 };

	std::cout << "Largest Key: " << linklist.FindLargestKey() << std::endl;

	linklist.Append(10);

	return 0;
}