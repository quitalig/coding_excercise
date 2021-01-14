/*Activity#4: Validate Balanced Parentheses*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
	string isValid(string inputStr)
	{
		vector<char> storeString;

		if ((inputStr.length() % 2) != 0)
		{
			return "False";
		}

		for (int ctr = 0; ctr < (int)inputStr.length(); ctr++)
		{
			if ('(' == inputStr[ctr] || '{' == inputStr[ctr] || '[' == inputStr[ctr])
			{
				storeString.push_back(inputStr[ctr]);
			}
			else
			{
				switch (inputStr[ctr])
				{
				case ')':
					if (storeString.back() != '(')
						return "False";
					break;
				case '}':
					if ((storeString.back()) != '{')
						return "False";
					break;
				case ']':
					if ((storeString.back()) != '[')
						return "False";
					break;
				}

				storeString.pop_back();
			}
		}

		if ((storeString.size()) != 0)
		{
			return "False";
		}

		return "True";
	}
};


int main()
{
	Solution solutions;

    cout << "{}()() - " << solutions.isValid("{}()()") << endl;
    cout << "{}(()() - " << solutions.isValid("{}(()()") << endl;
    cout << ") - " << solutions.isValid(")") << endl;
	cout << "()(){(()) - " << solutions.isValid("()(){(())") << endl;
	cout << "(EMPTY STRING) - " << solutions.isValid("") << endl;
	cout << "([{}])() - " << solutions.isValid("([{}])()") << endl;
}
