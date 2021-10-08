#include "Node.h"
#include "DoublyLinkedList.h"

#define print linkedlist.PrintList()

int main() {
	
	DoublyLinkedList<int> linkedlist = { 1, 2, 3, 4, 5, 6, 20 };
	print;
	linkedlist.Append(25);
	print;

	linkedlist.Delete(2);
	print;

	std::cout << linkedlist.FindNode(5)->GetData() << std::endl;
	int length = linkedlist.Length();

	linkedlist.DeleteAt(length-1);
	print;
	std::cout << linkedlist.FindNode(4, false)->GetData() << std::endl;

	std::cout << "Largest key: " << linkedlist.FindLargestKey() << std::endl;

	return 0;
 }
