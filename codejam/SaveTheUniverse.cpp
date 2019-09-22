#include <iostream>
#include <string>
#include <set>

using namespace std;

int main()
{
    int N, S, Q, count;
    string line;
    set<string> segments;

    getline(cin, line);
    N = stoi(line);

    for (int i = 1; i <= N; ++i)
    {
        getline(cin, line);
        S = stoi(line);

        for (int j = 0; j < S; ++j) getline(cin, line);

        getline(cin, line);
        Q = stoi(line);

        segments.clear();
        count = 0;
        for (int j = 0; j < Q; ++j)
        {
            getline(cin, line);
            if (segments.find(line) == segments.end())
            {
                if (segments.size() == S - 1)
                {
                    ++count;
                    segments.clear();
                }
                
                segments.insert(line);
            }
        }

        cout << "Case #" << i << ": " << count << endl;
    }

    return 0;
}