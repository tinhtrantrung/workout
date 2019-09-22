#include <iostream>
#include <iomanip>
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
	
	double Cz = 2.0f;
	for (int i = 1; i <= T; i++)
	{
		double C, F, X;
		cin >> C >> F >> X;

		double Cz = 2.0;
		double Y = X / Cz;
		double j = 1 / Cz;

		Cz += F;
		double k = 1 / Cz;
		while (true)
		{
			double S = C * j + X * k;
			if (S > Y)
			{
				break;
			}
			else
			{
				j += k;
				Cz += F;
				k = 1 / Cz;
				Y = S;
			}
		}

		cout << fixed << setprecision(7) << "Case #" << i << ": " << Y << endl;
	}

	return 0;
}