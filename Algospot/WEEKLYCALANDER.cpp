/*
  url: https://algospot.com/judge/problem/read/WEEKLYCALENDAR
*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;

vector<int> WEEKLYCALANDER(int m, int d, string day);

string DAYS[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
// index+1 월에 31일이 존재하는지 여부를 저장
bool MONTH[12] = { true, false, true, false, true ,false, true, true, false , true, false, true };

int main(void) {
	int C;
	cin >> C;
	vector<vector<int>> answer(C);

	for (int i = 0; i < C; i++) {
		int m, d;
		string day;
		cin >> m >> d >> day;

		answer[i] = WEEKLYCALANDER(m, d, day);
	}

	for (int i = 0; i < C; i++) {
		for (int k = 0; k < 7; k++)
			cout << answer[i][k] << " ";
		cout << endl;
	}

	return 0;
}

vector<int> WEEKLYCALANDER(int m, int d, string day) {
	vector<int> ret(7);
	
	int index = -1;
	for (int i = 0; i < 7; i++) {
		if (day == DAYS[i]) {
			index = i;
			break;
		}
	}

	if (m == 1) {
		for (int i = 0; i < 7; i++) {
			ret[i] = d - index + i <= 0 ? d + 31 - index + i : (d - index + i) % 31;
			if (ret[i] == 0)		ret[i] = 31;
		}
	}
	else if (m == 2) {
		for (int i = 0; i < 7; i++) {
			ret[i] = d - index + i <= 0 ? d + 31 - index + i : (d - index + i) % 28;
			if (ret[i] == 0)		ret[i] = 28;
		}
	}
	else if (m == 3) {
		for (int i = 0; i < 7; i++) {
			ret[i] = d - index + i <= 0 ? d + 28 - index + i : (d - index + i) % 31;
			if (ret[i] == 0)		ret[i] = 31;
		}
	}
	else if (m == 8) {
		for (int i = 0; i < 7; i++) {
			ret[i] = d - index + i <= 0 ? d + 31 - index + i : (d - index + i) % 31;
			if (ret[i] == 0)		ret[i] = 31;
		}
	}
	else if (MONTH[m-1]) {
		for (int i = 0; i < 7; i++) {
			ret[i] = d - index + i <= 0 ? d + 30 - index + i : (d - index + i) % 31;
			if (ret[i] == 0)		ret[i] = 31;
		}
	}
	else {
		for (int i = 0; i < 7; i++) {
			ret[i] = d - index + i <= 0 ? d + 31 - index + i : (d - index + i) % 30;
			if (ret[i] == 0)		ret[i] = 30;
		}
	}
	
	return ret;
}
