#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
	int T;
	cin >> T;
	
	set<char> BaseElement = { 'Q', 'W', 'E', 'R', 'A', 'S', 'D', 'F' };
	for (int i = 1; i <= T; i++)
	{
		string S;
		int C;
		cin >> C;

		map<pair<char, char>, char> CombineMap;
		for (int j = 1; j <= C; j++)
		{
			cin >> S;
			auto combine_pair1 = make_pair(S[0], S[1]);
			auto combine_pair2 = make_pair(S[1], S[0]);
			CombineMap[combine_pair1] = S[2];
			CombineMap[combine_pair2] = S[2];
		}

		int D;
		cin >> D;
		set<pair<char, char>> OpposedSet;
		for (int j = 1; j <= D; j++)
		{
			cin >> S;
			auto opposed_pair1 = make_pair(S[0], S[1]);
			auto opposed_pair2 = make_pair(S[1], S[0]);
			OpposedSet.insert(opposed_pair1);
			OpposedSet.insert(opposed_pair2);
		}

		int N;
		cin >> N >> S;

		list<char> R;
		for (auto& c : S)
		{
			if (R.empty())
			{
				R.push_front(c);
				continue;
			}

			auto combine_pair = make_pair(c, R.front());
			auto combine_it = CombineMap.find(combine_pair);
			if (combine_it != CombineMap.end())
			{
				R.pop_front();
				R.push_front(combine_it->second);
				continue;
			}

			bool need_clear = false;
			for (auto& r : R)
			{
				auto opposed_pair = make_pair(c, r);
				if (OpposedSet.find(opposed_pair) != OpposedSet.end())
				{
					need_clear = true;
					break;
				}
			}

			if (need_clear)
				R.clear();
			else
				R.push_front(c);
		}

		if (R.empty())
		{
			cout << "Case #" << i << ": []" << endl;
			continue;
		}

		cout << "Case #" << i << ": [";
		auto j = R.size() - 1;
		auto it = R.rbegin();
		for (; j > 0; j--, it++)
		{
			cout << *it << ", ";
		}

		if (j == 0)
			cout << *it;

		cout << "]" << endl;

	}

	return 0;
}