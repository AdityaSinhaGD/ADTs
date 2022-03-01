// ADTs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "DoublyLinkedList.h"
#include "CircularQueue.h"

template <typename tdata>
void printVector2d(const std::vector<std::vector<tdata>>& result) {

    for (const auto& vector : result) {
        for (const auto& data : vector) {
            std::cout << data << " ";
        }
        std::cout << "\n";
    }

}

int main()
{
    std::cout << "Hello World!\n";
    /*
    BinarySearchTree<int>* tree = new BinarySearchTree<int>();
    tree->Insert(9);
    tree->Insert(17);
    tree->Insert(2);
    tree->Insert(5);
    tree->Insert(-5);
    tree->Insert(1);
    tree->Insert(10);
    tree->Insert(21);

    tree->Delete(17);

    //tree->Find(-9);

    //tree->InorderSuccessorValue(2);

    std::vector<std::vector<int>> result;
    tree->LevelOrderTraversal(result);
    printVector2d(result);
    std::cout << "Diameter of tree:" << tree->Diameter();
  
    //tree->Inorder();
    delete tree;
    */

    /*
    LinkedList<int> list;
    list.InsertFront(5);
    list.InsertFront(7);
    list.InsertAtEnd(9);
    list.InsertAtEnd(19);
    list.InsertAtEnd(27);
    //list.Delete(9);
    list.printList();
    std::cout << "\n";
    //list.ReverseInKNodes(3);
    list.RotateByN(2);
    list.printList();
    */

    DoublyLinkedList<int> dList;
    dList.InsertEnd(5);
    dList.InsertEnd(6);
    dList.InsertEnd(7);
    dList.InsertEnd(8);
    dList.DeleteVal(8);
    dList.Print();
    std::cout << "\n";
    dList.PrintReverse();
    

    /*
    CircularQueue<int> queue(5);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    queue.push(6);
    queue.push(7);
    //queue.push(8);
    queue.pop();
    queue.pop();
    while (!queue.isEmpty()) {
        std::cout << queue.peekFront() << "\n";
        queue.pop();
    }
    */
  
}


