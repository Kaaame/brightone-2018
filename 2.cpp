# brightone-2018

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	string input;
	getline(cin, input);
	stringstream buffer(input);
	string hold;
	vector<string> res;
	vector<int> converted;
	while (getline(buffer, hold, ' ')) res.push_back(hold);

	for (int i = 0; i < res.size(); i++)
	{
		converted.push_back(atoi(res[i].c_str()));
	}
	if (converted.size() == 2) return 0;
	int leftsum = 0, rightsum = 0;

	for (int i = 1; i < converted.size(); i++)
	{

		for (int j = 0; j < i; j++) leftsum += converted[j];
		for (int j = i + 1; j < converted.size(); j++) rightsum += converted[j];
		if (leftsum == rightsum)
		{
			cout << "Yes";
			return 0;
		}
		leftsum = 0;
		rightsum = 0;
	}
	cout << "No";
	return 0;

}
