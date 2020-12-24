/*
  url: https://algospot.com/judge/problem/read/PACKING
  
  시간초과
*/

#include<iostream> 
#include<vector>
#include<stack>
#include<string>
#include<algorithm>

using namespace std;

stack<int> solve(int index, int v, int n);
int getSum(stack<int> stk);

stack<int> cache[1001][100];

int N, W;

vector<string> object;
vector<int> volume;
vector<int> need;

int main(void) {
	int C;
	cin >> C;
	vector<string> answer;

	for (int i = 0; i < C; i++) {
		fill(&cache[0][0], &cache[1000][100], stack<int>());

		cin >> N >> W;

		object.clear();
		volume.clear();
		need.clear();
		for (int k = 0; k < N; k++) {
			string name;
			int v, n;
			cin >> name >> v >> n;
			object.push_back(name);
			volume.push_back(v);
			need.push_back(n);
		}
		
		stack<int> temp = solve(0, 0, 0);
		int sum = 0, count = temp.size();
		string str = "";
		while (!temp.empty()) {
			int index = temp.top();
			temp.pop();
			sum += need[index];
			str += object[index] + "\n";
		}
		answer.push_back(to_string(sum) + " " + to_string(count) + "\n" + str);
	}

	for (int i = 0; i < C; i++)
		cout << answer[i];

	return 0;
}

stack<int> solve(int index, int v, int n) {
	if (index == N) return stack<int>();

	if (v > W)	return stack<int>();

	stack<int>& ret = cache[v][index];
	if (!ret.empty())	return ret;

	ret = solve(index + 1, v, n);
	if (v + volume[index] <= W) {
		stack<int> pack = solve(index + 1, v + volume[index], n + need[index]);
		pack.push(index);
		ret = getSum(ret) > getSum(pack) ? ret : pack;
	}

	return ret;
}

int getSum(stack<int> stk) {
	int ret = 0;
	while (!stk.empty()) {
		int index = stk.top();
		stk.pop();
		ret += need[index];
	}
	return ret;
}
