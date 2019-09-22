#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

using namespace std;

bool Flip(string& S, size_t from, size_t to)
{
	if (to > S.length())
		return false;

	for (auto i = from; i < to; ++i)
	{
		if (S[i] == '-')
			S[i] = '+';
		else
			S[i] = '-';
	}

	return true;
}

int main()
{
	int T = 0;
	cin >> T;

	for (int i = 1; i <= T; ++i)
	{
		string S = "";
		int K = 0;
		cin >> S >> K;

		int R = 0;
		bool done = true;
		size_t j = S.find('-');;
		for (; j != string::npos; j = S.find('-'))
		{
			if (!Flip(S, j, j + K))
			{
				done = false;
				break;
			}
			R++;
		}

		if (done)
			cout << "Case #" << i << ": " << R << endl;
		else
			cout << "Case #" << i << ": IMPOSSIBLE" << endl;
	}

	return 0;
}