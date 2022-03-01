#pragma once
#include <iostream>

template <typename tData>
class LinkedList{
private:
	struct ListNode {
		tData val;
		ListNode* next;
		ListNode(const tData& _val) : val(_val), next(nullptr) {}

	};

	ListNode* head;


	int countNodes(ListNode* head) {

		int count = 0;
		ListNode* temp = head;
		while (temp != nullptr) {
			count++;
			temp = temp->next;
		}
		return count;
	}

	ListNode* ReverseInKGroups(ListNode* head, int k) {
		if (countNodes(head) < k) {
			return head;
		}

		int count = 0;
		ListNode* curr = head;
		ListNode* prev = nullptr;
		ListNode* nextNode = nullptr;

		while (count < k) {
			nextNode = curr->next;
			curr->next = prev;
			prev = curr;
			curr = nextNode;
			count++;
		}

		ListNode* revChunkHead = prev;
		while (revChunkHead->next != nullptr) {
			revChunkHead = revChunkHead->next;
		}

		revChunkHead->next = ReverseInKGroups(nextNode, k);
		return prev;
	}

	ListNode* RotateCounterClockwiseByN(ListNode* head, int n) {

		if (head == nullptr) {
			return head;
		}

		/*Making List circular*/
		ListNode* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = head;

		int count = 0;
		while (count < n) {
			head = head->next;
			current = current->next;
			count++;
		}

		current->next = nullptr;
		return head;

	}

public:
	LinkedList() {
		head = nullptr;
	}

	void InsertFront(const tData& val) {
		ListNode* newNode = new ListNode(val);
		if (head == nullptr) {
			head = newNode;
			return;
		}
		newNode->next = head;
		head = newNode;
	}

	void InsertAtEnd(const tData& val) {

		ListNode* newNode = new ListNode(val);
		if (head == nullptr) {
			head = newNode;
			return;
		}

		ListNode* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}

		current->next = newNode;

	}

	void Delete(const tData& val) {

		if (head == nullptr) {
			std::cout << "List is empty \n";
			return;
		}

		if (head != nullptr && head->val == val) {
			ListNode* tempHead = head;
			head = head->next;
			delete tempHead;
			return;
		}

		ListNode* current = head;
		ListNode* previous = nullptr;

		while (current != nullptr && current->val != val) {
			previous = current;
			current = current->next;
		}

		if (current == nullptr) {
			std::cout << "Value to delete not found in list";
			return;
		}

		previous->next = current->next;
		delete current;
	}

	void Reverse() {
		ListNode* current = head;
		ListNode* prev = nullptr;
		ListNode* nextNode = nullptr;

		while (current != nullptr) {
			nextNode = current->next;
			current->next = prev;
			prev = current;
			current = nextNode;
		}

		head = prev;
	}

	void ReverseInKNodes(int k) {
		head = ReverseInKGroups(head, k);
	}

	void RotateByN(int n) {
		head = RotateCounterClockwiseByN(head, n);
	}

	void printList() {
		ListNode* current = head;
		while (current != nullptr) {
			std::cout << current->val << " ";
			current = current->next;
		}
	}


};	