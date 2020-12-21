/*
  url: https://algospot.com/judge/problem/read/NERD2
  
  알고스팟 채점 시스템에서 시간초과로 처리되는 코드임
  but 문제에서 제시한 예제를 돌리면 정답이 나오는 코드이며, 제시된 예제 외의 다른 경우에 대해서는 옳바르게 작동하는지 확인되지 않음
  
  https://algospot.com/forum/read/2496/ 을 참고해서 
  input method 를 cin 에서 printf 로 변경해봤지만 그래도 시간초과
  getchar 로 정수값만을 파싱해서 입력받아도 시간초과
  -> 알고리즘이 느린것이다 
*/

#include<iostream>
#include<vector>

using namespace std;

class Node
{
private:
	int p, q;

	Node* parent;
	Node* leftChild;
	Node* rightChild;

public:
	Node();
	Node(int p, int q, Node* parent);
	~Node();

	int getP();
	int getQ();
	Node* getParent();
	Node* getLeftChild();
	Node* getRightChild();

	void setP(int p);
	void setQ(int q);
	void setParent(Node* parent);
	void setLeftChild(Node* leftChild);
	void setRightChild(Node* rightChild);
};

Node::Node()
	: p(-1), q(-1), parent(nullptr), leftChild(nullptr), rightChild(nullptr)
{
}

Node::Node(int p, int q, Node* parent)
	: p(p), q(q), parent(parent), leftChild(nullptr), rightChild(nullptr)
{
}

Node::~Node()
{
	if (parent != nullptr)		delete parent;
	if (leftChild != nullptr)		delete leftChild;
	if (rightChild != nullptr)		delete rightChild;
}

int Node::getP()
{
	return this->p;
}

int Node::getQ()
{
	return this->q;
}

Node* Node::getParent()
{
	return this->parent;
}

Node* Node::getLeftChild()
{
	return this->leftChild;
}

Node* Node::getRightChild()
{
	return this->rightChild;
}

void Node::setP(int p)
{
	this->p = p;
}

void Node::setQ(int q)
{
	this->q = q;
}

void Node::setParent(Node* parent)
{
	this->parent = parent;
}

void Node::setLeftChild(Node* leftChild)
{
	this->leftChild = leftChild;
}

void Node::setRightChild(Node* rightChild)
{
	this->rightChild = rightChild;
}

void _Insert(int p, int q, Node* node);
void Delete(Node* node, Node** root);
bool CheckNerd(int p, int q, Node* node);
std::vector<Node*>  notNerd;

class BST
{
private:
	Node* root;
	int nodeNum;

public:
	BST();
	BST(int p, int q);
	~BST();

	int getNodeNum();

	void ChangeNodeNum(bool check);

	bool Insert(int p, int q);
};

BST::BST()
	: root(nullptr), nodeNum(0)
{
}

BST::BST(int p, int q)
	: nodeNum(1)
{
	this->root = new Node(p, q, nullptr);
}

BST::~BST()
{
}

int BST::getNodeNum()
{
	return this->nodeNum;
}

void BST::ChangeNodeNum(bool check)
{
	if (check) {
		this->nodeNum++;
	}
	else {
		this->nodeNum--;
	}
}

bool BST::Insert(int p, int q)
{
	if (root == nullptr) {
		root = new Node(p, q, nullptr);
	}

	notNerd.clear();
	bool ret = CheckNerd(p, q, root);

	if (ret) {
		for (int i = 0; i < notNerd.size(); i++) {
			Delete(notNerd[i], &root);
			this->ChangeNodeNum(false);
		}

		_Insert(p, q, root);
		this->ChangeNodeNum(true);
	}

	return ret;
}

void _Insert(int p, int q, Node* node) {
	if (node == nullptr) {
		node = new Node(p,q,nullptr);
	}

	if (node->getP() > p) {
		if (node->getLeftChild() != nullptr)
			_Insert(p, q, node->getLeftChild());
		else
			node->setLeftChild(new Node(p, q, node));
	}
	else if (node->getP() < p) {
		if (node->getRightChild() != nullptr)
			_Insert(p, q, node->getRightChild());
		else
			node->setRightChild(new Node(p, q, node));
	}
}

