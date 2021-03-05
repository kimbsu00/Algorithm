/*
  url: https://codeforces.com/problemset/problem/118/A
*/

#include<iostream>

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    char str[101];
    cin >> str;

    char output[201];
    int index = 0;
    for (int i = 0; i < 101; i++) {
        if (str[i] == '\0') {
            output[index++] = '\0';
            break;
        }

        if (str[i] >= 'A' && str[i] <= 'Z') {
            int diff = str[i] - 'A';
            str[i] = 'a' + diff;
            i--;
            continue;
        }

        switch (str[i]) {
        case 'a':
        case 'o':
        case 'y':
        case 'e':
        case 'u':
        case 'i':
            break;
        default:
            output[index++] = '.';
            output[index++] = str[i];
            break;
        }
    }

    cout << output << "\n";

    return 0;
}
