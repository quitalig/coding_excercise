#include <iostream>
#include <utility>

class Solution
{
public:
	std::pair<int, int> getRange(int *arr, int target, int arrSize)
	{
		std::pair <int, int> result(-1, -1);

		for (int i = 0; i < arrSize; i++)
		{
			if (target == arr[i] && -1 == result.first)
			{
				result.first = i;
			}

			if (target == arr[i] && target != arr[i+1])
			{
				result.second = i;
				break;
			}
		}

		return result;
	}
};


int main()
{
	Solution solutions;

	int arr[] = {1,2,2,2,2,3,4,7,8,8};
	int x = 2;
	std::pair<int, int> result = solutions.getRange(arr, x, std::size(arr));
	std::cout << result.first << ", " << result.second << std::endl;

	int arr1[] = {1,3,3,5,7,8,9,9,9,15};
	x = 9;
	result = solutions.getRange(arr1, x, std::size(arr));
	std::cout << result.first << ", " << result.second << std::endl;

	int arr2[] = {100,150,150,153};
	x =150;
	result = solutions.getRange(arr2, x, std::size(arr));
	std::cout << result.first << ", " << result.second << std::endl;

	int arr3[] = {1,2,3,4,5,6,10};
	x = 9;
	result = solutions.getRange(arr3, x, std::size(arr));
	std::cout << result.first << ", " << result.second << std::endl;
} 