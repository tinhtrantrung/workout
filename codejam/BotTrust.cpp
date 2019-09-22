#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

using namespace std;

struct button
{
	int p;
	int order;
};

int main()
{
	int T, N;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		cin >> N;

		button o_target[100], b_target[100];
		int o_count = 0, b_count = 0, p;
		string c;
		for (int j = 0; j < N; ++j)
		{
			cin >> c >> p;
			if (c == "O")
			{
				o_target[o_count].p = p;
				o_target[o_count].order = j;
				o_count++;
			}
			else
			{
				b_target[b_count].p = p;
				b_target[b_count].order = j;
				b_count++;
			}
		}

		int k = 0, l = 0;
		int o_pos = 1, b_pos = 1;
		int count = 0;
		while (k < o_count && l < b_count)
		{
			if (o_target[k].order < b_target[l].order)
			{
				if (o_pos < o_target[k].p) {
					o_pos++;
				} else if (o_pos > o_target[k].p) {
					o_pos--;
				} else {
					k++;
				}

				if (b_pos < b_target[l].p) {
					b_pos++;
				}
				else if (b_pos > b_target[l].p) {
					b_pos--;
				}
			}
			else
			{
				if (b_pos < b_target[l].p) {
					b_pos++;
				}
				else if (b_pos > b_target[l].p) {
					b_pos--;
				}
				else {
					l++;
				}

				if (o_pos < o_target[k].p) {
					o_pos++;
				}
				else if (o_pos > o_target[k].p) {
					o_pos--;
				}
			}

			count++;
		}

		while (k < o_count)
		{
			if (o_pos < o_target[k].p) {
				o_pos++;
			}
			else if (o_pos > o_target[k].p) {
				o_pos--;
			}
			else {
				k++;
			}

			count++;
		}
		
		while (l < b_count)
		{
			if (b_pos < b_target[l].p) {
				b_pos++;
			}
			else if (b_pos > b_target[l].p) {
				b_pos--;
			}
			else {
				l++;
			}

			count++;
		}


		cout << "Case #" << i << ": " << count << endl;
	}

	return 0;
}