/*
  url: https://algospot.com/judge/problem/read/JOSEPHUS
  
  LinkedList 를 이용하여 순환 리스트를 구현해서 해결함.
*/
#include<iostream>

using namespace std;

class Node
{
private:
	int num;
	Node* next;

public:
	Node();
	Node(int num);
	~Node();

	void setNext(Node* next);
	Node* getNext();
	int getNum();
};

Node::Node()
	:num(-1), next(nullptr)
{
}

Node::Node(int num)
	: num(num), next(nullptr)
{
}

Node::~Node()
{
}

void Node::setNext(Node* next)
{
	this->next = next;
}

Node* Node::getNext()
{
	return this->next;
}

int Node::getNum()
{
	return this->num;
}

class LinkedList
{
private:
	Node* head;

public:
	LinkedList();
	~LinkedList();

	Node* getHead();

	void Insert(int num);
	void Joseputh(int K);
};

LinkedList::LinkedList()
	: head(new Node(-1))
{
	head->setNext(head);
}

LinkedList::~LinkedList()
{
}

Node* LinkedList::getHead()
{
	return this->head;
}

void LinkedList::Insert(int num)
{
	Node* temp = head;
	while (true) {
		if (temp->getNext() == head)		break;
		temp = temp->getNext();
	}

	Node* node = new Node(num);
	node->setNext(head);
	temp->setNext(node);
}

void LinkedList::Joseputh(int K)
{
	Node* prev = head;
	Node* temp = prev->getNext();

	prev->setNext(temp->getNext());
	delete temp;
	temp = prev->getNext();

	/*
		실제로 제거할 노드는 temp이다.
		temp는 prev의 다음 노드이기 때문에 K번 움직이지 않고 K-1번 움직여야 한다.
		그리고 temp가 head인 경우에는 temp를 head의 다음 노드로 바꿔주면 된다.
		여기서 prev는 왜 안바꿔주냐? -> temp만 바꿔주면 prev는 temp와 같이 이동하게 되기 때문에 따로 바꿔주지 않아도 됨.
	*/
	while (true) {
		// LinkedList 에 존재하는 노드가 두개인 경우
		if (head->getNext()->getNext()->getNext() == head)	break;

		if (prev->getNext() == head)
			temp = head->getNext();

		for (int i = 0; i < K - 1; i++) {
			prev = temp;
			temp = temp->getNext();
			if (temp == head)	i--;
		}

		prev->setNext(temp->getNext());

		delete temp;
		temp = prev->getNext();
	}

	std::cout << head->getNext()->getNum() << " " << head->getNext()->getNext()->getNum() << std::endl;
}

int main(void) {
	int C;
	cin >> C;

	for (int i = 0; i < C; i++) {
		int N, K;
		cin >> N >> K;

		LinkedList list = LinkedList();
		for (int i = 0; i < N; i++) {
			list.Insert(i + 1);
		}
		list.Joseputh(K);
	}

	return 0;
}	
