/*
  url: https://algospot.com/judge/problem/read/MAXSUM
  
  처음에 문제 읽었을 때는 별거 아닌 문제라고 생각했는데,
  14번 만에 정답처리 받은 문제.
*/

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		int N;
		cin >> N;

		int sum = 0;		// 양수만 합한 값
		int any = 0;			// 합이 음수가 아니라면 뭐든지 다 합하는 값, 합이 음수가 되면 0으로 초기화
		int ret = 0;
		for (int k = 0; k < N; k++) {
			int num;
			cin >> num;
			num > 0 ? sum += num : sum = 0;
			any + num >= 0 ? any += num : any = 0;
			ret = max(ret, max(num, any));
		}
		
		answer[i] = ret;
	} 

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}
