/*
  url: https://algospot.com/judge/problem/read/CONVERT
*/

#include<iostream>
#include<vector>
#include<string>

#define KILOGRAM "kg"
#define POUND "lb"
#define LITER "l"
#define GALLON "g"

using namespace std;

pair<double, string> CONVERT(double input, string unit);

int main(void) {
	int C;
	cin >> C;
	vector<pair<double, string>> answer(C);

	for (int i = 0; i < C; i++) {
		double input;
		string unit;
		cin >> input >> unit;

		answer[i] = CONVERT(input, unit);
	}

	for (int i = 0; i < C; i++) {
		printf("%d %.4lf ", i + 1, answer[i].first);
		cout << answer[i].second << endl;
	}

	return 0;
}

pair<double, string> CONVERT(double input, string unit) {
	pair<double, string> ret(-1, "");
	if (unit == KILOGRAM) {
		ret.first = 2.2046 * input;
		ret.second = POUND;
	}
	else if (unit == POUND) {
		ret.first = 0.4536 * input;
		ret.second = KILOGRAM;
	}
	else if (unit == LITER) {
		ret.first = 0.2642 * input;
		ret.second = GALLON;
	}
	else if (unit == GALLON) {
		ret.first = 3.7854 * input;
		ret.second = LITER;
	}
	return ret;
}
