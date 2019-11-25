/*
소방서랑만 연결된 새로운 노드를 추가해서,
새로 추가한 노드랑 소방서 사이의 weight를 0으로 설정하고,
새로 추가한 노드에서 다익스트라 알고리즘을 돌리면 최단경로가 나온다.
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int C, V, E, n, m; // # of test case, vertex, edge, 화재장소, 소방서
int** weight;
int* shortPath;
vector<int> fire_place, fire_station;

void Dijkstra(int start);

int main(void)
{
	cin >> C;
	vector<int> answer(C);

	for (int tc = 0; tc < C; tc++)
	{
		cin >> V >> E >> n >> m;
		weight = new int* [V];
		for (int i = 0; i < V; i++)
			weight[i] = new int[V];
		shortPath = new int[V];

		//fill(&weight[0][0], &weight[V - 1][V], 101);
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
				weight[i][j] = 101;
			shortPath[i] = 101;
		}

		for (int i = 0; i < E; i++)
		{
			int first, second;
			cin >> first >> second;
			int num;
			cin >> num;
			weight[second - 1][first - 1] = weight[first - 1][second - 1] = num;
		}

		for (int i = 0; i < n; i++)
		{
			int temp;
			cin >> temp;
			fire_place.push_back(temp - 1);
		}

		for (int i = 0; i < m; i++)
		{
			int temp;
			cin >> temp;
			fire_station.push_back(temp - 1);
		}

		vector<int> temp(n, 999999);
		for (int i = 0; i < m; i++)
		{
			Dijkstra(fire_station[i]);
			for (int j = 0; j < n; j++)
			{
				if (temp[j] > shortPath[fire_place[j]])
					temp[j] = shortPath[fire_place[j]];
			}
		}
		
		for (int i = 0; i < temp.size(); i++)
			answer[tc] += temp[i];
	}

	for (int tc = 0; tc < C; tc++)
		cout << answer[tc] << endl;

	return 0;
}

void Dijkstra(int start)
{
	bool* visited = new bool[V];
	fill(&visited[0], &visited[V], false);
	visited[start] = true;

	for (int i = 0; i < V; i++)
	{
		if (i == start) continue;
		shortPath[i] = weight[start][i];
	}

	for (int i = 0; i < V - 1; i++)
	{
		int min = 101;
		int index = -1;
		for (int j = 0; j < V; j++)
		{
			if (j == start) continue;
			if ((min > shortPath[j]) && !visited[j])
			{
				min = shortPath[j];
				index = j;
			}
		}
		if (index != -1)
		{
			visited[index] = true;
			for (int j = 0; j < V; j++)
			{
				if (j == start) continue;
				if (!visited[j])
				{
					shortPath[j] = shortPath[j] > shortPath[index] + weight[index][j] ?
						shortPath[index] + weight[index][j] : shortPath[j];
				}
			}
		}
	}
}
