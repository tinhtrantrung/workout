#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main()
{
    int L, D, N;
    string line;
    vector<string> words;

    cin >> L >> D >> N;
    getline(cin, line);

    for (int i = 0; i < D; ++i)
    {
        getline(cin, line);
        words.push_back(line);
    }

    for (int i = 1; i <= N; ++i)
    {
        int K = 0;
        vector<set<char>> segments(L);

        getline(cin, line);
        int idx = 0;
        bool in_parenthesis = false;
        for (auto character : line)
        {
            if (character == '(')
                in_parenthesis = true;

            if (character == ')')
            {
                in_parenthesis = false;
                ++idx;
            }

            if (character != '(' && character != ')')
            {
                segments[idx].insert(character);
                if (!in_parenthesis)
                    idx++;
            }
        }

        for (auto word : words)
        {
            bool match = true;
            for (int j = 0; j < L; ++j)
            {
                if (segments[j].find(word[j]) == segments[j].end())
                {
                    match = false;
                    break;
                }
            }

            if (match) K++;
        }

        cout << "Case #" << i << ": " << K << endl;
    }
    return 0;
}