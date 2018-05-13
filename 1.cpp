#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <conio.h>
#include <algorithm>

using namespace std;
using std::cout;

typedef struct
{
	string hexa;
	int inte;
} val;

int countbit(val &a)
{
	int hold = a.inte;
	int res = 0;
	while (hold > 0)
	{
		if (hold & 0x1) res++;
		hold >>= 1;
	}
	return res;
}

bool compare(const val &a, const val &b)
{
	return a.inte < b.inte;
}

int main()
{
	string filename;
	cout << "Podaj nazwe pliku: ";
	cin >> filename;

	fstream fd;
	fd.open(filename, ios::in, ios::binary);
	if (!fd.is_open())
	{
		cout << "\nNie mozna bylo otworzyc pliku.\n";
		return 1;
	}
	string fbuf;
	string filterbuf;
	while (!fd.eof())
	{
		fd >> fbuf;
		//getline(fd, fbuf);
		//cout << filebuffer << endl;
		for (int i = 0; i < fbuf.size(); i++)
		{
			if ((fbuf[i] >= 'A' && fbuf[i] <= 'F') || (fbuf[i] >= '0' && fbuf[i] <= '9'))
			{
				filterbuf += fbuf[i];
			}
		}
	}

	char * buffer = new char[2];
	buffer[2] = '\0';
	int num;
	int size;
	vector<val> values;
	val hold;
	int iter = 0;
	for (int i = 0; i < filterbuf.size(); i = i + 2, iter++)
	{
		buffer[i % 2] = filterbuf[i];
		if (i < filterbuf.size()) buffer[(i % 2) + 1] = filterbuf[i + 1];

		sscanf_s(buffer, "%x", &num);
		hold.hexa = buffer;
		hold.inte = num;
		values.insert(values.begin(), hold);
	}
	vector<val> even;
	vector<val> odd;

	for (int i = 0; i < values.size(); i++)

	{
		if ((countbit(values[i]) % 2) == 0)
		{
			even.insert(even.begin(), values[i]);
		}
		else
		{
			odd.insert(odd.begin(), values[i]);
		}
	}

	sort(even.begin(), even.end(), compare);
	sort(odd.begin(), odd.end(), compare);
	reverse(odd.begin(), odd.end());

	fstream fdres;
	fdres.open("wyniki.txt", ios::out);
	if (!fdres.is_open())
	{
		cout << "\nNie mozna bylo otworzyc pliku.\n";
		return 1;
	}

	for (int i = 0; i < even.size(); i++)
	{
		fdres << even[i].hexa << '=' << even[i].inte << '\n';
	}
	fdres << '\n';
	for (int i = 0; i < odd.size(); i++)
	{
		fdres << odd[i].hexa << '=' << odd[i].inte << '\n';
	}
}
