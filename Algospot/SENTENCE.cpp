/*
  url: https://algospot.com/judge/problem/read/SENTENCE
*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

int SENTENCE();

int M, N;
vector<vector<char>> book;
vector<vector<char>> memo;

int main(void) {
	cin >> M >> N;
	getchar();
	
	for (int i = 0; i < M; i++) {
		string str;
		getline(cin, str);
		vector<char> vec;
		for (int k = 0; k < str.size(); k++) {
			vec.push_back(str[k]);
		}
		book.push_back(vec);
	}

	for (int i = 0; i < N; i++) {
		string str;
		getline(cin, str);
		vector<char> vec;
		for (int k = 0; k < str.size(); k++) {
			vec.push_back(str[k]);
		}
		memo.push_back(vec);
	}

	int output = SENTENCE();
	cout << output << endl;
	
	return 0;
}

int SENTENCE() {
	int ret = 0;
  
  // 각각의 메모에 대한 for loop
	for (int i = 0; i < memo.size(); i++) {
		bool check = true;
    // 메모를 책에 적혀있는 문구와 비교하기 위한 for loop
		for (int j = 0; j < book.size(); j++) {
      // 메모가 책에 적혀있는 문구의 접두사(prefix) 이기 때문에 메모의 길이만큼만 확인해주면 된다.
			for (int k = 0; k < memo[i].size(); k++) {
				if (memo[i][k] == book[j][k]) {

				}
				else {
					check = false;
				}

				if (!check)		break;
			}

			if (check) {
				ret++;
				break;
			}
			else {
				check = true;
			}
		}
	}

	return ret;
}
