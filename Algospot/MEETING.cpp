/*
  url: https://algospot.com/judge/problem/read/MEETING
  
  Quick Sort 를 이용하여 오름차순 정렬해서 풀었음.
*/

#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

vector<int> QuickSort(vector<int> list);

int main(void) {
	int T;
	cin >> T;
	vector<int> answer(T, 0);

	for (int i = 0; i < T; i++) {
		int N;
		cin >> N;

		vector<int> man;
		vector<int> woman;
		for (int k = 0; k < N; k++) {
			int num;
			cin >> num;
			man.push_back(num);
		}
		for (int k = 0; k < N; k++) {
			int num;
			cin >> num;
			woman.push_back(num);
		}

		man = QuickSort(man);
		woman = QuickSort(woman);
		
		for (int k = 0; k < N; k++) {
				answer[i] += abs(man[k] - woman[k]);
		}
	}

	for (int i = 0; i < T; i++)
		cout << answer[i] << endl;

	return 0;
}

vector<int> QuickSort(vector<int> list) {
	if (list.size() <= 1)
		return list;

	vector<int> prev;
	vector<int> next;

	for (int i = 1; i < list.size(); i++) {
		if (list[0] < list[i])
			next.push_back(list[i]);
		else
			prev.push_back(list[i]);
	}

	prev = QuickSort(prev);
	prev.push_back(list[0]);
	next = QuickSort(next);
	prev.insert(prev.end(), next.begin(), next.end());

	return prev;
}
