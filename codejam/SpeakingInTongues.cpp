#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

using namespace std;

int main()
{
	string G1 = "ejp mysljylc kd kxveddknmc re jsicpdrysi";
	string G2 = "rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd";
	string G3 = "de kr kd eoya kw aej tysr re ujdr lkgc jv";

	string S1 = "our language is impossible to understand";
	string S2 = "there are twenty six factorial possibilities";
	string S3 = "so it is okay if you want to just give up";

	int n = (int)('z' - 'a' + 1);
	vector<char> mapping(n, '0');
	set<char> letterS;
	set<char> letterG;
	for (char i = 'a'; i <= 'z'; ++i)
	{
		letterS.insert(i);
		letterG.insert(i);
	}

	for (size_t i = 0; i < G1.length(); ++i)
	{
		if (G1[i] == ' ')
			continue;

		mapping[G1[i] - 'a'] = S1[i];
		letterS.erase(S1[i]);
		letterG.erase(G1[i]);
	}

	for (size_t i = 0; i < G2.length(); ++i)
	{
		if (G2[i] == ' ')
			continue;
		mapping[G2[i] - 'a'] = S2[i];
		letterS.erase(S2[i]);
		letterG.erase(G2[i]);
	}

	for (size_t i = 0; i < G3.length(); ++i)
	{
		if (G3[i] == ' ')
			continue;
		mapping[G3[i] - 'a'] = S3[i];
	}

	// only q,z remain. Let try to switch them.
	mapping['q' - 'a'] = 'z';
	mapping['z' - 'a'] = 'q';
	
	int T;
	string G;

	cin >> T;
	getline(cin, G); // bypass first line.
	for (int i = 1; i <= T; ++i)
	{
		// read line.
		getline(cin, G);

		for (auto& ch : G)
			if (ch != ' ')
				ch = mapping[ch - 'a'];

		cout << "Case #" << i << ": " << G << endl;
	}

	return 0;
}