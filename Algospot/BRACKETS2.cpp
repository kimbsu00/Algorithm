/*
This problem is BRACKETS2 in Algospot.
URL : https://algospot.com/judge/problem/read/BRACKETS2

I solved this problem using Dequeue like stack.
*/

#include<iostream>

class Node
{
private:
	Node* prev;
	Node* next;
	char data;

public:
	Node();
	Node(Node* prev ,Node* next, char data);
	~Node();

	Node* getPrev();
	void setPrev(Node* prev);
	Node* getNext();
	void setNext(Node* next);
	char getData();
	void setData(char& data);
};

Node::Node()
	: prev(nullptr), next(nullptr), data(' ')
{
}

Node::Node(Node* prev, Node* next, char data)
	: prev(prev), next(next), data(data)
{
}

Node::~Node()
{
	/*if (prev != nullptr)
		delete prev;
	if (next != nullptr)
		delete next;*/
}

Node* Node::getPrev()
{
	return prev;
}

void Node::setPrev(Node* prev)
{
	this->prev = prev;
}

Node* Node::getNext()
{
	return next;
}

void Node::setNext(Node* next)
{
	this->next = next;
}

char Node::getData()
{
	return data;
}

void Node::setData(char& data)
{
	this->data = data;
}

// double-ended queue 의 준말
class Dequeue
{
private:
	Node* head;
	Node* tail;

public:
	Dequeue();
	Dequeue(char data);
	~Dequeue();

	bool pushFront(char data);
	bool pushBack(char data);

	char popFront();
	char popBack();

	char getFront();
	char getBack();
};

Dequeue::Dequeue()
	: head(nullptr), tail(nullptr)
{
}

Dequeue::Dequeue(char data)
{
	Node* node = new Node(nullptr, tail, data);

	head = node;
	tail = nullptr;
}

Dequeue::~Dequeue()
{
}

bool Dequeue::pushFront(char data)
{
	// when Dequeue doesn't have node
	if (head == nullptr) {
		head = new Node(nullptr, tail, data);
	}
	// when Dequeue has a node
	else if (tail == nullptr) {
		Node* node = new Node(nullptr, tail, data);
		
		tail = head;
		tail->setNext(nullptr);
		
		head = node;
		tail->setPrev(head);
		
		return true;
	}
	// when Dequeue has nodes more than one
	else {
		Node* node = new Node(nullptr, head, data);

		head->setPrev(node);
		head = node;

		return true;
	}
}

bool Dequeue::pushBack(char data)
{
	// when Dequeue doesn't have node
	if (head == nullptr) {
		head = new Node(nullptr, tail, data);
	}
	// when Dequeue has a node
	else if (tail == nullptr) {
		Node* node = new Node(tail, nullptr, data);

		tail = node;

		return true;
	}
	// when Dequeue has nodes more than one
	else {
		Node* node = new Node(tail, nullptr, data);

		tail->setNext(node);
		tail = node;

		return true;
	}
}

char Dequeue::popFront()
{
	// when Dequeue doesn't have node
	if (head == nullptr) {
		return ' ';
	}
	// when Dequeue has a node
	else if (tail == nullptr) {
		char ret = head->getData();
		head = nullptr;
		return ret;
	}
	// when Dequeue has nodes more than one
	else {
		char ret = head->getData();
		head = head->getNext();
		return ret;
	}
}

char Dequeue::popBack()
{
	// when Dequeue doesn't have node
	if (head == nullptr) {
		return ' ';
	}
	// when Dequeue has a node
	else if (tail == nullptr) {
		char ret = head->getData();
		head = nullptr;
		return ret;
	}
	// when Dequeue has nodes more than one
	else {
		char ret = tail->getData();
		tail = tail->getPrev();
		return ret;
	}
}

char Dequeue::getFront()
{
	// when Dequeue doesn't have node
	if (head == nullptr) {
		return ' ';
	}
	// when Dequeue has a node
	else if (tail == nullptr) {
		return head->getData();
	}
	// when Dequeue has nodes more than one
	else {
		return head->getData();
	}
}

char Dequeue::getBack()
{
	// when Dequeue doesn't have node
	if (head == nullptr) {
		return ' ';
	}
	// when Dequeue has a node
	else if (tail == nullptr) {
		return head->getData();
	}
	// when Dequeue has nodes more than one
	else {
		return tail->getData();
	}
}

int main() {
	int c;

	std::cin >> c;
	Dequeue* stack = new Dequeue[c];
	bool* answer = new bool[c];

	for (int i = 0; i < c; i++) {
		std::string str;
		std::cin >> str;
		
		for (int j = 0; j < str.length(); j++) {
			if (str[j] == '[' || str[j] == '{' || str[j] == '(') {
				stack[i].pushBack(str[j]);
			}
			else {
				bool check = false;
				switch (str[j]) {
				case ']':
					if (stack[i].getBack() == '[')
						check = true;
					break;
				case '}':
					if (stack[i].getBack() == '{')
						check = true;
					break;
				case ')':
					if (stack[i].getBack() == '(')
						check = true;
					break;
				}

				if (check) {
					stack[i].popBack();
				} 
				else {
					answer[i] = false;
					break;
				}
			}
			if (j == str.length() - 1 && stack[i].getBack() == ' ')
				answer[i] = true;
		}
	}

	for (int i = 0; i < c; i++) {
		if (answer[i])
			std::cout << "YES" << std::endl;
		else
			std::cout << "NO" << std::endl;
	}

	return 0;
}
