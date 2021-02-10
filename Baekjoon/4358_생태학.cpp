/*
  url: https://www.acmicpc.net/problem/4358
  
  c++ 의 map 은 중복된 key 값을 허용하지 않는다.
  map 의 insert 함수는 리턴 값으로 pair<iterator, bool> 를 리턴한다.
  
  만약 추가하고자 하는 키 값이 이미 존재할 경우,
  iterator 에는 이미 존재하는 pair<key, value> 를 저장하고, bool 에는 false 를 저장한다.
  
  추가하고자 하는 키 값이 새로운 키 값인 경우,
  iterator 에는 새로 추가된 pair<key, value> 를 저장하고, bool 에는 true 를 저장한다.
*/

#include<iostream>
#include<string>
#include<map>

using namespace std;

int main(void) {	
	int count = 0;
	map<string, int> trie;

	string input;
	while (getline(cin, input)) {
		if (cin.eof())		break;

		count += 1;
		auto it = trie.insert(make_pair(input, 1));
		if (!it.second) {
			it.first->second += 1;
		}
	}

	for (map<string, int>::iterator it = trie.begin(); it != trie.end(); it++) {
		double ratio = (double)it->second / (double)count * 100;
		cout << it->first << " ";
		printf("%.4lf\n", ratio);
	}

	return 0;
}
