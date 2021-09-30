/*
  url: https://www.acmicpc.net/problem/6416
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<vector<int>> directedGraph;
vector<int> indegree;
vector<bool> visited;

bool check_connected() {
	for (int i = 0; i < visited.size(); i++) {
		if (!visited[i] && indegree[i] != -1)			return false;
	}

	return true;
}

bool solve(int node) {
	if (visited[node])			return false;

	visited[node] = true;
	bool ret = true;
	for (int next : directedGraph[node]) {
		ret = ret && solve(next);
		if (!ret)			break;
	}

	return ret;
}

int check_indegree() {
	int root_num = 0;
	int root = -1;

	for (int i = 0; i < indegree.size(); i++) {
		if (indegree[i] == 0) {
			root_num += 1;
			root = i;
		}
		if (root_num > 1)			return -1;
	}

	for (int i = 0; i < indegree.size(); i++) {
		if (i == root)						continue;
		if (indegree[i] == -1)			continue;
		if (indegree[i] > 1)				return -1;
	}

	return root;
}

bool make_graph(vector<pair<int, int>>& input, int& size) {
	if (size == 0)			return false;

	directedGraph = vector<vector<int>>(size, vector<int>());
	indegree = vector<int>(size, -1);

	for (pair<int, int> pq : input) {
		directedGraph[pq.first].push_back(pq.second);
		if (indegree[pq.second] == -1) {
			indegree[pq.second] = 1;
		}
		else {
			indegree[pq.second] += 1;
		}
		if (indegree[pq.first] == -1) {
			indegree[pq.first] = 0;
		}
	}

	return true;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<string> answer;
	vector<pair<int, int>> input;
	int size = 0;
	for (int i = 1;;) {
		int p, q;
		cin >> p >> q;

		if (p == 0 && q == 0) {
			string tmp = "Case ";
			// graph에 node가 1개라도 있는 경우
			if (make_graph(input, size)) {
				int root = -1;
				// indegree가 0인 node가 1개가 아닌 경우 & indegree가 2이상인 node가 존재하는 경우
				if ((root = check_indegree()) >= 0) {
					visited = vector<bool>(directedGraph.size(), false);
					// root node부터 탐색했을 때, 2번 이상 방문한 노드가 없는 경우
					if (solve(root)) {
						// connected graph인 경우
						if (check_connected()) {
							tmp.append(to_string(i));
							tmp.append(" is a tree.");
						}
						// connected graph가 아닌 경우
						else {
							tmp.append(to_string(i));
							tmp.append(" is not a tree.");
						}
					}
					// root node부터 탐색했을 때, 2번 이상 방문한 노드가 있는 경우
					else {
						tmp.append(to_string(i));
						tmp.append(" is not a tree.");
					}
				}
				else {
					tmp.append(to_string(i));
					tmp.append(" is not a tree.");
				}
			}
			// graph에 node가 0개인 경우
			else {
				tmp.append(to_string(i));
				tmp.append(" is a tree.");
			}
			answer.push_back(tmp);

			input.clear();
			indegree.clear();
			visited.clear();
			size = 0;
			i++;
		}
		else if (p == -1 && q == -1) {
			break;
		}
		else {
			input.push_back({ p - 1,q - 1 });
			size = max(size, max(p, q));
		}
	}

	for (string ans : answer) {
		cout << ans << "\n";
	}

	return 0;
}
