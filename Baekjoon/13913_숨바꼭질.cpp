#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>

using namespace std;

int N, K;
bool visited[100005];

vector<string> split(string input, char delimiter)
{
    vector<string> answer;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter))
    {
        answer.push_back(temp);
    }

    return answer;
}

string solve()
{
    string ret = "";
    if (N > K)
    {
        ret = to_string(N);
        for (int idx = N - 1; idx >= K; idx--)
        {
            ret = ret.append(" " + to_string(idx));
        }
    }
    else
    {
        queue<pair<int, string>> q;
        q.push({N, to_string(N)});

        while (true)
        {
            pair<int, string> front = q.front();
            q.pop();

            int pos = front.first;
            string path = front.second;

            if (pos == K)
            {
                ret = path;
                break;
            }

            if (pos <= 50000 && !visited[pos * 2])
            {
                string new_path = path + " " + to_string(pos * 2);

                visited[pos * 2] = true;
                q.push({pos * 2, new_path});
            }
            if (pos < 100000 && !visited[pos + 1])
            {
                string new_path = path + " " + to_string(pos + 1);

                visited[pos + 1] = true;
                q.push({pos + 1, new_path});
            }
            if (pos > 0 && !visited[pos - 1])
            {
                string new_path = path + " " + to_string(pos - 1);

                visited[pos - 1] = true;
                q.push({pos - 1, new_path});
            }
        }
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&visited[0], &visited[100005], false);
    cin >> N >> K;

    string path = solve();
    vector<string> path_vec = split(path, ' ');

    cout << path_vec.size() - 1 << "\n";
    for (string p : path_vec)
    {
        cout << p << " ";
    }
    cout << "\n";

    return 0;
}
