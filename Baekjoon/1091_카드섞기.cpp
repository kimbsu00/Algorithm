#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int N;
vector<int> P, S;

string to_string(vector<int> &vec)
{
    string ret = "";
    for (int num : vec)
    {
        ret += to_string(num);
    }
    return ret;
}

void shuffle_card(vector<int> &card)
{
    vector<int> origin;
    origin.insert(origin.begin(), card.begin(), card.end());

    for (int idx = 0; idx < N; idx++)
    {
        int new_idx = S[idx];
        card[new_idx] = origin[idx];
    }
}

bool is_okay(vector<int> &card)
{
    bool ret = true;
    for (int idx = 0; idx < N; idx++)
    {
        if (card[idx] != (idx % 3))
        {
            ret = false;
            break;
        }
    }
    return ret;
}

int solve()
{
    int ret = 0;
    set<string> s;

    while (true)
    {
        if (!is_okay(P))
        {
            shuffle_card(P);
            
            string card_str = to_string(P);
            auto pair = s.insert(card_str);
            if (!pair.second)
            {
                return -1;
            }

            ret += 1;
        }
        else
        {
            break;
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    P = vector<int>(N);
    S = vector<int>(N);

    for (int idx = 0; idx < N; idx++)
    {
        cin >> P[idx];
    }

    for (int idx = 0; idx < N; idx++)
    {
        cin >> S[idx];
    }

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
