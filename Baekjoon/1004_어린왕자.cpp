/*
  url: https://www.acmicpc.net/problem/1004
*/

#include <iostream>
#include <vector>
#include <cmath>
 
using namespace std;

double getDistance(int x1, int y1, int x2, int y2);
int isPassed(int x, int y, int r);
 
pair<int ,int> start, dest;
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
 
	int T;
	cin>>T;
	vector<int> answer(T, 0);
	for(int i=0; i<T; i++) {
		cin>>start.first>>start.second>>dest.first>>dest.second;
 
		int n;
		cin>>n;
		for(int j=0; j<n; j++) {
			int x, y, r;
			cin>>x>>y>>r;
 
			answer[i] += isPassed(x, y, r);
		}
	}
 
	for(int output : answer) {
		cout << output << "\n";
	}
 
	return 0;
}
 
double getDistance(int x1, int y1, int x2, int y2) {
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
 
int isPassed(int x, int y, int r) {
	double from_start = getDistance(x, y, start.first, start.second);
	double from_end = getDistance(x, y, dest.first, dest.second);
 
	double check = (from_start - r) * (from_end - r);
	if(check < 0)			return 1;
	return 0;
}
