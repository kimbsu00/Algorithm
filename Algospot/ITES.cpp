/*
  url: https://algospot.com/judge/problem/read/ITES
  
  직접 Dequeue 자료구조를 구현해서 시도했던 문제.
  https://github.com/kimbsu00/Algorithm/blob/master/Algospot/ITES_STL.cpp 에 나와있는 알고리즘과 똑같은 알고리즘인데 시간초과가 발생함.
  cpp 에서 제공하는 Queue 와 내가 직접 구현한 Dequeue 의 데이터 추가 및 제거에서 속도 차이가 상당한 것 같다.
*/

#include<iostream>
#include<vector>
#include<climits>

#define X ((long long)UINT_MAX + 1)

using namespace std;

int ITES();

int K, N;

class Node
{
private:
	int value;

	Node* prev;
	Node* next;

public:
	Node();
	Node(int value);
	Node(int value, Node* next);
	~Node();

	void setValue(int value);
	void setPrev(Node* prev);
	void setNext(Node* next);

	int getValue();
	Node* getPrev();
	Node* getNext();
};

Node::Node()
	: value(-1), prev(nullptr), next(nullptr)
{
}

Node::Node(int value)
	: value(value), prev(nullptr), next(nullptr)
{
}

Node::Node(int value, Node* next)
	: value(value), prev(nullptr), next(next)
{
}

Node::~Node()
{
}

void Node::setValue(int value)
{
	this->value = value;
}

void Node::setPrev(Node* prev)
{
	this->prev = prev;
}

void Node::setNext(Node* next)
{
	this->next = next;
}

int Node::getValue()
{
	return this->value;
}

Node* Node::getPrev()
{
	return this->prev;
}

Node* Node::getNext()
{
	return this->next;
}

class Dequeue
{
private:
	int sum;

	Node* front;
	Node* back;

public:
	Dequeue();
	~Dequeue();

	void pushFront(int value);
	void pushBack(int value);

	void popFront();
	void popBack();

	int getFront();
	int getBack();
	int getSum();
};

Dequeue::Dequeue()
	: sum(0)
{
	this->back = new Node(-1, nullptr);
	this->front = new Node(-1, this->back);

	this->back->setPrev(front);
}

Dequeue::~Dequeue()
{
}

void Dequeue::pushFront(int value)
{
	Node* node = new Node(value, this->front->getNext());
	node->setPrev(this->front);
	
	this->front->setNext(node);
	node->getNext()->setPrev(node);

	sum += value;
}

void Dequeue::pushBack(int value)
{
	Node* node = new Node(value, this->back);
	node->setPrev(this->back->getPrev());

	this->back->setPrev(node);
	node->getPrev()->setNext(node);

	sum += value;
}

void Dequeue::popFront()
{
	if (this->front->getNext() == this->back)
		return;

	Node* node = this->front->getNext();
	sum -= node->getValue();
	
	this->front->setNext(node->getNext());
	node->getNext()->setPrev(this->front);

	node->setNext(nullptr);
	node->setPrev(nullptr);
	delete node;
}

void Dequeue::popBack()
{
	if (this->back->getPrev() == this->front)
		return;

	Node* node = this->back->getPrev();
	sum -= node->getValue();

	this->back->setPrev(node->getPrev());
	node->getPrev()->setNext(this->back);

	node->setNext(nullptr);
	node->setPrev(nullptr);
	delete node;
}

int Dequeue::getFront()
{
	if (this->front->getNext() == this->back)
		return -1;

	return this->front->getNext()->getValue();
}

int Dequeue::getBack()
{
	if (this->back->getPrev() == this->front)
		return -1;

	return this->back->getPrev()->getValue();
}

int Dequeue::getSum()
{
	return this->sum;
}

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C, 0);

	for (int i = 0; i < C; i++) {
		cin >> K >> N;

		answer[i] = ITES();
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

int ITES() {
	Dequeue dq;

	long long value = 1983;
	int ret = 0;
	for (int i = 0; i < N; i++) {
		dq.pushBack(value % 10000 + 1);
		value = (value * 214013 + 2531011) % X;

		while (dq.getSum() > K) {
			dq.popFront();
		}
		
		if (dq.getSum() == K) {
			dq.popFront();
			ret++;
		}
	}

	return ret;
}
