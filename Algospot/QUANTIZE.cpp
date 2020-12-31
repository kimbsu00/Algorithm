/*
  url: https://algospot.com/judge/problem/read/QUANTIZE
  
  처음에 문제를 여러개의 부분문제로 어떻게 쪼개야 하는지 감을 못잡아서 많이 헤맨 문제.
  그리고 Quantize() 함수에서 기저 사례 처리 부분에서, if (index == sequence.size()) 조건과 if (count == 0) 조건의 순서를 고려하지 않고 예제 문제에서 오답이 나와서 많이 삽질함.
*/

#include<iostream>
#include<algorithm>
#include<vector>

#define INF 2100000000

using namespace std;

int Quantize(int index, int count);
int getMinError(int start, int end);
int getAverage(int start, int end);

vector<int> sequence;
int N, S;
int cache[101][11];

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		sequence.clear();
		fill(&cache[0][0], &cache[100][11], INF);

		cin >> N >> S;
		
		for (int k = 0; k < N; k++) {
			int temp;
			cin >> temp;
			sequence.push_back(temp);
		}

		sort(sequence.begin(), sequence.end());
		int temp = INF;
		for (int k = 1; k <= S; k++) {
			temp = min(temp, Quantize(0, k));
		}
		answer[i] = temp;
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

// input으로 주어진 수열 sequence를 index번째 위치에서 부터 count만큼 부분 수열로 쪼개서 최소 오차 제곱값을 구하는 함수.
int Quantize(int index, int count) {
  // 기저 사례 처리
	if (index == sequence.size())
		return 0; 

	if (count == 0)
		return INF;

	int& ret = cache[index][count];
	if (ret != INF)
		return ret;

	for (int i = 1; i <= sequence.size() - index; i++) {
		ret = min(ret, getMinError(index, index + i) + Quantize(index + i, count - 1));
	}

	return ret;
}

// [start, end) 범위 내에 존재하는 값들을 양자화할 때, 오차 제곱의 합의 최솟값을 리턴
int getMinError(int start, int end) {
	int average = getAverage(start, end);

	int ret = 0;
	for (int i = start; i < end; i++) {
		ret += (sequence[i] - average) * (sequence[i] - average);
	}

	return ret;
}

// [start, end) 범위 내에 존재하는 값들의 평균을 반올림 해서 리턴
int getAverage(int start, int end) {
	double ret = 0;
	for (int i = start; i < end; i++) {
		ret += sequence[i];
	}
	ret = (ret) / ((double)end - start);

	return (int)(ret + 0.5);
}
