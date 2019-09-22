#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

using namespace std;

int main()
{
	int T;
	cin >> T;

	for (int i = 1; i <= T; ++i)
	{
		int first_answer;
		cin >> first_answer;

		int card;
		int begin = (first_answer - 1) * 4;
		int end = begin + 4;

		set<int> first_set;
		for (int j = 0; j < 16; j++)
		{
			cin >> card;
			if (j >= begin && j < end)
				first_set.insert(card);
		}

		int second_answer;
		cin >> second_answer;

		begin = (second_answer - 1) * 4;
		end = begin + 4;
		
		int count = 0;
		int result = 0;
		for (int j = 0; j < 16; j++)
		{
			cin >> card;
			if (j >= begin && j < end && first_set.find(card) != first_set.end())
			{
				result = card;
				count++;
			}
				
		}

		switch (count)
		{
		case 0:
			cout << "Case #" << i << ": Volunteer cheated!" << endl;
			break;
		case 1:
			cout << "Case #" << i << ": " << result << endl;
			break;
		default:
			cout << "Case #" << i << ": Bad magician!" << endl;
			break;
		}
	}
	
	return 0;
}