/*
  url: https://algospot.com/judge/problem/read/WORDCHAIN
  
  EulerCircuit 과 EulerTrail 에 대하여 공부할 수 있었던 문제.
  아직 그래프를 이용하는 알고리즘에 익숙하지 않아서 다소 어려웠음.
  각각의 알고리즘마다 그래프를 인접 배열로 저장할지, 인접 리스트로 저장할지 확실한 판단이 들지 않는다.
  그래서 이번 문제에서도 처음에는 인접 리스트로 그래프를 저장했다가 EulerCircuit 을 구하는 알고리즘 구현에 있어서 인접 배열이 더 편리함을 깨닫고,
  인접리스트를 인접 배열로 변경해서 다시 풀었다.
*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

string WORDCHAIN();
void getEulerCircuit(int node, vector<int>& circuit);
vector<int> getEulerTrailOrCircuit();
bool checkEuler();
void makeGraph();
int CharToInt(char ch);

vector<string> words;
vector<vector<int>> adj;
vector<string> graph[26][26];
vector<int> indegree, outdegree;

int main(void) {
	int C;
	cin >> C;
	vector<string> answer(C);

	for (int i = 0; i < C; i++) {
		int N;
		cin >> N;
		words = vector<string>(N);
		for (int j = 0; j < N; j++)
			cin >> words[j];

		answer[i] = WORDCHAIN();
	}

	for (string output : answer) {
		cout << output << endl;
	}

	return 0;
}

string WORDCHAIN() {
	makeGraph();

	if (!checkEuler())		return "IMPOSSIBLE";

	vector<int> circuit = getEulerTrailOrCircuit();
	// 오일러 서킷이 모든 간선을 방문했는지 확인
	if (circuit.size() != words.size() + 1)		return "IMPOSSIBLE";

	reverse(circuit.begin(), circuit.end());

	string ret = "";
	for (int i = 0; i < circuit.size() - 1; i++) {
		int from = circuit[i];
		int to = circuit[i + 1];
		ret += graph[from][to].back() + " ";
		graph[from][to].pop_back();
	}
	return ret;
}

void getEulerCircuit(int node, vector<int>& circuit) {
	for (int i = 0; i < adj[node].size(); i++) {
		while (adj[node][i] > 0) {
			// 방문할 간선을 미리 지우고 해당 간선으로 이동한다.
			adj[node][i]--;
			getEulerCircuit(i, circuit);
		}
	}
	circuit.push_back(node);
}

vector<int> getEulerTrailOrCircuit() {
	vector<int> ret;

	// find EulerTrail
	for (int i = 0; i < 26; i++) {
		if (outdegree[i] == indegree[i] + 1) {
			getEulerCircuit(i, ret);
			return ret;
		}
	}
	// find EulerCircuit
	for (int i = 0; i < 26; i++) {
		if (outdegree[i]) {
			getEulerCircuit(i, ret);
			return ret;
		}
	}
	return ret;
}

bool checkEuler() {
	int plus1 = 0;
	int minus1 = 0;

	for (int i = 0; i < indegree.size(); i++) {
		int diff = indegree[i] - outdegree[i];
		if (diff < -1 || diff > 1)		return false;
		if (diff == 1)		plus1 += 1;
		if (diff == -1)		minus1 += 1;
	}

	/*
	(plus1 == 0 && minus1 == 0)		-> 오일러 서킷이 존재할 조건
	(plus1 == 1 && minus1 == 1)		-> 오일러 트레일이 존재할 조건
	*/
	return (plus1 == 0 && minus1 == 0) || (plus1 == 1 && minus1 == 1);
}

void makeGraph() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			graph[i][j].clear();
		}
	}

	adj = vector<vector<int>>(26, vector<int>(26, 0));
	indegree = vector<int>(26, 0);
	outdegree = vector<int>(26, 0);

	for (int i = 0; i < words.size(); i++) {
		int a = CharToInt(words[i][0]);
		int b = CharToInt(words[i][words[i].size() - 1]);
		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		indegree[b]++;
		outdegree[a]++;
	}
}

int CharToInt(char ch) {
	return ch - 'a';
}
