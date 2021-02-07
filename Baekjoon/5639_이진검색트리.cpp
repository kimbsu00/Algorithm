/*
  url: https://www.acmicpc.net/problem/5639
  
  지금껏 풀었던 알고리즘 문제들은 input 의 종료지점을 -1 과 같은 특정한 값으로 알려주거나,
  맨 처음에 주어지는 input 의 개수를 알려주는 형식으로 되어 있었는데,
  이 문제는 input 으로 들어오는 데이터의 개수가 몇 개 인지도, input 의 종료지점을 알려주지도 않아서 어떻게 input 을 받아야 하나 고민했던 문제이다.
  
  막연히 고민만 하다가 좋은 방법이 떠오르지 않아서 구글링 해본 결과,
  cin 함수의 리턴 값을 이용해서 input 을 입력 받으면 됨을 알게 되었다.
  [27, 30] 줄을 기억해두자.
*/

#include<iostream>
#include<vector>

using namespace std;

void postorder(vector<int>& preorder);
void postorder(const int& left, const int& right);

vector<int> preorder;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int num;
	while (cin >> num) {
		preorder.push_back(num);
	}

	postorder(0, preorder.size());

	return 0;
}

// [left, right) 범위에 해당하는 노드들을 postorder 순서로 출력하는 함수
void postorder(const int& left, const int& right) {
	if (left == right)			return;

	if (left + 1 == right) {
		cout << preorder[left] << "\n";
		return;
	}

	int index = right;
	for (int i = left + 1; i < right; i++) {
		if (preorder[left] < preorder[i]) {
			index = i;
			break;
		}
	}
	
	postorder(left + 1, index);
	postorder(index, right);
	

	cout << preorder[left] << "\n";
}

// vector 를 매개변수로 넘기면 메모리 초과가 발생한다.
void postorder(vector<int>& preorder) {
	if (preorder.empty())		return;

	if (preorder.size() == 1) {
		cout << preorder[0] << "\n";
		return;
	}

	vector<int> prev;
	vector<int> next;
	for (int i = 1; i < preorder.size(); i++) {
		if (preorder[0] < preorder[i]) {
			next.push_back(preorder[i]);
		}
		else {
			prev.push_back(preorder[i]);
		}
	}

	postorder(prev);
	postorder(next);
	cout << preorder[0] << "\n";
}
