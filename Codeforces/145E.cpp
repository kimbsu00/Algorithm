/*
  url: https://codeforces.com/problemset/problem/145/E
*/

#include<cstdio>
#include<algorithm>

using namespace std;

class Node {
public:
	// 현재 노드가 위치해 있는 배열상의 인덱스를 의미
	int index;
	// 현재 노드를 루트로 하는 서브트리에 포함되는 인덱스 범위를 의미 [left, right]
	int left, right;
	// [left, right] 범위가 switch 되었는지 여부
	bool isSwitch;
	// 현재 노드를 루트로 하는 서브트리에 포함되는 4의 개수와 7의 개수
	int fourNum, sevenNum;
	// 44..77 형태의 sequence 길이, 77..44 형태의 sequence 길이
	int fourToSeven, sevenToFour;
};

int* makeIndexTree(int index, int left, int right);
int* doSwitch(int index, int left, int right);
void doUpdate(int index, int lc, int rc, int left, int right);
void checkSwitch(int index, int lc, int rc);

int N, M;
char input[1000001];
Node tree[2100000];

int main(void) {	
	scanf("%d %d", &N, &M);
	scanf("%s", &input);

	makeIndexTree(1, 1, N);

	char s[7];
	for (int i = 0; i < M; i++) {
		scanf("%s", &s);
		if (!strcmp(s, "count")) {
			//int ret = tree[1].isSwitch ? tree[1].sevenToFour : tree[1].fourToSeven;
			int ret = tree[1].fourToSeven;
			printf("%d\n", ret);
		}
		else {
			int left, right;
			scanf("%d %d", &left, &right);
			//doSwitch(1, left, right);
			doUpdate(1, 1, N, left, right);
		}
	}

	return 0;
}

int* makeIndexTree(int index, int left, int right) {
	// 현재 노드의 변수 초기화
	tree[index].index = index;
	tree[index].left = left;
	tree[index].right = right;
	tree[index].isSwitch = false;

	int* ret = new int[4];

	// left 와 right 가 같은 경우 -> 현재 노드가 leaf 인 경우가 된다.
	if (left == right) {
		if (input[left-1] == 52) {
			ret[0] = tree[index].fourNum = 1;
			ret[1] = tree[index].sevenNum = 0;
		}
		else {
			ret[0] = tree[index].fourNum = 0;
			ret[1] = tree[index].sevenNum = 1;
		}
		ret[2] = tree[index].fourToSeven = 1;
		ret[3] = tree[index].sevenToFour = 1;
		return ret;
	}

	int mid = (left + right) / 2;
	int* leftRet = makeIndexTree(index * 2, left, mid);
	int* rightRet = makeIndexTree(index * 2 + 1, mid + 1, right);

	ret[0] = tree[index].fourNum = leftRet[0] + rightRet[0];
	ret[1] = tree[index].sevenNum = leftRet[1] + rightRet[1];
	ret[2] = tree[index].fourToSeven = max(max(leftRet[0] + rightRet[1], leftRet[0] + rightRet[2]), leftRet[2] + rightRet[1]);
	ret[3] = tree[index].sevenToFour = max(max(leftRet[1] + rightRet[0], leftRet[1] + rightRet[3]), leftRet[3] + rightRet[0]);

	delete leftRet;
	delete rightRet;

	return ret;
}

int* doSwitch(int index, int left, int right) {
	int* ret = new int[4];
	if (tree[index].left >= left && tree[index].right <= right) {
		tree[index].isSwitch = !tree[index].isSwitch;
		if (tree[index].isSwitch){
			ret[0] = tree[index].sevenNum;
			ret[1] = tree[index].fourNum;
			ret[2] = tree[index].sevenToFour;
			ret[3] = tree[index].fourToSeven;
		}
		else {
			ret[0] = tree[index].fourNum;
			ret[1] = tree[index].sevenNum;
			ret[2] = tree[index].fourToSeven;
			ret[3] = tree[index].sevenToFour;
		}
		return ret;
	}

	if (left > tree[index].right || right < tree[index].left) {
		if (tree[index].isSwitch) {
			ret[0] = tree[index].sevenNum;
			ret[1] = tree[index].fourNum;
			ret[2] = tree[index].sevenToFour;
			ret[3] = tree[index].fourToSeven;
		}
		else {
			ret[0] = tree[index].fourNum;
			ret[1] = tree[index].sevenNum;
			ret[2] = tree[index].fourToSeven;
			ret[3] = tree[index].sevenToFour;
		}
		return ret;
	}

	int* leftRet = doSwitch(index * 2, left, right);
	int* rightRet = doSwitch(index * 2 + 1, left, right);

	if (tree[index].isSwitch) {
		ret[1] = tree[index].fourNum = leftRet[0] + rightRet[0];
		ret[0] = tree[index].sevenNum = leftRet[1] + rightRet[1];
		ret[3] = tree[index].fourToSeven = max(max(leftRet[0] + rightRet[1], leftRet[0] + rightRet[2]), leftRet[2] + rightRet[1]);
		ret[2] = tree[index].sevenToFour = max(max(leftRet[1] + rightRet[0], leftRet[1] + rightRet[3]), leftRet[3] + rightRet[0]);
	}
	else {
		ret[0] = tree[index].fourNum = leftRet[0] + rightRet[0];
		ret[1] = tree[index].sevenNum = leftRet[1] + rightRet[1];
		ret[2] = tree[index].fourToSeven = max(max(leftRet[0] + rightRet[1], leftRet[0] + rightRet[2]), leftRet[2] + rightRet[1]);
		ret[3] = tree[index].sevenToFour = max(max(leftRet[1] + rightRet[0], leftRet[1] + rightRet[3]), leftRet[3] + rightRet[0]);
	}

	delete leftRet;
	delete rightRet;

	return ret;
}
