/*
  url: https://www.acmicpc.net/problem/2533
  
  처음 이 문제를 읽었을 때 바로 떠오른 해결방법은 다음과 같다.
  "트리에 존재하는 모든 노드들에 대하여, 레벨이 짝수인 노드와 홀수인 노드들을 카운트하면 
  짝수 레벨의 노드와 홀수 레벨의 노드중에서 더 적은 수의 노드들을 얼리어답터로 하면 되겠다."
  
  위의 아이디어로 코딩을 해서 제출한 결과, 오답처리...
  확실한 반례는 생각해내지 못했지만 결국 "부모와 자식이 모두 얼리어답터인 경우가 존재할 수 도 있구나" 를 깨닫게 되었고,
  이를 바탕으로 문제를 해결함.
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int getEarlyAdapter(int node, bool isAdapter);

vector<vector<int>> tree;
vector<bool> visited;
int cache[1000000][2];

int main(void) {
	// cin 함수의 속도 향상을 위한 코드
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	tree = vector<vector<int>>(N, vector<int>());
	visited = vector<bool>(N, false);
	fill(&cache[0][0], &cache[999999][2], -1);

	for (int i = 1; i < N; i++) {
		int a, b;
		cin >> a >> b;
		tree[a - 1].push_back(b - 1);
		tree[b - 1].push_back(a - 1);
	}

	cout << min(getEarlyAdapter(0, true), getEarlyAdapter(0, false)) << "\n";

	return 0;
}

int getEarlyAdapter(int node, bool isAdapter) {
	visited[node] = true;

	int& ret = cache[node][isAdapter];
	if (ret != -1)			return ret;

	isAdapter ? ret = 1 : ret = 0;

	for (int next : tree[node]) {
		if (!visited[next]) {
			// node 가 얼리어답터라면, node 의 자식은 얼리어답터여도 되고, 얼리어답터가 아니어도 된다.
			if (isAdapter) {
				ret += min(getEarlyAdapter(next, true), getEarlyAdapter(next, false));
			}
			// node 가 얼리어답터가 아니라면, node 의 자식은 얼리어답터여만 한다.
			else {
				ret += getEarlyAdapter(next, true);
			}
		}
	}

	/* 
	node 가 얼리어답터인 경우,
	node 의 자식이 얼리어답터인 경우 1가지, 얼리어답터가 아닌 경우 1가지
	총 2번의 재귀호출이 발생하는데 이때 visited[node] = false 를 하지 않으면
	2번째로 호출되는 재귀호출에서 visited[node] 값이 true 로 설정되어 있는 경우가 발생하므로, 
	재귀호출이 끝나기 직전에 다시 false 로 바꿔주었음.

	visited 값을 false 로 바꾸면 나중에 재방문 하는 경우가 발생할수도 있지 않나??
	-> 발생하지 않는다.
	     이유는 루트 노드에서 부터 dfs 를 이용하기 때문이다.
	*/
	visited[node] = false;

	return ret;
}
