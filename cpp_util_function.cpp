#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return answer;
}

// priority_queue with Custom Struct
struct Tree
{
    int row, col, age;
};

struct CompareTree
{
    /**
     * Priority Queue에 대하여, Tree 구조체의 age를 기준으로 오름차순 정렬하기 위해 사용함
     * PQ의 디폴트는 내림차순 정렬임
     */
    bool operator()(Tree &left, Tree &right)
    {
        return left.age > right.age;
    }
};

// priority_queue 선언 방법
priority_queue<Tree, vector<Tree>, CompareTree> pq;
