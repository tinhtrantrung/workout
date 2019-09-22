#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <algorithm>

using namespace std;

struct TrainTime
{
	int		depart;
	int		arrive;
	bool	a2b;

	bool operator < (const TrainTime& rhs)
	{
		return depart < rhs.depart;
	}
};

int current_time = 0;

bool IsGood(int time) {
	return (time <= current_time);
}

int Time2Minute(const string& time)
{
	auto p = time.find(':');
	auto hour = time.substr(0, p);
	auto minute = time.substr(p + 1);

	return stoi(hour) * 60 + stoi(minute);
}

int main()
{
	int N = 0;
	cin >> N;

	for (int i = 1; i <= N; ++i)
	{
		int T, A, B;
		cin >> T >> A >> B;

		string depart, arrive;
		int total = A + B;
		vector<TrainTime> Timetable(total);
		for (int j = 0; j < A; j++)
		{
			cin >> depart >> arrive;
			Timetable[j].a2b = true;
			Timetable[j].depart = Time2Minute(depart);
			Timetable[j].arrive = Time2Minute(arrive) + T;
		}

		for (int j = 0; j < B; j++)
		{
			cin >> depart >> arrive;
			Timetable[j + A].a2b = false;
			Timetable[j + A].depart = Time2Minute(depart);
			Timetable[j + A].arrive = Time2Minute(arrive) + T;
		}

		sort(Timetable.begin(), Timetable.end());

		list<int> Aready, Bready;
		int Acount = 0, Bcount = 0;
		for (auto& train : Timetable)
		{
			current_time = train.depart;
			if (train.a2b)
			{
				auto it = find_if(Aready.begin(), Aready.end(), IsGood);
				if (it != Aready.end())
				{
					Aready.erase(it);
				}
				else
				{
					Acount++;
				}

				Bready.push_back(train.arrive);
			}
			else
			{
				auto it = find_if(Bready.begin(), Bready.end(), IsGood);
				if (it != Bready.end())
				{
					Bready.erase(it);
				}
				else
				{
					Bcount++;
				}

				Aready.push_back(train.arrive);
			}
		}

		cout << "Case #" << i << ": " << Acount << " " << Bcount << endl;
	}

	return 0;
}