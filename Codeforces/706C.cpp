/*
  url: https://codeforces.com/problemset/problem/706/C
  
  처음에 cache 메모리를 LL_MAX 로 초기화했었는데, 이렇게 하니깐 계속 시간 초과가 발생했다.
  알고리즘에는 특별한 오류가 존재하지 않았는데도 불구하고 시간 초과가 발생해서 어느 부분에서 문제가 발생하는지 감이 잘 안 잡혔고,
  그래서 한 시간 정도 고생하다가 cache 메모리에 LL_MAX 값이 들어가 있는 경우도 존재하므로,
  이 경우를 위해서 cache 메모리를 -1로 초기화해서 제출해본 결과 ACCEPT!
*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

long long solve(int index, int check, string prev);

int N;
long long cost[100000];
string input[100000][2];
long long cache[100000][2];
long long LL_MAX = 1000000000000000000LL;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cost[i];
	}

	for (int i = 0; i < N; i++) {
		cin >> input[i][0];
		input[i][1] = input[i][0];
		reverse(input[i][1].begin(), input[i][1].end());
	}

	long long answer = solve(0, 0, "");
	cout << (answer == LL_MAX ? -1 : answer) << "\n";

	return 0;
}

long long solve(int index, int check, string prev) {
	if (index == N)			return 0;

	long long& ret = cache[index][check];
	if (ret != -1)			return ret;
	ret = LL_MAX;

	if (input[index][0].compare(prev) >= 0) {
		ret = min(ret, solve(index + 1, 0, input[index][0]));
	}

	if (input[index][1].compare(prev) >= 0) {
		ret = min(ret, solve(index + 1, 1, input[index][1]) + cost[index]);
	}

	return ret;
}
