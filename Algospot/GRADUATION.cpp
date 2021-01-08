/*
  url: https://algospot.com/judge/problem/read/GRADUATION
  
  비트마스크 라는 개념을 접하고 처음 풀어본 문제, 비트마스크를 이용하여 공집합을 제외한 모든 부분집합에 쉽게 접할 수 있음을 알고 엄청 놀랐다.
  그리고 컴파일러 내장함수 { __popcnt() : Visual c++  / __builtin_popcount() : gcc } 를 처음 사용해봄.
  
  알고스팟의 채점 시스템(gcc 컴파일러)에 제출할 때에는 74, 97번째 줄을 주석처리 / 75, 98번째 줄을 주석처리 하지 않고 제출해야 함
  Visual C++ 컴파일러로 컴파일 할때에는 74, 97번째 줄을 주석처리 하지 않고 / 75, 98번째 줄을 주석처리 하고 제출해야 함
*/

#include<iostream>
#include<vector>
#include<algorithm>

#define MAX 1000000000

using namespace std;

int GRADUATION(int termNum, unsigned int taken, vector<unsigned int>& preRequired, vector<unsigned int>& term);

int cache[11][1<<12];
int N;		// 전공 과목의 수
int K;		// 들어야 할 과목의 수
int M;	  // 학기의 수
int L;		// 한 학기에 최대로 들을 수 있는 과목의 수

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		fill(&cache[0][0], &cache[10][1<<12], -1);

		cin >> N >> K >> M >> L;

		// index 번째 과목을 듣기 위해서는 preRequired[index] 에서 1로 표시되어 있는 과목을 선이수 해야한다.
		vector<unsigned int> preRequired(N, 0);
		for (int j = 0; j < N; j++) {
			int num;
			cin >> num;
			for (int k = 0; k < num; k++) {
				int shift;
				cin >> shift;
				preRequired[j] |= (1 << shift);
			}
		}

		// index 번째 학기에 열리는 과목은 term[index] 에서 1로 표시되어 있는 과목들이다.
		vector<unsigned int> term(M, 0);
		for (int j = 0; j < M; j++) {
			int num;
			cin >> num;
			for (int k = 0; k < num; k++) {
				int shift;
				cin >> shift;
				term[j] |= (1 << shift);
			}
		}

		answer[i] = GRADUATION(0, 0, preRequired, term);
	}

	for (int i = 0; i < C; i++) {
		if (answer[i] == MAX)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << answer[i] << endl;
	}

	return 0;
}

int GRADUATION(int termNum, unsigned int taken, vector<unsigned int>& preRequired, vector<unsigned int>& term) {
	// 기저 사례 처리
	//if (__popcnt(taken) == K)		return 0;
	if (__builtin_popcount(taken) == K)		return 0;

	if (termNum == M)		return MAX;

	int& ret = cache[termNum][taken];
	if (ret != -1)		return ret;

	ret = MAX;
	int canTake = 0;
	int index = 0;
	// 이번 학기에 열리는 수업들 중에서 수강 가능한 과목들을 canTake 변수에 저장
	canTake = (term[termNum] & ~taken);
	// canTake 에 저장된 과목들 중에서 선수과목 때문에 수강할 수 없는 과목들을 걸러
	for (int i = 0; i < N; i++) {
		if (canTake & (1 << i)) {
			if ((taken & preRequired[i]) != preRequired[i]) {
				canTake &= ~(1 << i);
			}
		}
	}

	// 수강 가능한 과목들의 모든 부분집합에 대하여 (공집합 제외)
	for (int subset = canTake; subset; subset = ((subset - 1) & canTake)) {
		//if (__popcnt(subset) <= L) {
		if (__builtin_popcount(subset) <= L) {
			ret = min(ret, 1 + GRADUATION(termNum + 1, taken | subset, preRequired, term));
		}
	}

	// 이번학기에 아무것도 듣지 않을 경우도 고려
	ret = min(ret, GRADUATION(termNum + 1, taken, preRequired, term));

	return ret;
}
