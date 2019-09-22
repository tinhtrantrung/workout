#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	int T = 10;
	cin >> T;

	for (int i = 1; i <= T; i++)
	{
		int H, W;
		cin >> H >> W;

		vector<vector<int>> Map(102, vector<int>(102, 10001));
		vector<vector<char>> Label(102, vector<char>(102, 0));
		char current_label = 'a';

		for (int r = 1; r <= H; r++)
			for (int c = 1; c <= W; c++)
				cin >> Map[r][c];

		for (int r = 1; r <= H; r++)
			for (int c = 1; c <= W; c++)
			{
				if (Label[r][c] != 0)
					continue;

				//Flow from here.
				char label = 0;
				list<int> flow;
				int r1 = r;
				int c1 = c;
				while (true)
				{
					int val = Map[r1 - 1][c1];
					char lbl = Label[r1 - 1][c1];
					int direction = 0;
					
					if (val > Map[r1][c1 - 1])
					{
						val = Map[r1][c1 - 1];
						lbl = Label[r1][c1 - 1];
						direction = 1;
					}

					if (val > Map[r1][c1 + 1])
					{
						val = Map[r1][c1 + 1];
						lbl = Label[r1][c1 + 1];
						direction = 2;
					}

					if (val > Map[r1 + 1][c1])
					{
						val = Map[r1 + 1][c1];
						lbl = Label[r1 + 1][c1];
						direction = 3;
					}

					if (val >= Map[r1][c1])
					{
						// Label and break;
						label = current_label++;
						break;
					}

					if (lbl != 0)
					{
						// Label and break;
						label = lbl;
						break;
					}

					switch (direction)
					{
					case 0:
						r1--;
						break;
					case 1:
						c1--;
						break;
					case 2:
						c1++;
						break;
					case 3:
						r1++;
						break;
					}

					flow.push_back(direction);
				}

				Label[r][c] = label;
				r1 = r;
				c1 = c;
				for (auto d : flow)
				{
					switch (d)
					{
					case 0:
						r1--;
						break;
					case 1:
						c1--;
						break;
					case 2:
						c1++;
						break;
					case 3:
						r1++;
						break;
					}
					Label[r1][c1] = label;
				}
			}

		cout << "Case #" << i << ":" << endl;
		for (int r = 1; r <= H; r++)
		{
			for (int c = 1; c <= W; c++)
			{
				cout << Label[r][c] << " ";
			}
			cout << endl;
		}
	}

	return 0;
}