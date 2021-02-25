#include <iostream>
#include <cmath>
#include <vector>
 
using namespace std;
 
double getDistance(int x1, int y1, int x2, int y2);
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
 
	int N;
	cin >> N;
 
	vector<int> answer(N);
	for(int i=0;i<N;i++) {
		int x1, y1, r1, x2, y2, r2;
		cin>>x1>>y1>>r1>>x2>>y2>>r2;
 
		if(x1==x2 && y1==y2 && r1==r2) {
			answer[i] = -1;
			continue;
		}
 
		double distance = getDistance(x1,y1,x2,y2);
		// 외접하는 경우
		if(distance == r1+r2) {
			answer[i] = 1;
		}
		// 내접하는 경우
		else if(distance == abs(r1-r2)) {
			answer[i] = 1;
		} 
		// 두 점에서 만나는 경우
		else if(distance < r1+r2 && distance > abs(r1-r2)) {
			answer[i] = 2;
		}
		// 그 외의 경우
		else {
			answer[i] = 0;
		}
	}
 
	for(int output : answer) {
		cout<<output<<"\n";
	}
 
	return 0;
}
 
double getDistance(int x1, int y1, int x2, int y2) {
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
