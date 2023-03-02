#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string S, T;

bool solve()
{
    int length = T.length();
    for (int idx = length - 1; idx >= S.size(); idx--)
    {
        char last = T[idx];
        T = T.substr(0, T.length() - 1);
        if (last == 'B')
        {
            reverse(T.begin(), T.end());
        }
    }
    
    return S == T;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> S >> T;

    if (solve())
        cout << "1\n";
    else
        cout << "0\n";

    return 0;
}
