#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

using namespace std;

int main()
{
	int T = 0;
	cin >> T;

	for (int i = 1; i <= T; ++i)
	{
		int N = 0;
		cin >> N;

		if (N == 0)
		{
			cout << "Case #" << i << ": INSOMNIA" << endl;
			continue;
		}

		set<int> digits;
		int S = N;
		while (true)
		{
			int M = S;
			while (M > 0)
			{
				digits.insert(M % 10);
				M = M / 10;
			}

			if (digits.size() == 10)
				break;

			S += N;
		}


		cout << "Case #" << i << ": " << S << endl;
	}

	return 0;
}