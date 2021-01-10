/*
  url: https://algospot.com/judge/problem/read/FESTIVAL
*/

#include<iostream>
#include<vector>
#include<algorithm>

#define MAX 10000000

using namespace std;

double FESTIVAL();
int rangeSum(int start, int end);

int N, L;
vector<int> partialSum;

int main(void) {
	int C;
	cin >> C;
	vector<double> answer(C);

	for (int i = 0; i < C; i++) {
		partialSum.clear();

		cin >> N >> L;
		
		int temp = 0;
		for (int k = 0; k < N; k++) {
			int input;
			cin >> input;
			temp += input;
			partialSum.push_back(temp);
		}

		answer[i] = FESTIVAL();
	}

	for (int i = 0; i < C; i++)
		printf("%.8lf\n", answer[i]);

	return 0;
}

double FESTIVAL() {
	double ret = MAX;

	for (int i = 0; i < partialSum.size(); i++) {
		for (int j = i + L - 1; j < partialSum.size(); j++) {
			ret = min(ret, (double)rangeSum(i, j) / (j - i + 1));
		}
	}

	return ret;
}

int rangeSum(int start, int end) {
	if (start == 0)		return partialSum[end];

	return partialSum[end] - partialSum[start - 1];
}
