/*
  url: https://codeforces.com/problemset/problem/327/A
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int solve(int index, int flip);

vector<int> input;
int cache[100][2];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, 100 * 2 * sizeof(int));
	int N;
	cin >> N;
	input = vector<int>(N);
	for (int i = 0; i < N; i++) {
		cin >> input[i];
	}

	int output = -1;
	int temp = 0;
	for (int i = 0; i < N; i++) {
		output = max(output, temp + solve(i, 1));
		temp += input[i];
	}

	cout << output << "\n";

	return 0;
}

/*
flip = 0 인 경우 -> index 번째 값을 not flip
flip = 1 인 경우 -> index 번째 값을 flip
*/
int solve(int index, int flip) {
	if (index == input.size())			return 0;

	int& ret = cache[index][flip];
	if (ret != -1)			return ret;

	// index 번째 값을 flip 한 경우에는 index+1 번째 값을 flip 해도 되고, 안해도 된다.
	if (flip) {
		ret = (1 - input[index]) + max(solve(index + 1, 0), solve(index + 1, 1));
	}
	// index 번째 값을 flip 하지 않은 경우에는 index+1 번째 값은 flip 할 수 없다.
	else {
		ret = input[index] + solve(index + 1, 0);
	}

	return ret;
}
