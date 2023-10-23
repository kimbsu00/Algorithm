#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

enum Type
{
    START,
    END
};

class Time
{
public:
    Type type;
    int time;

    Time() : type(Type::START), time(-1) {}

    Time(Type p_type, int p_time) : type(p_type), time(p_time) {}

    bool operator<(const Time &other) const
    {
        return this->time >= other.time;
    }
};

int N;
priority_queue<Time> input;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    int S, T;
    for (int idx = 0; idx < N; idx++)
    {
        cin >> S >> T;
        input.push(Time(Type::START, S));
        input.push(Time(Type::END, T));
    }

    int cur_time = 0;
    int classroom = 0, answer = 0;
    while (!input.empty())
    {
        Time top = input.top();

        if (cur_time < top.time)
        {
            cur_time = top.time;
        }

        do
        {
            input.pop();
            if (top.type == Type::START)
            {
                classroom += 1;
            }
            else if (top.type == Type::END)
            {
                classroom -= 1;
            }
            top = input.top();
        } while (!input.empty() && top.time == cur_time);

        answer = max(answer, classroom);
    }

    cout << answer << "\n";

    return 0;
}
