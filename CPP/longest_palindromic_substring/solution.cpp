#include <iostream>
#include <string>

class Solution
{
public:
	std::string longestPalindrome(std::string str)
	{
		std::string result, temp;

		for (int i = 1; i < str.length(); i++)
		{
			if (str[i] == str[i + 1])
			{
				temp = getPalindrome(str, i, i + 1);
			}
			else if (str[i - 1] == str[i + 1])
			{
				temp = getPalindrome(str, i - 1, i + 1);
			}

			if (temp.length() > result.length())
			{
				result = temp;
			}
		}
		return result;
	}

private:
	std::string getPalindrome(std::string input, int start, int end)
	{
		std::string output;

		while ((input[start] == input[end]) && ((start != 0) || (end != input.length() - 1)))
		{
			output = input.substr(start, end - start + 1);
			
			start--;
			end++;
		}

		return output;
	}
};

int main()
{
	Solution solutions;

	std::cout << solutions.longestPalindrome("tracecars") << std::endl;

	std::cout << solutions.longestPalindrome("bananacake") << std::endl;

	std::cout << solutions.longestPalindrome("MILLIONS") << std::endl;

	std::cout << solutions.longestPalindrome("WINNER") << std::endl; 
}