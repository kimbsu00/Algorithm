/*
  url: https://www.acmicpc.net/problem/1781
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Data {
public:
	int deadline;
	int cup_noodle;

	Data()
		: deadline(-1), cup_noodle(-1)
	{
	}

	Data(int deadline, int cup_noodle)
		: deadline(deadline), cup_noodle(cup_noodle)
	{
	}

	bool operator < (const Data& other) const {
		if (this->deadline == other.deadline) {
			return this->cup_noodle > other.cup_noodle;
		}

		return this->deadline < other.deadline;
	}
};

int N;
vector<Data> datas;

int solve() {
	priority_queue<int> pq;

	sort(datas.begin(), datas.end());
	int time = 1;
	for (Data data : datas) {
		if (data.deadline >= time) {
			pq.push(-data.cup_noodle);
			time += 1;
		}
		else if (-pq.top() < data.cup_noodle) {
			pq.pop();
			pq.push(-data.cup_noodle);
		}
	}

	int ret = 0;
	while (!pq.empty()) {
		ret -= pq.top();
		pq.pop();
	}
	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int deadline, cup_noodle;
		cin >> deadline >> cup_noodle;
		datas.push_back(Data(deadline, cup_noodle));
	}

	int answer = solve();
	cout << answer << "\n";

	return 0;
}
