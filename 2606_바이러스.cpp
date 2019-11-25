#include<iostream>
#define MAX_V 100

using namespace std;

int root[MAX_V];
int _rank[MAX_V];

int Find(int index);
void Union(int index1, int index2);

int main(void)
{
	int computer;			// # of computer
	int count;				// 조합의 개수
	cin >> computer >> count;
	
	for (int i = 0; i < MAX_V; i++)
	{
		root[i] = i;
		_rank[i] = 0;
	}

	for (int i = 0; i < count; i++)
	{
		int num1, num2;
		cin >> num1 >> num2;
		Union(num1 - 1, num2 - 1);
	}

	int answer = -1;
	for (int i = 0; i < computer; i++)
	{
		if (root[i] == root[0])
			answer++;
	}
	cout << answer << endl;
	
	return 0;
}

int Find(int index)
{
	if (root[index] == index)
		return index;

	return root[index] = Find(root[index]);
}

void Union(int index1, int index2)
{
	int first = Find(index1);
	int second = Find(index2);

	if (first == second)
		return;

	if (_rank[first] < _rank[second])
	{
		root[first] = second;
	}
	else
	{
		root[second] = first;
		if (_rank[first] == _rank[second])
		{
			_rank[first]++;
		}
	}
}
