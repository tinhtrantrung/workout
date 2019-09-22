#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main()
{
	int T, N, K;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        cin >> N >> K;
		
		cout << "Case #" << i << ": " << ((K + 1) % (1 << N) == 0 ? "ON" : "OFF") << endl;
    }

    return 0;
}