#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Node
{
    string word;
    int word_bit, cost;
} typedef node;

const int MAX = 54321;

int N;
string sentence;
vector<string> words;
map<int, vector<string>> words_bit;
int cache[55];

int compare(const string &sub_sentence, const vector<string> &word_list)
{
    int ret = MAX;
    for (string word : word_list)
    {
        if (sub_sentence.size() == word.size())
        {
            int cost = 0;
            vector<int> sentence_alphabet(26, 0);
            vector<int> word_alphabet(26, 0);
            for (int idx = 0; idx < sub_sentence.size(); idx++)
            {
                char left_ch = sub_sentence[idx];
                char right_ch = word[idx];

                sentence_alphabet[left_ch - 'a'] += 1;
                word_alphabet[right_ch - 'a'] += 1;

                if (left_ch != right_ch)
                {
                    cost += 1;
                }
            }

            /**
             *  비트 마스킹으로 표기한 정수 값이 같으면서 동시에 문자열의 길이가 같은 경우에도
             *  서로 다른 문자열인 경우가 존재함
             *  ex) aabcd vs abbcd
             *  이런 경우에 비트 마스킹과 문자열의 길이가 같지만, 서로 바꿀 수 없는 문자열임
             *  이러한 반례를 처리하기 위해 알파벳 개수를 비교하는 코드를 추가함
             */
            bool flag = true;
            for (int idx = 0; idx < 26; idx++)
            {
                if (sentence_alphabet[idx] != word_alphabet[idx])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                ret = min(ret, cost);
            }
        }
    }
    return ret;
}

int solve(int start)
{
    if (start >= sentence.size())
    {
        return 0;
    }

    int &ret = cache[start];
    if (ret != -1)
    {
        return ret;
    }
    ret = MAX;

    string sub_sentence = "";
    int sub_sentence_bit = 0;
    for (int idx = start; idx < sentence.size(); idx++)
    {
        char ch = sentence[idx];
        sub_sentence += ch;

        int lsh = ch - 'a';
        sub_sentence_bit |= (1 << lsh);

        auto it = words_bit.find(sub_sentence_bit);
        if (it != words_bit.end())
        {
            int cost = compare(sub_sentence, it->second);
            ret = min(ret, cost + solve(idx + 1));
        }
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&cache[0], &cache[55], -1);

    cin >> sentence >> N;
    words = vector<string>(N);

    vector<bool> sentence_alphabet(26, false);
    for (char ch : sentence)
    {
        int idx = ch - 'a';
        sentence_alphabet[idx] = true;
    }

    vector<bool> words_alphabet(26, false);
    for (int idx = 0; idx < N; idx++)
    {
        cin >> words[idx];

        int word_bit = 0;
        for (char ch : words[idx])
        {
            int idx = ch - 'a';
            words_alphabet[idx] = true;

            word_bit |= (1 << idx);
        }

        vector<string> vec(1, words[idx]);
        auto it = words_bit.insert({word_bit, vec});
        if (!it.second)
        {
            it.first->second.push_back(words[idx]);
        }
    }

    for (int idx = 0; idx < 26; idx++)
    {
        if (sentence_alphabet[idx] && !words_alphabet[idx])
        {
            printf("-1\n");
            return 0;
        }
    }

    int answer = solve(0);
    if (answer >= MAX)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n", answer);
    }

    return 0;
}

/*
반례 모음

asdf
2
asdf
adsf

answer: 0


aa
1
aaa

answer: - 1


aabcd
1
abbcd

answer: -1

*/
