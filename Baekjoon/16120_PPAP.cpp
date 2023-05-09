#include <iostream>
#include <string>

using namespace std;

string solve(string input)
{
    if (input == "P")
    {
        return "PPAP";
    }
    else if (input.size() < 4)
    {
        return "NP";
    }

    string ppap = "";
    for (int idx = 0; idx < input.size(); idx++)
    {
        ppap += input[idx];

        if (ppap.length() >= 4)
        {
            string tmp = ppap.substr(ppap.length() - 4, 4);
            if (tmp == "PPAP")
            {
                ppap = ppap.replace(ppap.length() - 4, 4, "P");
            }
        }
    }

    if (ppap == "P" || ppap == "PPAP")
    {
        return "PPAP";
    }
    else
    {
        return "NP";
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string input;
    cin >> input;

    cout << solve(input) << "\n";

    return 0;
}
