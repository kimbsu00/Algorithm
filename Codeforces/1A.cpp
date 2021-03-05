/*
  url: https://codeforces.com/problemset/problem/1/A
*/

#include<iostream>
 
using namespace std;
 
int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
 
	int n, m, a;
	cin >> n >> m >> a;
	int count1 = 0, count2 = 0;
	while(n>0) {
		n -= a;
		count1++;
	}
	while (m > 0) {
		m -= a;
		count2++;
	}
 
	cout << (long long)count1 * (long long)count2 << "\n";
 
	return 0;
}
