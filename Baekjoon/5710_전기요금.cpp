/*
  url: https://www.acmicpc.net/problem/5710
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int calculate_pay(int wh) {
	int ret = 0;

	if (wh <= 100) {
		ret += wh * 2;
	}
	else if (wh <= 10000) {
		ret += (100 * 2);
		wh -= 100;
		ret += wh * 3;
	}
	else if (wh <= 1000000) {
		ret += (100 * 2) + (9900 * 3);
		wh -= 10000;
		ret += wh * 5;
	} 
	else{
		ret += (100 * 2) + (9900 * 3) + (990000 * 5);
		wh -= 1000000;
		ret += wh * 7;
	}

	return ret;
}

int solve(int A, int B) {
	int sum_of_wh = 0;
	if (A <= (100 * 2)) {
		sum_of_wh = A / 2;
	}
	else if (A <= (100 * 2) + (9900 * 3)) {
		sum_of_wh += 100;
		sum_of_wh += (A - (100 * 2)) / 3;
	}
	else if (A <= (100 * 2) + (9900 * 3) + (990000 * 5)) {
		sum_of_wh += 10000;
		sum_of_wh += (A - ((100 * 2) + (9900 * 3))) / 5;
	}
	else {
		sum_of_wh += 1000000;
		sum_of_wh += (A - ((100 * 2) + (9900 * 3) + (990000 * 5))) / 7;
	}

	int ret = -1;
	int start = 0, end = sum_of_wh;
	/*
	* x는 상근이의 전기 사용량
	* y는 이웃의 전기 사용량
	*/
	int x = 0, y = 0;
	while (true) {
		int mid = (start + end) / 2;
		x = mid;
		y = sum_of_wh - mid;

		int x_pay = calculate_pay(x);
		int y_pay = calculate_pay(y);
		int diff = abs(x_pay - y_pay);

		if (diff > B) {
			start = mid;
		}
		else if (diff < B) {
			end = mid;
		}
		else {
			ret = x_pay;
			break;
		}
	}
	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<int> answer;

	while (true) {
		int A, B;
		cin >> A >> B;

		if (A == 0 && B == 0)			break;

		answer.push_back(solve(A, B));
	}

	for (int ans : answer) {
		cout << ans << "\n";
	}

	return 0;
}
