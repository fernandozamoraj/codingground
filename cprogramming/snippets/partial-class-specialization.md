### Partial Class Specialization
At some point in cpp you will need to create data structure classes. Those classes will use templates and work with any type.  Except they may have trouble working with pointers.  This will lead to compilation problems.  That is because pointers have different requirement than value types.  Therefore you will need to write another template for your pointers needs. 
Here is an example.

Here is an example of a stack that works with a specialized version of the template for Widget pointers
```c++
#include "Node.h"
#include "Widget.h"

#ifndef STACK
#define STACK

template <class T>
class Stack {
private:
	Node<T>* front;
	int _size;

	// 1 2 3
	// 3 2 1
	void copyOther(Node<T>* otherFront) {
		Node<T>* otherCurrent = otherFront;
		Node<T>* back = nullptr;
		_size = 0;
		while (otherCurrent != nullptr) {
			if (front == nullptr) {
				front = new Node<T>(otherCurrent->getData());
				back = front;
			}
			else {

				back->setNext( new Node<T>(otherCurrent->getData()));
				back = back->getNext();
			}

			_size++;
			otherCurrent = otherCurrent->getNext();
		}

	}

	void deleteList() {
		Node<T>* current = front;

		while (current != nullptr) {
			Node<T>* temporary = current;
			current = current->getNext();
			delete temporary;
		}
		front = nullptr;
		_size = 0;
	}

public:
	Stack() {
		front = nullptr;
		_size = 0;
	}

	Stack(const Stack<T> &other) {
		_size = 0;
		copyOther(other.front);
	}

	Stack operator=(const Stack<T>& other) {
		deleteList();
		copyOther(other.front);
	}

	~Stack() {
		deleteList();
	}

	int size() {
		return _size;
	}

	T peek() {

		return front->getData();
	}

	bool isEmpty() {
		return front == nullptr;
	}

	void push(T data) {
		//TODO add item
		if (front == nullptr) {
			front = new Node<T>(data);
		}
		else {
			Node<T> *newNode = new Node<T>(data);
			newNode->setNext(front);
			front = newNode;
		}
		_size++;
	}

	Node<T> *getFront() {

		return front;
	}

	T pop() {
		T data;
		if (!isEmpty()) {
			data = peek();
			front = front->getNext();
			_size--;
		}

		return data;
	}
};


template <>
class Stack<Widget *> {
private:
	Node<Widget*>* front;
	int _size;

	void copyOther(Node<Widget*>* otherFront) {
		Node<Widget*>* otherCurrent = otherFront;
		Node<Widget*>* back = nullptr;
		_size = 0;
		while (otherCurrent != nullptr) {
			if (front == nullptr) {
				front = new Node<Widget*>(otherCurrent->getData());
				back = front;
			}
			else {

				back->setNext(new Node<Widget*>(otherCurrent->getData()));
				back = back->getNext();
			}

			_size++;
			otherCurrent = otherCurrent->getNext();
		}

	}

	void deleteList() {
		Node<Widget*>* current = front;

		while (current != nullptr) {
			Node<Widget*>* temporary = current;
			current = current->getNext();
			delete temporary;
		}
		front = nullptr;
		_size = 0;
	}

public:
	Stack() {
		front = nullptr;
		_size = 0;
	}

	Stack(const Stack<Widget*>& other) {
		_size = 0;
		copyOther(other.front);
	}

	Stack operator=(const Stack<Widget*>& other) {
		deleteList();
		copyOther(other.front);
	}

	~Stack() {
		deleteList();
	}

	int size() {
		return _size;
	}

	Widget* peek() {

		return front->getData();
	}

	bool isEmpty() {
		return front == nullptr;
	}

	void push(Widget* data) {
		if (front == nullptr) {
			front = new Node<Widget *>(data);
		}
		else {
			Node<Widget*>* newNode = new Node<Widget*>(data);
			newNode->setNext(front);
			front = newNode;
		}
		_size++;
	}

	Node<Widget*>* getFront() {

		return front;
	}

	Widget* pop() {
		Widget* data = nullptr;
		if (!isEmpty()) {
			data = peek();
			front = front->getNext();
			_size--;
		}

		return data;
	}
};

#endif 



```