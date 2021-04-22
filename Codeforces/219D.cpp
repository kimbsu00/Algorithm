/*
  url: https://codeforces.com/problemset/problem/219/D
  
  임의의 노드 x 에 대하여,
  루트를 x 로 하는 트리를 만들 때 뒤집게 되는 엣지의 개수(k)를 계산한다. (solve 함수)
  그리고 x 에서부터 x 의 자식 노드 c 로 이동하면서 다음의 연산을 수행한다.
    1. 엣지가 x -> c 의 방향인 경우 : c 를 루트로 하는 트리를 만들기 위해서는 k + 1 개의 엣지를 뒤집어야 한다.
    2. 엣지가 x <- c 의 방향인 경우 : c 를 루트로 하는 트리를 만들기 위해서는 k - 1 개의 엣지를 뒤집어야 한다.
  연산을 끝낸 후에는 정렬해서 정답 출력하면 끝!
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int solve(int node);
void calculate(int node, int sum);
bool compare(const pair<int, int>& a, const pair<int, int>& b);

int N;
vector<vector<pair<int, bool>>> tree;
vector<bool> visited;
vector<pair<int, int>> output;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	tree = vector<vector<pair<int, bool>>>(N, vector<pair<int, bool>>());
	visited = vector<bool>(N, false);

	for (int i = 1; i < N; i++) {
		int S, T;
		cin >> S >> T;
		tree[S - 1].push_back({ T - 1, true });
		tree[T - 1].push_back({ S - 1, false });
	}

	output.push_back(make_pair(solve(0), 0));
	
	visited = vector<bool>(N, false);	
	calculate(0, output[0].first);
	sort(output.begin(), output.end(), compare);

	int minValue = output[0].first;
	int index = -1;
	for (int i = 1; i < output.size(); i++) {
		if (minValue != output[i].first) {
			index = i;
			break;
		}
	}
	cout << minValue << "\n";
	for (int i = 0; i < index; i++) {
		cout << output[i].second + 1 << " ";
	}

	return 0;
}

int solve(int node) {
	visited[node] = true;

	int ret = 0;
	for (pair<int, int> next: tree[node]) {
		if (!visited[next.first]) {
			if (next.second) 
				ret += solve(next.first);
			else 
				ret += 1 + solve(next.first);
		}
	}

	return ret;
}

void calculate(int node, int sum) {
	visited[node] = true;

	for (pair<int, int> next : tree[node]) {
		if (!visited[next.first]) {
			if (next.second) {
				output.push_back(make_pair(sum + 1, next.first));
				calculate(next.first, sum + 1);
			}
			else {
				output.push_back(make_pair(sum - 1, next.first));
				calculate(next.first, sum - 1);
			} 
		}
	}
}

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
	if (a.first < b.first) {
		return true;
	}
	else if (a.first == b.first) {
		return a.second < b.second;
	}
	return false;
}
