/*
  url: https://algospot.com/judge/problem/read/PACKING
  
  아래의 코드로 알고스팟에 답안 제출을 하면 다음과 같은 에러메시지와 함께 런타임 오류가 발생한다.
  "RTE (SIGSEGV: segmentation fault, probably incorrect memory access or stack overflow)"
  처음에는 배열의 인덱스 접근에 오류가 있는줄 알았으나, 내가 생각했을 때 이 코드에서 인덱스 접근 오류는 발생하지 않는다는 결론을 내림.
  캐시 메모리의 자료형이 스택이라서 메모리 초과가 발생하고 있다는 결론.
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
	vector<stack<int>> answer(C);

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
		
		answer[i] = solve(0, 0, 0);
	}

	for (int i = 0; i < C; i++) {
		int temp = 0, count = 0;
		string str = "";
		while (!answer[i].empty()) {
			int index = answer[i].top();
			answer[i].pop();
			temp += need[index];
			count++;
			str += object[index] + "\n";
		}
		cout << temp << " " << count << endl << str;
	}

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
