#include "std_lib_facilities.h"

int main()
{
	vector<string> names;
	vector<int> value;


	cout << "Input(name, score) pairs" << '\n';

	string s;
	int i;
	int count = 0;

	for (; cin >> s >> i;)
	{

		if (s == "NoName" && i == 0)
			break;

		names.push_back(s);
		value.push_back(i);


		
	}


	bool success = true;
	for (int a = 0; a < names.size(); a++)
	{
		for (int b = 1; b < names.size() - a; b++)
			if (names[a] == names[a + b])
			{
				cout << "Bad! The name " << "\""<<names[a]<<"\"" << " is entered more than once\n";
				success = false;
			}
	}

	if (success)
	{
		cout << "Good! Each name is entered just once.\n";

		for (int i = 0; i < names.size(); i++)
			cout << names[i] << ' ' << value[i] << '\n';
	}


	return 0;
}