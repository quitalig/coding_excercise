#include <iostream>
#include <string>
#include <list>

class Solution
{
public:
	std::string check(std::list<int> input)
	{
		if (0 == input.size())
			return "True";

		int count = 0;

		for (auto itr = std::next(input.begin()); itr != input.end(); itr++)
		{
			if (*(std::prev(itr)) > *itr )
			{
				count++;
				
				if(count > 1)
					return "False"
			}
		}

		return "True";
	}
};

int main()
{
	Solution solutions;

	std::list<int> A = { 13, 4, 7 };
	std::list<int> B = { 5,1,3,2,5 };
	std::list<int> C = { 1,2,5,7,100 };
	std::list<int> D = { };
	std::list<int> E = { 2 };

	std::cout << solutions.check(A) << std::endl;
	std::cout << solutions.check(B) << std::endl;
	std::cout << solutions.check(C) << std::endl;
	std::cout << solutions.check(D) << std::endl;
	std::cout << solutions.check(E) << std::endl;
}