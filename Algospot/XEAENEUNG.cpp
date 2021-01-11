/*
  url: https://algospot.com/judge/problem/read/XHAENEUNG
  
  정답 출력에서 "Yes" or "No" 인데 "YES" or "NO" 를 출력해서 계속 오답으로 처리된 문제.
  문제를 똑바로 읽자!
*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

bool XEAENEUNG(vector<string>& parsing);

int main(void) {
	int C;
	cin >> C;
	vector<bool> answer(C);

	for (int i = 0; i < C; i++) {
		vector<string> parsing;
		for (int i = 0; i < 5; i++) {
			string input;
			cin >> input;
			parsing.push_back(input);
		}
		answer[i] = XEAENEUNG(parsing);
	}

	for (int i = 0; i < C; i++) {
		if (answer[i])
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}

	return 0;
}

bool XEAENEUNG(vector<string>& parsing) {
	bool ret = false;
	int left = -1, right = -1;
	string number[11] = { "zero","one","two","three","four","five","six","seven","eight","nine","ten" };
	for (int i = 0; i < 11; i++) {
		if (parsing[0] == number[i])		left = i;
		if (parsing[2] == number[i])		right = i;
		if (left != -1 && right != -1)		break;
	}
	
	int result = -1;
	if (parsing[1] == "+") {
		result = left + right;
	}
	else if (parsing[1] == "-") {
		result = left - right;
	}
	else if (parsing[1] == "*") {
		result = left * right;
	}

	if (result > 10 || result < 0)		return false;

	switch (result) {
	case 0:
		if (parsing[4].size() == 4) {
			int z = 0, e = 0, r = 0, o = 0;
			for (int index = 0; index < parsing[4].size(); index++) {
				if (parsing[4][index] == 'z')		z++;
				else if (parsing[4][index] == 'e')		e++;
				else if (parsing[4][index] == 'r')		r++;
				else if (parsing[4][index] == 'o')		o++;
			}
			if (z == 1 && e == 1 && r == 1 && o == 1)		ret = true;
		}
		break;
	case 1:
		if (parsing[4].size() == 3) {
			int o = 0, n = 0, e = 0;
			for (int index = 0; index < parsing[4].size(); index++) {
				if (parsing[4][index] == 'o')		o++;
				else if (parsing[4][index] == 'n')		n++;
				else if (parsing[4][index] =='e')		e++;
			}
			if (o == 1 && n == 1 && e == 1)		ret = true;
		}
		break;
	case 2:
		if (parsing[4].size() == 3) {
			int t = 0, w = 0, o = 0;
			for (int index = 0; index < parsing[4].size(); index++) {
				if (parsing[4][index] == 't')		t++;
				else if (parsing[4][index] =='w')		w++;
				else if (parsing[4][index] == 'o')		o++;
			}
			if (t == 1 && w == 1 && o == 1)		ret = true;
		}
		break;
	case 3:
		if (parsing[4].size() == 5) {
			int t = 0, h = 0, r = 0, e = 0;
			for (int index = 0; index < parsing[4].size(); index++) {
				if (parsing[4][index] == 't')		t++;
				else if (parsing[4][index] == 'h')		h++;
				else if (parsing[4][index] == 'r')		r++;
				else if (parsing[4][index] == 'e')		e++;
			}
			if (t == 1 && h == 1 && r == 1 && e == 2)		ret = true;
		}
		break;
	case 4:
		if (parsing[4].size() == 4) {
			int f = 0, o = 0, u = 0, r = 0;
			for (int index = 0; index < parsing[4].size(); index++) {
				if (parsing[4][index] == 'f')		f++;
				else if (parsing[4][index] == 'o')		o++;
				else if (parsing[4][index] == 'u')		u++;
				else if (parsing[4][index] == 'r')		r++;
			}
			if (f == 1 && o == 1 && u == 1 && r == 1)		ret = true;
		}
		break;
	case 5:
		if (parsing[4].size() == 4) {
			int f = 0, i = 0, v = 0, e = 0;
			for (int index = 0; index < parsing[4].size(); index++) {
				if (parsing[4][index] == 'f')		f++;
				else if (parsing[4][index] == 'i')		i++;
				else if (parsing[4][index] =='v')		v++;
				else if (parsing[4][index] == 'e')		e++;
			}
			if (f == 1 && i == 1 && v == 1 && e == 1)		ret = true;
		}
		break;
	case 6:
		if (parsing[4].size() == 3) {
			int s = 0, i = 0, x = 0;
			for (int index = 0; index < parsing[4].size(); index++) {
				if (parsing[4][index] == 's')		s++;
				else if (parsing[4][index] == 'i')		i++;
				else if (parsing[4][index] == 'x')		x++;
			}
			if (s == 1 && i == 1 && x == 1)		ret = true;
		}
		break;
	case 7:
		if (parsing[4].size() == 5) {
			int s = 0, e = 0, v = 0, n = 0;
			for (int index = 0; index < parsing[4].size(); index++) {
				if (parsing[4][index] == 's')		s++;
				else if (parsing[4][index] == 'e')		e++;
				else if (parsing[4][index] == 'v')		v++;
				else if (parsing[4][index] == 'n')		n++;
			}
			if (s == 1 && e == 2 && v == 1 && n == 1)		ret = true;
		}
		break;
	case 8:
		if (parsing[4].size() == 5) {
			int e = 0, i = 0, g = 0, h = 0, t = 0;
			for (int index = 0; index < parsing[4].size(); index++) {
				if (parsing[4][index] == 'e')		e++;
				else if (parsing[4][index] == 'i')		i++;
				else if (parsing[4][index] == 'g')		g++;
				else if (parsing[4][index] == 'h')		h++;
				else if (parsing[4][index] == 't')		t++;
			}
			if (e == 1 && i == 1 && g == 1 && h == 1 && t == 1)		ret = true;
		}
		break;
	case 9:
		if (parsing[4].size() == 4) {
			int n = 0, i = 0, e = 0;
			for (int index = 0; index < parsing[4].size(); index++) {
				if (parsing[4][index] == 'n')		n++;
				else if (parsing[4][index] =='i')		i++;
				else if (parsing[4][index] == 'e')		e++;
			}
			if (n == 2 && i == 1 && e == 1)		ret = true;
		}
		break;
	case 10:
		if (parsing[4].size() == 3) {
			int t = 0, e = 0, n = 0;
			for (int index = 0; index < parsing[4].size(); index++) {
				if (parsing[4][index] == 't')		t++;
				else if (parsing[4][index] == 'e')		e++;
				else if (parsing[4][index] == 'n')		n++;
			}
			if (t == 1 && e == 1 && n == 1)		ret = true;
		}
		break;
	}

	return ret;
}

/*
문제의 인풋 조건을 제대로 확인하지 않고 생각할 때, string 을 token 을 기준으로 자르는 함수가 필요하다고 생각해서 구현했음.
token 을 기준으로 str 을 자른 조각들을 vector<string> 에 저장해서 리턴하는 함수.
#include<sstream> 
*/
vector<string> split(string& str, char token) {
	vector<string> ret;
	stringstream ss(str);
	string temp;

	while (getline(ss, temp, token)) {
		ret.push_back(temp);
	}

	return ret;
}
