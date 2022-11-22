/*
  url: https://www.acmicpc.net/problem/1700
*/

#include <iostream>
#include <map>
#include <queue>

using namespace std;

int N, K;

class Node
{
public:
    int value;
    int refer_cnt;

    Node() : value(-1), refer_cnt(1) {}

    Node(int p_value) : value(p_value), refer_cnt(1) {}

    bool operator<(const Node &other) const
    {
        return this->refer_cnt > other.refer_cnt;
    }

    bool operator==(const Node &other) const
    {
        return this->value == other.value;
    }
};

// LRU Algorithm
void LRU()
{
    // 가장 큰 값이 top이 되도록 정렬되어 저장됨
    priority_queue<Node *> pq;
    map<int, Node *> node_map;
    int input;
    int answer = 0;
    for (int idx = 0; idx < K; idx++)
    {
        cin >> input;

        auto it = node_map.find(input);
        // 새롭게 추가한 전기 용품인 경우
        if (it == node_map.end())
        {
            if (pq.size() == N)
            {
                Node *top_node = pq.top();
                pq.pop();
                node_map.erase(top_node->value);
                answer += 1;
            }

            Node *node = new Node(input);
            pair<map<int, Node *>::iterator, bool> ret = node_map.insert({input, node});
            pq.push(node);
        }
        // 이미 연결된 전기 용품인 경우
        else
        {
            it->second->refer_cnt += 1;
        }
    }

    cout << answer << "\n";
}

// Optimal Algorithm
void OPT()
{
    int list[100];
    for (int idx = 0; idx < K; idx++)
    {
        cin >> list[idx];
    }

    int cache[100];
    fill(&cache[0], &cache[100], -1);

    int answer = 0;
    for (int i = 0; i < K; i++)
    {
        int page = list[i];
        bool cache_hit = false;

        for (int j = 0; j < N; j++)
        {
            if (cache[j] == page)
            {
                cache_hit = true;
                break;
            }
        }

        // 페이지가 적재되어 있었다면 == 캐시 히트인 경우, 다음 페이지로 넘어감
        if (cache_hit)
            continue;

        bool page_loaded = false;
        for (int j = 0; j < N; j++)
        {
            if (cache[j] == -1)
            {
                cache[j] = page;
                page_loaded = true;
                break;
            }
        }

        // 캐시에 여유 공간이 있어서 페이지가 적재된 경우, 다음 페이지로 넘어감
        if (page_loaded)
            continue;

        int max_value = -1;
        int remove_idx = 0;     // 제거해야 하는 페이지가 적재되어 있는 캐시 인덱스
        for (int j = 0; j < N; j++)
        {
            int cnt = 0;
            for (int n = i + 1; n < K; n++, cnt++)
            {
                int tmp_page = list[n];
                if (tmp_page == cache[j])
                    break;
            }

            if (max_value < cnt)
            {
                max_value = cnt;
                remove_idx = j;
            }
        }

        // 가장 나중에 사용되는 페이지를 제거하고, 새로운 페이지를 캐시에 적재함
        cache[remove_idx] = page;
        answer += 1;
    }

    cout << answer << "\n";
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    OPT();

    return 0;
}
