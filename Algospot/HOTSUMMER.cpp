/*
  url: https://algospot.com/judge/problem/read/HOTSUMMER
*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main(void) {
	int T;
	cin >> T;
	vector<string> answer(T);

	for (int i = 0; i < T; i++) {
		int target, sum = 0;
		cin >> target;
		for (int k = 0; k < 9; k++) {
			int temp;
			cin >> temp;
			sum += temp;
		}
		if (sum <= target)
			answer[i] = "YES";
		else
			answer[i] = "NO";
	}

	for (int i = 0; i < T; i++)
		cout << answer[i] << endl;

	return 0;
}
