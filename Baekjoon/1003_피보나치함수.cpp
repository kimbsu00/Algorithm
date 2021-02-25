/*
  url: https://www.acmicpc.net/problem/1003
*/

#include <iostream>
#include <vector>
 
using namespace std;
 
pair<int, int> Fibonacci(int n);
 
pair<int, int> cache[41];
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
 
	int T;
	cin>>T;
	
	fill(&cache[0], &cache[41], make_pair(-1, -1));
	vector<pair<int, int>> answer(T, pair<int, int>());
	for(int i=0; i<T; i++) {
		int n;
		cin>>n;
		answer[i] = Fibonacci(n);
	}
 
	for(pair<int,int> output : answer) {
		cout<< output.first << " " << output.second << "\n";
	}
 
	return 0;
}
 
pair<int, int> Fibonacci(int n) {
	pair<int, int>& ret = cache[n];
	if(ret.first != -1 && ret.first != -1)
		return ret;
	
	ret.first = 0;
	ret.second = 0;
	if(n == 0) {
		ret.first += 1;
	}
	else if(n == 1) {
		ret.second += 1;
	}
	else {
		pair<int, int> n_1 = Fibonacci(n-1); 
		ret.first += n_1.first;
		ret.second += n_1.second;
		pair<int, int> n_2 = Fibonacci(n-2);
		ret.first += n_2.first;
		ret.second += n_2.second;
	}
	return ret;
}
