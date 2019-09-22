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
		int S[1001] = { 0 };
		int Smax = 0;
		string Sdata = "";
		cin >> Smax >> Sdata;

		int R = 0;
		S[0] = Sdata[0] - '0';
		for (int j = 1; j < Sdata.length(); ++j)
		{
			if (S[j - 1] >= j)
			{
				S[j] = S[j - 1] + (Sdata[j] - '0');
			}
			else
			{
				int more = j - S[j - 1];
				R += more;
				S[j] = S[j - 1] + (Sdata[j] - '0') + more;
			}
		}
		
		cout << "Case #" << i << ": " << R << endl;
	}

	return 0;
}