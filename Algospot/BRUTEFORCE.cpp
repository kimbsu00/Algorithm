/*
  url: https://algospot.com/judge/problem/read/BRUTEFORCE
  
  main() 함수를 제외한 다른 함수에서 연산을 수행하는 중간중간에 % 연산을 수행하는 이유는 % 연산자의 특성 때문.
*/

#include<iostream>
#include<vector>

#define MOD 1000000007

using namespace std;

int BRUTEFORCE(int min, int max, int N);
long long calculate(int base, int length);
long long pow(int base, int exponent);

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		int A, B, N;
		cin >> A >> B >> N;

		answer[i] = BRUTEFORCE(A, B, N);
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

int BRUTEFORCE(int min, int max, int N) {
	int ret = 0;

	ret = ((calculate(N, max) - calculate(N, min - 1)) + MOD) % MOD;

	return ret;
}

/*
	base^1 + base^2 + base^3 + ... + base^length 의 값을 리턴하는 함수
	ex)
	base == 3, length == 9 라고 가정하면,
	3^1 + 3^2 + 3^3 + 3^4 + 3^5 + 3^6 + 3^7 + 3^8 + 3^9
	= (3^1 + 3^2 + 3^3 + 3^4) + 3^4 x (3^1 + 3^2 + 3^3 + 3^4) +3^9
	= (3^1 + 3^2 + 3^3 + 3^4) x (1 + 3^4) +3^9 가 되므로
	
	calculate(base, 2a+1) = calculate(base, 2a) + base^(2a+1) 
	calculate(base, 2a) = calculate(base, 2) x (1 + base^a) 가 된다.
*/
long long calculate(int base, int length) {
	// 기저 사례 처리
	if (length == 0)
		return 0;

	if (length == 1)
		return (long long)base;

	long long ret = calculate(base, length / 2);
	ret %= MOD;
	ret = ret * (pow(base, length / 2) + 1);
	ret %= MOD;

	if (length % 2 == 1) {
		ret += pow(base, length) % MOD;
		ret %= MOD;
	}
	
	return ret;
}

// base^exponent 의 값을 구하는 함수
long long pow(int base, int exponent) {
	// 기저 사례 처리
	if (exponent == 0)
		return (long long)1;

	if (exponent == 1)
		return (long long)base;

	long long ret = pow(base, exponent / 2) % MOD;
	ret *= ret;
	ret %= MOD;

	if (exponent % 2 == 1) {
		ret *= base;
		ret %= MOD;
	}

	return ret;
}