void Delete(Node* node, Node** root)
{
	Node* parent = node->getParent();
	/*
	자식노드가 존재하지 않는 경우
	현재 노드를 삭제하면 됨.
	*/
	if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr) {
		if (parent != nullptr) {
			if (node == parent->getLeftChild())
				parent->setLeftChild(nullptr);
			else
				parent->setRightChild(nullptr);

			node->setParent(nullptr);
			delete node;
		}
		else {
			*root = nullptr;

			node->setParent(nullptr);
			delete node;
		}
	}
	/* 
	왼쪽 자식 노드만 존재하는 경우
	현재 노드를 제거하고 그 자리에 왼쪽 자식노드를 가져다 놓는다.
	*/
	else if (node->getLeftChild() != nullptr && node->getRightChild() == nullptr) {
		if (parent != nullptr) {
			if (node == parent->getLeftChild())
				parent->setLeftChild(node->getLeftChild());
			else
				parent->setRightChild(node->getLeftChild());

			node->getLeftChild()->setParent(parent);

			node->setParent(nullptr);
			node->setLeftChild(nullptr);
			delete node;
		}
		else {
			*root = node->getLeftChild();

			node->getLeftChild()->setParent(parent);

			node->setParent(nullptr);
			node->setLeftChild(nullptr);
			delete node;
		}
	}
	/*
	오른쪽 자식 노드만 존재하는 경우
	현재 노드를 제거하고 그 자리에 오른쪽 자식노드를 가져다 놓는다.
	*/
	else if(node->getLeftChild() == nullptr && node->getRightChild() != nullptr) {
		if (parent != nullptr) {
			if (node == parent->getLeftChild())
				parent->setLeftChild(node->getRightChild());
			else
				parent->setRightChild(node->getRightChild());
			node->getRightChild()->setParent(parent);

			node->setParent(nullptr);
			node->setRightChild(nullptr);
			delete node;
		}
		else {
			*root = node->getRightChild();

			node->getRightChild()->setParent(parent);

			node->setParent(nullptr);
			node->setRightChild(nullptr);
			delete node;
		}
	}
	/*
	왼쪽 자식 노드와 오른쪽 자식 노드 모두 존재하는 경우
	왼쪽 서브트리를 오른쪽 서브트리의 맨 왼쪽 아래에 가져다 붙이면 됨.
	*/
	else {
		Node* leftChild = node->getLeftChild();
		Node* rightChild = node->getRightChild();
		Node* temp = node->getRightChild();

		while (true) {
			if (temp->getLeftChild() != nullptr)
				temp = temp->getLeftChild();
			else
				break;
		}

		if (parent != nullptr) {
			if (node == parent->getLeftChild())
				parent->setLeftChild(rightChild);
			else
				parent->setRightChild(rightChild);

			rightChild->setParent(parent);

			temp->setLeftChild(leftChild);
			leftChild->setParent(temp);

			node->setParent(nullptr);
			node->setLeftChild(nullptr);
			node->setRightChild(nullptr);
			delete node;
		}
		else {
			*root = rightChild;

			rightChild->setParent(parent);

			temp->setLeftChild(leftChild);
			leftChild->setParent(temp);

			node->setParent(nullptr);
			node->setLeftChild(nullptr);
			node->setRightChild(nullptr);
			delete node;
		}
	}
}

bool CheckNerd(int p, int q, Node* node)
{
	if (node == nullptr) return true;

	if (node->getP() > p && node->getQ() > q)		return false;

	if (node->getP() < p && node->getQ() < q)		notNerd.push_back(node);

	bool ret = true;
	if (node->getLeftChild() != nullptr)
		ret = CheckNerd(p, q, node->getLeftChild());

	if (ret) {
		if (node->getRightChild() != nullptr)
			ret = ret && CheckNerd(p, q, node->getRightChild());
	}

	return ret;
}

int main() {
	int C;
	cin >> C;
	vector<int> answer(C, 0);

	for (int i = 0; i < C; i++) {
		int N;
		cin >> N;
		
		int p, q;
		scanf("%d %d", &p, &q);
		BST bst(p, q);
		answer[i] += bst.getNodeNum();
		for (int j = 1; j < N; j++) {
			scanf("%d %d", &p, &q);
			bst.Insert(p, q);
			answer[i] += bst.getNodeNum();
		}
	}

	for (int i = 0; i < C; i++)
		printf("%d\n", answer[i]);

	return 0;
}
