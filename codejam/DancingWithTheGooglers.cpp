#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
	int T;
	cin >> T;
	
	for (int i = 1; i <= T; i++)
	{
		int N, S, p;
		cin >> N >> S >> p;

		vector<int> t(N, 0);
		for (int j = 0; j < N; j++)
			cin >> t[j];

		sort(begin(t), end(t), greater<int>());

		int R = 0;
		for (const auto& score : t)
		{
			if (score >= 3*p - 2)
			{
				R++;
			}
			else if (S > 0 && score >= 3 * p - 4 && score >= p)
			{
				R++;
				S--;
			}
			else
			{
				break;
			}
		}

		cout << "Case #" << i << ": " << R << endl;
	}

	return 0;
}