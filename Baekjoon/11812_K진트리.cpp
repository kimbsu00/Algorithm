/*
  url: https://www.acmicpc.net/problem/11812
  
  17번째 줄에 K 를 int 형으로 선언하고 나머지 코드를 똑같이 해서 제출하면 오답처리가 된다.
 
  y = ((y - 2) / K) + 1; 
  x = ((x - 2) / K) + 1;
  
  아무래도 위의 두 코드를 연산할 때, x 와 y 는 long long 타입인데 K 는 int 형이어서 그런가 보다.
  근데 int 와 double 끼리 연산하면 double 로 바뀌는 것처럼
  long long 이 크기가 더 큰 형식이어서 int 가 long long 으로 강제 형변환이 일어나서 상관없을 줄 알았는데 그게 아닌가 보다.
*/

#include<iostream>
#include<vector>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

  long long N, K, Q;
	cin >> N >> K >> Q;

	for (int i = 0; i < Q; i++) {
        long long x, y;
		cin >> x >> y;

        long long distance = 0;
        if (K == 1) {
            distance = x < y ? y - x : x - y;
        }
        else {
            while (x != y) {
                if (x < y) {
                    y = ((y - 2) / K) + 1;
                }
                else {
                    x = ((x - 2) / K) + 1;
                }

                distance++;
            }
        }
        cout << distance << "\n";
	}

	return 0;
}
