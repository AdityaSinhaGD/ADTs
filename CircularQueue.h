#pragma once
#include <exception>

class EmptyQueueException : std::exception {
public:
	EmptyQueueException(){};
	const char* what() const noexcept override {
		return "Circular Queue is Empty";
	}
};

class FullQueueException : std::exception {
public:
	FullQueueException() {};
	const char* what() const noexcept override {
		return "Circular Queue is full";
	}
};

template<typename tData>
class CircularQueue
{
private:
	int front;
	int rear;
	int size;
	tData* queue;

public:
	CircularQueue(int _size) {
		queue = new tData[_size];
		this->size = _size;
		front = -1;
		rear = -1;
	}

	~CircularQueue() {
		if (queue != nullptr) {
			delete[] queue;
		}
	}

	void push(const tData& value) {

		if (isFull()) {
			throw FullQueueException{};
		}
		if (isEmpty()) {
			front++;
			rear++;
		}
		else {
			rear = (rear + 1) % size;
		}
		queue[rear] = value;

	}

	void pop() {

		if (isEmpty()) {
			throw EmptyQueueException{};
		}

		/*If only one element exists in the queue then we set front and rear pointers to -1 to make queue empty*/
		if (front == rear) {
			front = -1;
			rear = -1;
		}
		else {
			front = (front + 1) % size;
		}

	}

	tData peekFront() {

		if (isEmpty()) {
			throw EmptyQueueException{};
		}
		return queue[front];
	}

	tData peekRear() {
		if (isEmpty()) {
			throw EmptyQueueException{};
		}
		return queue[rear];
	}

	bool isEmpty() const {
		return (front == -1 && rear == -1);
	}

	bool isFull() const {
		return ((rear + 1) % size) == front;
	}

	int getSize() const {
		return this->size;
	}
};


