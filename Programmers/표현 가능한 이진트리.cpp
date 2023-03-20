#include <string>
#include <vector>

using namespace std;

string to_binary(long long number)
{
    string ret = "";
    while (number > 0)
    {
        int mod = number % 2;
        ret = to_string(mod) + ret;
        number /= 2;
    }
    return ret;
}

string to_full_binary(string binary)
{
    long long tmp = 1;
    long long length = 0;
    while (length < binary.length())
    {
        tmp = tmp << 1;
        length = tmp - 1;
    }

    long long diff = length - binary.length();
    string ret = binary;
    while (diff--)
    {
        ret = "0" + ret;
    }

    return ret;
}

bool solve(string &binary, int left, int right)
{
    if (left >= right)
        return true;

    int mid = (left + right) / 2;
    if (binary[mid] == '0')
    {
        bool ret = true;
        for (int idx = left; idx <= right; idx++)
        {
            if (binary[idx] != '0')
            {
                ret = false;
                break;
            }
        }
        return ret;
    }

    return solve(binary, left, mid - 1) && solve(binary, mid + 1, right);
}

bool solve(long long number)
{
    string binary = to_binary(number);
    string full_binary = to_full_binary(binary);
    return solve(full_binary, 0, full_binary.length() - 1);
}

vector<int> solution(vector<long long> numbers)
{
    vector<int> answer;

    for (int idx = 0; idx < numbers.size(); idx++)
    {
        bool ans = solve(numbers[idx]);
        answer.push_back((ans ? 1 : 0));
    }

    return answer;
}
