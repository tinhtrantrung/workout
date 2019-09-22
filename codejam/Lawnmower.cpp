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
		int N, M;
		cin >> N >> M;

		vector<vector<int>> Lawn(N, vector<int>(M, 0));
		vector<int> MaxRow(N, 0), MaxCol(M, 0);
		for (int j = 0; j < N; j++)
			for (int k = 0; k < M; k++)
			{
				cin >> Lawn[j][k];
				if (Lawn[j][k] > MaxRow[j])
					MaxRow[j] = Lawn[j][k];

				if (Lawn[j][k] > MaxCol[k])
					MaxCol[k] = Lawn[j][k];
			}

		bool Possible = true;
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
				if (Lawn[j][k] != MaxRow[j] && Lawn[j][k] != MaxCol[k])
				{
					Possible = false;
					break;
				}

			if (!Possible)
				break;
		}

		if (Possible)
			cout << "Case #" << i << ": YES" << endl;
		else
			cout << "Case #" << i << ": NO" << endl;
	}

	return 0;
}