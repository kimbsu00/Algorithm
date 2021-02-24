/*
  url: https://www.acmicpc.net/problem/6416
*/

#include<iostream>
#include<vector>
#include<set>

using namespace std;

set<int> node;
vector<pair<int, int>> edge;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<bool> answer;
	int u, v;
	while (true) {
		cin >> u >> v;
		if (u == -1 && v == -1)			break;

		if (u == 0 && v == 0) {
			if ((edge.size() + 1 == node.size()) || node.empty()) {
				answer.push_back(true);
			}
			else {
				answer.push_back(false);
			}

			node.clear();
			edge.clear();
			continue;
		}

		node.insert(u);
		node.insert(v);
		edge.push_back(make_pair(u, v));
	}

	for (int i = 0; i < answer.size(); i++) {
		cout << "Case " << i + 1 << " is ";
		cout << (answer[i] ? "a tree." : "not a tree.") << "\n";
	}

	return 0;
}
