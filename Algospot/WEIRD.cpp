/*
  url: https://algospot.com/judge/problem/read/WEIRD
  
  52번째 줄에서 true 를 리턴해야 되는데 실수로 false 를 리턴해서 한참동안 헤맨 문제
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool WEIRD();
bool recursion(int index, int sum, vector<int>& divisors);
vector<int> getDivisors(int input);

int input;

int main(void) {
	int C;
	cin >> C;
	vector<bool> answer(C);

	for (int i = 0; i < C; i++) {
		cin >> input;

		answer[i] = WEIRD();
	}

	for (int i = 0; i < C; i++) {
		if (answer[i])
			cout << "not weird" << endl;
		else
			cout << "weird" << endl;
	}

	return 0;
}

/* 
if input is weird number -> return false 
else			 -> return true
*/
bool WEIRD() {
	vector<int> divisors = getDivisors(input);
	sort(divisors.begin(), divisors.end(), greater<int>());

	int sum = 0;
	for (int divisor : divisors)
		sum += divisor;

	if (sum <= input)		return true;

	return recursion(0, 0, divisors);
}

bool recursion(int index, int sum, vector<int>& divisors) {
	if (sum == input)
		return true;

	if (sum > input)
		return false;

	if (index >= divisors.size())
		return false;

	return recursion(index + 1, sum + divisors[index], divisors) || recursion(index + 1, sum, divisors);
}

// input 을 제외한 input 의 약수를 저장하는 배열을 리턴
vector<int> getDivisors(int input) {
	vector<int> ret;
	int i;
	ret.push_back(1);
	for (i = 2; i * i < input; i++) {
		if (input % i == 0) {
			ret.push_back(i);
			ret.push_back(input / i);
		}
	}

	if (i * i == input)
		ret.push_back(i);

	return ret;
}
