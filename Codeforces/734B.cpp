/*
  url: https://codeforces.com/problemset/problem/734/B
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int solve(vector<int> digits);

vector<int> input(4);

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 4; i++) {
		cin >> input[i];
	}

	int answer = solve(input);
	cout << answer << "\n";
	
	return 0;
}

int solve(vector<int> digits) {
	int ret = 0;

	if (digits[0] > 0 && digits[2] > 0 && digits[3] > 0) {
		int minCount = min(digits[0], min(digits[2], digits[3]));
		digits[0] -= minCount;
		digits[2] -= minCount;
		digits[3] -= minCount;
		ret = max(ret, 256 * minCount + solve(digits));
	} 

	if (ret == 0 && digits[0] > 0 && digits[1] > 0) {
		int minCount = min(digits[0], digits[1]);
		digits[0] -= minCount;
		digits[1] -= minCount;
		ret = max(ret, 32 * minCount + solve(digits));
	}

	return ret;
}
