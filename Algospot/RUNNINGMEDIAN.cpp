/*
  url: https://algospot.com/judge/problem/read/RUNNINGMEDIAN
*/

/* 
	A[i] 에 대응되는 노드의 왼쪽 자손은 A[2*i +1]
	A[i] 에 대응되는 노드의 오른쪽 자손은 A[2*i +2]
	A[i] 에 대응되는 노드의 부모는 A[(i-1)/2]	(나눗셈의 결과는 내림함)
*/

#include<iostream>
#include<vector>
#include<queue>

#define MOD 20090711

using namespace std;

int solve();
int RUNNINGMEDIAN();
void precal(int N, int a, int b);
void push_heap(vector<int>& heap, int input);
int pop_heap(vector<int>& heap);

vector<int> sequence;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		int N, a, b;
		cin >> N >> a >> b;

		precal(N, a, b);
		//answer[i] = solve();
		answer[i] = RUNNINGMEDIAN();
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

// using STL
int solve() {
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int ret = 0;

	for (int i = 0; i < sequence.size(); i++) {
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(sequence[i]);
		else
			minHeap.push(sequence[i]);

		if (!maxHeap.empty() && !minHeap.empty() && (maxHeap.top() > minHeap.top())) {
			int max = maxHeap.top();
			int min = minHeap.top();
			maxHeap.pop();
			minHeap.pop();
			maxHeap.push(min);
			minHeap.push(max);
		}

		ret = (ret + maxHeap.top()) % MOD;
	}

	return ret;
}

// not using STL
int RUNNINGMEDIAN() {
	int ret = 0;

	vector<int> front_half;
	vector<int> back_half;
	for (int i = 0; i < sequence.size(); i++) {
		if (front_half.size() == back_half.size())
			push_heap(front_half, sequence[i]);
		else 
			push_heap(back_half, -sequence[i]);

		if (!front_half.empty() && !back_half.empty() && (front_half[0] > -back_half[0])) {
			int num1 = pop_heap(front_half);;
			int num2 = -pop_heap(back_half);
			push_heap(front_half, num2);
			push_heap(back_half, -num1);
		}

		ret += front_half[0];
		ret %= MOD;
	}

	return ret;
}

void precal(int N, int a, int b) {
	sequence.clear();
	sequence.push_back(1983);
	for (int i = 1; i < N; i++) {
		sequence.push_back((sequence[i - 1] * (long long)a + b) % MOD);
	}
}

/* 
	새로운 값을 맨 뒤에 삽입하고, 
	삽입한 위치의 부모 노드와 대소 비교를 한 후에, 
	부모보다 크면 부모와 위치를 바꾸면 된다.
	이를 부모보다 작을 때까지 반복하면 됨.
*/
void push_heap(vector<int>& heap, int input) {
	heap.push_back(input);

	int index = heap.size() - 1;
	while (index > 0 && heap[index] > heap[(index - 1) / 2]) {
		swap(heap[index], heap[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}

int pop_heap(vector<int>& heap) {
	int ret = heap[0];
	heap[0] = heap[heap.size() - 1];
	heap.pop_back();

	int here = 0;
	while (true) {
		// 자식 노드들의 인덱스를 계산
		int left = here * 2 + 1;
		int right = here * 2 + 2;

		// 자식 노드가 존재하지 않는 경우 
		if (left >= heap.size())		break;
		
		int next = here;
		// 왼쪽 자식 노드가 부모 노드보다 값이 더 큰 경우 -> 왼쪽 자식 노드로 바꾼다.
		if (heap[next] < heap[left])
			next = left;
		// 왼쪽 자식 노드가 오른쪽 자식 노드보다 작은 경우 -> 오른쪽 자식 노드로 바꾼다.
		if (right < heap.size() && heap[next] < heap[right])
			next = right;
		// 부모 노드가 자식 노드보다 값이 더 큰 경우
		if (next == here)		break;

		swap(heap[here], heap[next]);
		here = next;
	}

	return ret;
}
