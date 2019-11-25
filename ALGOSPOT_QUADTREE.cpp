#include<iostream>
#include<string>
#include<vector>

using namespace std;

// CNode.h
class CNode
{
private:
	char key;

	CNode* left_top;
	CNode* right_top;
	CNode* left_bottom;
	CNode* right_bottom;
public:
	CNode();
	CNode(char key);
	~CNode();

	char getKey();
	void setKey(char key);

	CNode** getLT();
	CNode** getRT();
	CNode** getLB();
	CNode** getRB();

	void setLT(CNode* node);
	void setRT(CNode* node);
	void setLB(CNode* node);
	void setRB(CNode* node);
};




// CNode.cpp
CNode::CNode()
	: key('x'), left_top(nullptr), right_top(nullptr), left_bottom(nullptr), right_bottom(nullptr)
{
}

CNode::CNode(char key)
	: key(key), left_top(nullptr), right_top(nullptr), left_bottom(nullptr), right_bottom(nullptr)
{
}


CNode::~CNode()
{
}

char CNode::getKey()
{
	return key;
}

void CNode::setKey(char key)
{
	this->key = key;
}

CNode ** CNode::getLT()
{
	return &left_top;
}

CNode ** CNode::getRT()
{
	return &right_top;
}

CNode ** CNode::getLB()
{
	return &left_bottom;
}

CNode ** CNode::getRB()
{
	return &right_bottom;
}

void CNode::setLT(CNode* node)
{
	this->left_top = node;
}

void CNode::setRT(CNode* node)
{
	this->right_top = node;
}

void CNode::setLB(CNode* node)
{
	this->left_bottom = node;
}

void CNode::setRB(CNode* node)
{
	this->right_bottom = node;
}



// QuadTree.h
class QuadTree
{
private:
	CNode* root;
public:
	QuadTree();
	QuadTree(string input);
	~QuadTree();

	CNode* getRoot();

	void Insert(string input);
	string _Insert(CNode* node, string input);

	void Reverse();
	void _Reverse(CNode** up, CNode** down);

	void Show_dfs();
	void _Show_dfs(CNode* node);
};



// QuadTree.cpp
QuadTree::QuadTree()
	: root(nullptr)
{
}

QuadTree::QuadTree(string input)
{
	root = new CNode(input.at(0));
	Insert(input.substr(1));
}


QuadTree::~QuadTree()
{
}

CNode * QuadTree::getRoot()
{
	return root;
}

void QuadTree::Insert(string input)
{
	_Insert(this->root, input);
}

string QuadTree::_Insert(CNode * node, string input)
{
	if (!(input.size()))
		return "";

	int diff = 0;
	if (!(input.size() / 4))
	{
		for (int i = 0; i < input.size() % 4; i++)
		{
			CNode* insert = new CNode(input.at(i - diff));

			switch (i)
			{
			case 0:
				node->setLT(insert);
				break;
			case 1:
				node->setRT(insert);
				break;
			case 2:
				node->setLB(insert);
				break;
			case 3:
				node->setRB(insert);
				break;
			}

			if (insert->getKey() == 'x')
			{
				input = _Insert(insert, input.substr(i + 1 - diff));
				diff = i + 1;
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			CNode* insert = new CNode(input.at(i - diff));

			switch (i)
			{
			case 0:
				node->setLT(insert);
				break;
			case 1:
				node->setRT(insert);
				break;
			case 2:
				node->setLB(insert);
				break;
			case 3:
				node->setRB(insert);
				break;
			}

			if (insert->getKey() == 'x')
			{
				input = _Insert(insert, input.substr(i + 1 - diff));
				diff = i + 1;
			}
		}
	}
	
	if (input.size() > 4 - diff)
		return input.substr(4 - diff);
	
	return "";
}

void QuadTree::Reverse()
{
	/*if (this->root->getLT() != nullptr && this->root->getLB() != nullptr)*/
		_Reverse(this->root->getLT(), this->root->getLB());
	/*if (this->root->getRT() != nullptr && this->root->getRB() != nullptr)*/
		_Reverse(this->root->getRT(), this->root->getRB());
}

void QuadTree::_Reverse(CNode ** up, CNode ** down)
{
	if (*up == nullptr && *down == nullptr)
		return;

	if ((*up)->getKey() == 'x')
	{
		_Reverse((*up)->getLT(), (*up)->getLB());
		_Reverse((*up)->getRT(), (*up)->getRB());
	}
	if ((*down)->getKey() == 'x')
	{
		_Reverse((*down)->getLT(), (*down)->getLB());
		_Reverse((*down)->getRT(), (*down)->getRB());
	}

	CNode* temp = *up;
	*up = *down;
	*down = temp;
}

void QuadTree::Show_dfs()
{
	_Show_dfs(this->root);
}

void QuadTree::_Show_dfs(CNode * node)
{
	if (node == nullptr)
		return;

	cout << node->getKey();

	// first recursion
	_Show_dfs(*(node->getLT()));
	// second recursion
	_Show_dfs((*node->getRT()));
	// third recursion
	_Show_dfs(*(node->getLB()));
	// fourh recursion
	_Show_dfs(*(node->getRB()));
}



// main.cpp
int main(void)
{
	QuadTree** qt;
	int c;
	cin >> c;

	qt = new QuadTree*[c];

	for (int i = 0; i < c; i++)
	{
		string str;
		cin >> str;
		qt[i] = new QuadTree(str);
		qt[i]->Reverse();
	}

	for (int i = 0; i < c; i++)
	{
		qt[i]->Show_dfs();
		cout << endl;
	}

	return 0;
}
