/*
  url: https://algospot.com/judge/problem/read/ZEROONE
  
  31, 33번 줄에 있는 printf() 함수를 사용해서 정답을 출력하면 1228ms 가 걸리고,
                     cout 함수를 사용해서 정답을 출력하면 1208ms 가 걸린다?
                     printf() 가 cout 보다 훨씬 더 빠른거로 알고 있는데 뭔가 이상하다..
*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

string str;
vector<int> sequence;

int main(void) {
	int  C;
	cin >> str >> C;

	int index = 0;
	sequence.push_back(index);
	for (int i = 1; i < str.size(); i++) {
		str[i - 1] == str[i] ? sequence.push_back(index) : sequence.push_back(++index);
	}
	
	for (int i = 0; i < C; i++) {
		int start, end;
		cin >> start >> end;

		if (sequence[start] == sequence[end])
			printf("Yes\n");
		else
			printf("No\n");
	}

	return 0;
}
