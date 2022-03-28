#pragma once
#include<iostream>
#include<exception>

class EmptyHeapException : std::exception {
public:
	EmptyHeapException() {};
	const char* what() const noexcept override {
		return "Heap is empty";
	}
};

template<class tData>
class MinHeap {
private:
	int size;
	int capacity;
	tData* heap;

	int left(int index) {
		return 2 * index + 1;
	}
	int right(int index) {
		return 2 * index + 2;
	}
	int parent(int index) {
		return (index - 1) / 2;
	}

	void heapify(int index) {
		int leftInd = left(index);
		int rightInd = right(index);
		int smallest = index;

		if (leftInd < size && heap[leftInd] < heap[smallest]) {
			smallest = leftInd;
		}

		if (rightInd < size && heap[rightInd] < heap[smallest]) {
			smallest = rightInd;
		}

		if (smallest != index) {
			std::swap(heap[smallest], heap[index]);
			heapify(smallest);
		}
	}

public:
	MinHeap(int _capacity) : capacity(_capacity) {
		heap = new tData[capacity];
		this->size = 0;
	}

	~MinHeap() {
		delete[] heap;
	}

	void push(const tData& value) {
		if (size == capacity) {
			std::cout << "Heap size is full. Cannot insert";
			return;
		}

		size++;
		int index = size - 1;
		heap[index] = value;

		while (index != 0 && heap[parent(index)] > heap[index]) {
			std::swap(heap[parent(index)], heap[index]);
			index = parent(index);
		}
	}

	void pop() {
		if (size == 0) {
			std::cout << "Heap is empty";
			return;
		}

		heap[0] = heap[size - 1];
		size--;

		heapify(0);
	}

	tData top() {
		if (size == 0) {
			std::cout << "Heap is empty";
			throw EmptyHeapException{};
		}
		return heap[0];
	}

	bool Empty() {
		return size == 0;
	}

};
