/*
  url: https://www.acmicpc.net/problem/2213
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void makeGraph(int node);
vector<int> solve(int node, bool isSubset);
int getSum(vector<int> vec);

vector<int> weight;
vector<vector<int>> tree;
vector<bool> visited;
vector<vector<int>> directedGraph;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	weight = vector<int>(N);
	tree = vector<vector<int>>(N, vector<int>());
	visited = vector<bool>(N, false);
	directedGraph = vector<vector<int>>(N, vector<int>());

	for (int i = 0; i < N; i++) {
		cin >> weight[i];
	}

	for (int i = 1; i < N; i++) {
		int a, b;
		cin >> a >> b;
		tree[a - 1].push_back(b - 1);
		tree[b - 1].push_back(a - 1);
	}

	makeGraph(0);

	vector<int> output1 = solve(0, true);
	sort(output1.begin(), output1.end(), less<int>());
	int sum1 = getSum(output1);

	vector<int> output2 = solve(0, false);
	sort(output2.begin(), output2.end(), less<int>());
	int sum2 = getSum(output2);

	if (sum1 < sum2) {
		cout << sum2 << "\n";
		for (int node : output2)
			cout << node + 1 << " ";
	}
	else {
		cout << sum1 << "\n";
		for (int node : output1)
			cout << node + 1 << " ";
	}

	return 0;
}

// 트리를 방향그래프 형태로 바꿔줌.
void makeGraph(int node) {
	visited[node] = true;

	for (int next : tree[node]) {
		if (!visited[next]) {
			directedGraph[node].push_back(next);
			makeGraph(next);
		}
	}
}

/*
node 가 부분집합에 포함된다면, node 의 자식 노드들은 모두 부분집합에 포함될 수 없다.
node 가 부분집합에 포함되지 않는다면, node 의 자식 노드들은 부분집합에 포함될 수도 있고, 포함되지 않을 수도 있다.
*/
vector<int> solve(int node, bool isSubset) {
	vector<int> ret;

	if (isSubset) {
		ret.push_back(node);
		for (int next : directedGraph[node]) {
			vector<int> temp = solve(next, false);
			ret.insert(ret.end(), temp.begin(), temp.end());
		}
	}
	else {
		for (int next : directedGraph[node]) {
			vector<int> temp1 = solve(next, true);
			vector<int> temp2 = solve(next, false);
			if (getSum(temp1) < getSum(temp2)) {
				ret.insert(ret.end(), temp2.begin(), temp2.end());
			}
			else {
				ret.insert(ret.end(), temp1.begin(), temp1.end());
			}
		}
	}

	return ret;
}

int getSum(vector<int> vec) {
	int ret = 0;
	for (int num : vec)
		ret += weight[num];
	return ret;
}
