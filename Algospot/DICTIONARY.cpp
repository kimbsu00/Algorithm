/*
  url: https://algospot.com/judge/problem/read/DICTIONARY
  
  Topological Sort 를 이용함.
*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

void dfs(int node, vector<int>& ret);
vector<int> topologicalSort();
void makeGraph(string prev, string next);
int CharToInt(char ch);

vector<string> words;
// 그래프를 인접리스트 형태로 표현함
vector<vector<int>> adj;
vector<bool> visited;

int main(void) {
	int C;
	cin >> C;
	vector<string> answer(C, "");

	for (int i = 0; i < C; i++) {
		int N;
		cin >> N;
		words = vector<string>(N);
		adj = vector <vector<int>>(26, vector<int>());
		visited = vector<bool>(26, false);

		for (int j = 0; j < N; j++) {
			cin >> words[j];
		}

		for (int j = 0; j < words.size() - 1; j++) {
			makeGraph(words[j], words[j + 1]);
		}

		vector<int> ret = topologicalSort();
		if (ret.empty()) {
			answer[i] = "INVALID HYPOTHESIS";
		}
		else {
			vector<bool> alphabet(26, false);
			for (int j = 0; j < ret.size(); j++) {
				answer[i].insert(answer[i].end(), (char)ret[j] + 'a');
				alphabet[ret[j]] = true;
			}
			for (int j = 0; j < alphabet.size(); j++) {
				if(!alphabet[j])
					answer[i].insert(answer[i].end(), (char)j + 'a');
			}
		}
	}

	for (string output : answer)
		cout << output << endl;

	return 0;
}

void dfs(int node, vector<int>& ret) {
	visited[node] = true;

	for (int i = 0; i < adj[node].size(); i++) {
		int there = adj[node][i];
		if (!visited[there]) {
			dfs(there, ret);
		}
	}
	ret.push_back(node);
}

vector<int> topologicalSort() {
	vector<int> ret;

	for (int i = 0; i < visited.size(); i++) {
		if (!adj[i].empty() && !visited[i]) {
			dfs(i, ret);
		}
	}
	reverse(ret.begin(), ret.end());
	for (int i = ret.size() - 1; i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			for (int k = 0; k < adj[ret[i]].size(); k++) {
				if (adj[ret[i]][k] == ret[j])
					return vector<int>();
			}
		}
	}
	return ret;
}

void makeGraph(string prev, string next) {
	if (prev.size() == 0 || next.size() == 0)		return;

	if (prev[0] == next[0]) {
		makeGraph(prev.substr(1), next.substr(1));
	}
	else {
		adj[CharToInt(prev[0])].push_back(CharToInt(next[0]));
	}
	return;
}

int CharToInt(char ch) {
	return ch - 'a';
}
