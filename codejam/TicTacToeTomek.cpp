#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

using namespace std;

int main()
{
	string line;
	getline(cin, line);
	
	int T = stoi(line);

	for (int i = 1; i <= T; ++i)
	{
		bool completed = true;
		int board[16] = { 0 };
		int score[10] = { 0 };
		
		for (int j = 0; j < 4; ++j)
		{
			getline(cin, line);
			for (int k = 0; k < 4; ++k)
			{
				switch (line[k])
				{
				case 'X':
					board[j * 4 + k] = 1;
					break;
				case 'O':
					board[j * 4 + k] = -1;
					break;
				case 'T':
					board[j * 4 + k] = 10;
					break;
				case '.':
					completed = false;
					board[j * 4 + k] = 0;
					break;
				default:
					break;
				}
			}
		}

		score[0] = board[0] + board[1] + board[2] + board[3];//row 0
		score[1] = board[4] + board[5] + board[6] + board[7];//row 1
		score[2] = board[8] + board[9] + board[10] + board[11];//row 2
		score[3] = board[12] + board[13] + board[14] + board[15];//row 3

		score[4] = board[0] + board[4] + board[8] + board[12];//column 0
		score[5] = board[1] + board[5] + board[9] + board[13];//column 1
		score[6] = board[2] + board[6] + board[10] + board[14];//column 2
		score[7] = board[3] + board[7] + board[11] + board[15];//column 3

		score[8] = board[0] + board[5] + board[10] + board[15];//diagonal 0
		score[9] = board[3] + board[6] + board[9] + board[12];//diagonal 1

		string result = completed ? "Draw" : "Game has not completed";

		for (int j = 0; j < 10; j++)
		{
			if (score[j] == 4 || score[j] == 13)
			{
				result = "X won";
				break;
			}
			else if (score[j] == -4 || score[j] == 7)
			{
				result = "O won";
				break;
			}
		}

		cout << "Case #" << i << ": " << result << endl;
		getline(cin, line);
	}
	
	return 0;
}