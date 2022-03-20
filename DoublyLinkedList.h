#pragma once
#include <iostream>

template<typename tData>
class DoublyLinkedList {
private:
	struct ListNode {
		tData val;
		ListNode* next;
		ListNode* prev;
		ListNode(const tData& _val) : val(_val), next(nullptr), prev(nullptr) {}

	};

	ListNode* head;
	ListNode* tail;

	void DeleteNode(ListNode* delNode) {

		if (delNode == nullptr) {
			std::cout << "Nothing to delete";
			return;
		}

		if (delNode == head) {
			head = head->next;
		}

		if (delNode == tail) {
			tail = tail->prev;
		}

		if (delNode->next != nullptr) {
			delNode->next->prev = delNode->prev;
		}

		if (delNode->prev != nullptr) {
			delNode->prev->next = delNode->next;
		}

		delete delNode;
	}

	/*linear search for now. Upgrade to 2 pointer later*/
	ListNode* FindNode(const tData& val) {
		ListNode* current = head;
		while (current != nullptr) {
			if (current->val == val) {
				break;
			}
			current = current->next;
		}
		return current;
	}

public:
	DoublyLinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	void InsertFront(const tData& val) {

		ListNode* newNode = new ListNode(val);

		/*if List is empty*/
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			return;
		}

		newNode->next = head;
		head->prev = newNode;
		head = newNode;

	}

	void InsertEnd(const tData& val) {

		ListNode* newNode = new ListNode(val);

		/*if List is empty*/
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			return;
		}

		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
		
	}

	void DeleteVal(const tData& val) {
		ListNode* delNode = FindNode(val);
		DeleteNode(delNode);
	}

	void Print() {
		ListNode* current = head;
		while (current != nullptr) {
			std::cout << current->val << " ";
			current = current->next;
		}
	}

	void PrintReverse() {
		ListNode* current = tail;
		while (current != nullptr) {
			std::cout << current->val << " ";
			current = current->prev;
		}
	}

};