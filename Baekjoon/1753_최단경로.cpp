/*
heap을 이용해서 weight 값을 저장하여 weight 값이 작은 것 부터 뽑아서 사용할 수 있다.
heap에 저장하는 형식은 (도착지, path weight합) 으로 하면 될 듯?
또한 heap에서 뽑아낸 값이 이미 갱신된 값이라면 무조건 버리면 된다.
-> 왜냐하면 heap에서 뽑아내는 순서가 크기 순서대로 뽑혀나오기 때문.
*/

// version 1 - unused queue
#include<iostream>

using namespace std;

int V, E;
char** weight;
char* shortPath;
bool* visited;
void Dijkstra(int start);

int main(void)
{
	cin >> V >> E;

	int start;
	cin >> start;
	start--;

	weight = new char* [V];
	for (int i = 0; i < V; i++)
		weight[i] = new char[V];

	shortPath = new char[V];
	
	visited = new bool[V];
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
			weight[i][j] = 11;
		shortPath[i] = 11;
		visited[i] = false;
	}
	shortPath[start] = 0;

	for (int i = 0; i < E; i++)
	{
		int row, col;
		cin >> row >> col;
		row--, col--;
		cin >> weight[row][col];
	}

	Dijkstra(start);

	for (int i = 0; i < V; i++)
	{
		if (shortPath[i] == 11)
			cout << "INF" << endl;
		else
			cout << shortPath[i] << endl;
	}

	return 0;
}

// 정점 start로 부터 시작되는 모든 정점으로의 최단 거리를 구하는 함수
void Dijkstra(int start)
{
	visited[start] = true;

	for (int i = 1; i < V; i++)
	{
		shortPath[i] = weight[start][i];
	}

	for (int i = 0; i < V - 1; i++)
	{
		int min = 11;
		int index = -1;
		for (int j = 1; j < V; j++)
		{
			if ((min > shortPath[j]) && !visited[j])
			{
				min = shortPath[j];
				index = j;
			}
		}
		if (index != -1)
		{
			visited[index] = true;
			for (int j = 1; j < V; j++)
			{
				if (!visited[j])
				{
					shortPath[j] = shortPath[j] > shortPath[index] + weight[index][j] ?
						shortPath[index] + weight[index][j] : shortPath[j];
				}
			}
		}
	}
}


// version 2 - used queue
#include<iostream>
#include<queue>
#include<vector>

#define MAX_V 11		// 가중치의 최대 값이 10 이기 때문.

using namespace std;

int** weight;
int V, E;
vector<int> shortPath;

void Dijkstra(int start);

int main(void)
{
	cin >> V >> E;
	int start;
	cin >> start;

	weight = new int* [V];
	for (int i = 0; i < V; i++)
	{
		weight = new int* [V];
		shortPath.push_back(MAX_V);
	}
	fill(weight, weight + V * V, MAX_V);


	for (int i = 0; i < E; i++)
	{
		int first, second;
		cin >> first >> second;
		cin >> weight[first][second];
	}

	Dijkstra(start);

	for (int i = 0; i < (int)shortPath.size(); i++)
	{
		if (shortPath[i] == MAX_V)
			cout << "INF" << endl;
		else
			cout << shortPath[i] << endl;
	}

	return 0;
}

void Dijkstra(int start)
{
	for (int i = 0; i < V; i++)
		shortPath[i] = weight[start][i];
	shortPath[start] = 0;

	priority_queue<pair<int, int>> q;
	q.push(pair<int, int>(-shortPath[start], 0));

	while (!q.empty())
	{
		int cur_weight = -q.top().first;		// 비용
		int cur_pos = q.top().second;		// 현재 위치

		if (shortPath[cur_pos] < cur_weight)
			continue;

		for (int i = 0; i < V; i++)
		{
			if (i == cur_pos) continue;

			int next_weight = weight[cur_pos][i];
			int next_pos = i;

			if (shortPath[next_pos] > shortPath[cur_pos] + next_weight)
			{
				shortPath[next_pos] = shortPath[cur_pos] + next_weight;
				q.push(pair<int, int>(-shortPath[next_weight], next_pos));
			}
		}
	}
}
