/*
  url: https://www.acmicpc.net/problem/9372
  
  처음에 문제를 잘못 읽어서 정답으로 출력해야 되는 값이
  모든 국가를 한 번씩 방문하기 위해 필요한 비행기 탑승 횟수로 이해를 했다.
  이 때문에 처음에 dfs 를 이용해서 이것저것 시도하게 되었고,
  정답 제출 결과는 당연히 오답 처리..
  
  도저히 내 알고리즘의 반례가 떠오르지 않아 질문 게시판을 찾아본 결과,
  MST 를 구하는 문제인데, 모든 간선의 가중치가 1 이므로,
  모든 MST 는 N-1 개의 간선을 갖는다. 
  따라서 정답은 N-1 이다.
  라는 게시글을 봤고, 여기서 아차... 싶었다.
  
  그리고 문제를 다시 읽어본 결과 "비행기의 종류" 를 구하는 문제였던 것...
*/

#include<iostream>
#include<vector>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int T;
	cin >> T;
	vector<int> answer(T, 0);

	for (int i = 0; i < T; i++) {
		int N, M;		// 국가의 수, 비행기의 수
		cin >> N >> M;

		for (int j = 0; j < M; j++) {
			int a, b;
			cin >> a >> b;
		}

		answer[i] = N - 1;
	}

	for (int output : answer) {
		cout << output << "\n";
	}

	return 0;
}
