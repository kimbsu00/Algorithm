#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<algorithm>

using namespace std;
int longest = 0;

class Node
{
private:
	// coordination of x and y
	int x, y;
	// radius
	int r;
	// node level
	int level;

	// parent node address
	Node* parent;
	// child nodes
	std::vector<Node*> childs;

public:
	Node();
	Node(int x, int y, int r);
	Node(int x, int y, int r, int level);
	Node(int x, int y, int r, int level, Node* parent);
	~Node();

	void setLevel(int level);
	void addChild(int x, int y, int r, int level);

	int getX();
	int getY();
	int getLevel();
	int getRadius();
	std::vector<Node*> getChilds();
};

Node::Node()
	: x(-1), y(-1), r(-1), level(-1), parent(nullptr)
{
}

Node::Node(int x, int y, int r)
	: x(x), y(y), r(r), level(-1), parent(nullptr)
{
}

Node::Node(int x, int y, int r, int level)
	: x(x), y(y), r(r), level(level), parent(nullptr)
{
}

Node::Node(int x, int y, int r, int level, Node* parent)
	: x(x), y(y), r(r), level(level), parent(parent)
{
}

Node::~Node()
{
}

void Node::setLevel(int level)
{
	this->level = level;
}

void Node::addChild(int x, int y, int r, int level)
{
	this->childs.push_back(new Node(x, y, r, level, this));
}

int Node::getX()
{
	return this->x;
}

int Node::getY()
{
	return this->y;
}

int Node::getLevel()
{
	return this->level;
}

int Node::getRadius()
{
	return this->r;
}

std::vector<Node*> Node::getChilds()
{
	return this->childs;
}

class Tree
{
private:
	Node* root;

public:
	Tree();
	Tree(int x, int y, int r);
	~Tree();

	void Insert(int x, int y, int r);

	int getMaxDistance();
};

Tree::Tree()
	: root(nullptr)
{
}

Tree::Tree(int x, int y, int r)
{
	this->root = new Node(x, y, r, 1);
}

Tree::~Tree()
{
}

/* 
	중심이 (x1, y1) 이고 반지름이 r1 인 원을 A, 중심이 (x2, y2) 이고 반지름이 r2 인 원을 B 라고 할 때,
	B가 A의 내부에 위치해 있는 경우 -> return true
	B가 A의 외부에 위치해 있는 경우 -> return false
*/
bool isInnerCircle(int x1, int y1, int r1, int x2, int y2, int r2) {
	double distance = sqrt((x1-x2)* (x1 - x2) +(y1-y2)* (y1 - y2));
	if (abs(r1 - r2) >= distance) {
		return true;
	}
	else {
		return false;
	}
}

void _Insert(Node* node, int x, int y, int r) {
	if (node->getChilds().empty()) {
		node->addChild(x, y, r, node->getLevel() + 1);
		return;
	}

	bool isExit = false;
	std::vector<Node*> vector = node->getChilds();
	for (int i = 0; i < vector.size(); i++) {
		if (isInnerCircle(vector[i]->getX(), vector[i]->getY(), vector[i]->getRadius(), x, y, r)) {
			_Insert(vector[i], x, y, r);
			isExit = true;
			break;
		}
	}

	if (!isExit) {
		node->addChild(x, y, r, node->getLevel() + 1);
	}

	return;
}

void Tree::Insert(int x, int y, int r)
{
	if (root == nullptr)
		return;

	_Insert(root, x, y, r);
}

int getMaxLevel(Node* node) {
	if (node->getChilds().empty())
		return node->getLevel();

	std::vector<int> maxLevel;
	for (int i = 0; i < node->getChilds().size(); i++) {
		maxLevel.push_back(getMaxLevel(node->getChilds()[i]));
	}
	sort(maxLevel.begin(), maxLevel.end());

	// 자식 노드를 루트로 하는 서브트리의 리프-리프 간 거리가 최장거리인 경우도 생각해야 함.
	if (maxLevel.size() > 1) {
		longest = std::max(longest, maxLevel[maxLevel.size() - 1] + maxLevel[maxLevel.size() - 2] - node->getLevel() * 2);
	}

	return maxLevel[maxLevel.size() - 1];
}

int Tree::getMaxDistance()
{
	if (root->getChilds().empty())	return 0;
	
	int ret = -1;
	if (root->getChilds().size() == 1) {
		ret = getMaxLevel(root) - 1;
	}
	else {
		std::vector<int> maxLevel;
		for (int i = 0; i < root->getChilds().size(); i++) {
			maxLevel.push_back(getMaxLevel(root->getChilds()[i]));
		}
		sort(maxLevel.begin(), maxLevel.end());
		ret = maxLevel[maxLevel.size() - 1] + maxLevel[maxLevel.size() - 2] - 2;
	}

	return std::max(longest, ret);
}

int main() {
	int C;
	cin >> C;

	vector<int> answer;
	for (int i = 0; i < C; i++) {
		longest = 0;
		int N;
		cin >> N;
		
		int x, y, r;
		cin >> x >> y >> r;
		Tree tree(x, y, r);
		for (int j = 1; j < N; j++) {
			cin >> x >> y >> r;
			tree.Insert(x, y, r);
		}
		answer.push_back(tree.getMaxDistance());
	}

	for (int i = 0; i < C; i++) {
		cout << answer[i] << endl;
	}

	return 0;
}
