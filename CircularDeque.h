#pragma once
#include <exception>
#include <iostream>

class EmptyDequeException : std::exception {
public:
	EmptyDequeException() {};
	const char* what() const noexcept override {
		return "Deque is Empty";
	}
};

class FullDequeException : std::exception {
public:
	FullDequeException() {};
	const char* what() const noexcept override {
		return "Deque is full";
	}
};

template<typename tData>
class CircularDeque {
private:
	int front;
	int rear;
	tData* deque;
	int size;

public:
	CircularDeque(int _size) {
		this->size = _size;
		front = -1;
		rear = -1;
		deque = new tData[size];
	}

	~CircularDeque() {
		delete[] deque;
	}

	bool empty() {
		return (front == -1 && rear == -1);
	}

	bool isFull() {
		return (rear + 1) % size == front;
	}

	void push_Front(const tData& value) {
		if (isFull()) {
			throw FullDequeException{};
		}

		if (empty()) {
			front = 0;
			rear = 0;
		}
		else if (front == 0) {
			front = size - 1;
		}
		else {
			front--;
		}
		deque[front] = value;
	}

	void push_Back(const tData& value) {
		if (isFull()) {
			throw FullDequeException{};
		}

		if (empty()) {
			front = 0;
			rear = 0;
		}
		else {
			rear = (rear + 1) % size;
		}

		deque[rear] = value;
	}

	void pop_front() {
		if (empty()) {
			throw EmptyDequeException{};
		}

		if (front == rear) {
			front = -1;
			rear = -1;
		}
		else {
			front = (front + 1) % size;
		}
	}

	void pop_back() {
		if (empty()) {
			throw EmptyDequeException{};
		}

		if (front == rear) {
			front = -1;
			rear = -1;
		}
		else if (rear == 0) {
			rear = size - 1;
		}
		else {
			rear--;
		}
	}

	tData getFront() {
		if (empty()) {
			throw EmptyQueueException{};
		}
		return deque[front];
	}

	tData getRear() {
		if (empty()) {
			throw EmptyQueueException{};
		}
		return deque[rear];
	}

	void Display() {
		if (empty()) {
			throw EmptyQueueException{};
		}
		int fr = front;
		while (fr != rear) {
			std::cout << deque[fr] << " ";
			fr = (fr + 1) % size;
		}
		std::cout << deque[fr];
	}

};
