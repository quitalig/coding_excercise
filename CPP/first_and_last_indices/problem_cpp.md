# First and Last Indices of an Element in a Sorted Array

<p>
<em>This problem was recently asked by AirBNB!</em>

Given a sorted array, A, with possibly duplicated elements, find the indices of the first and last occurrences of a target element, x. Return -1 if the target is not found.

**Example:**<br />
**Input:** A = [1,3,3,5,7,8,9,9,9,15], target = 9<br />
**Output:** [6,8]<br />

**Input:** A = [100, 150, 150, 153], target = 150<br />
**Output:** [1,2]<br />

**Input:** A = [1,2,3,4,5,6,10], target = 9<br />
**Output:** [-1, -1]<br />

Here is a function signature example:
</p>

```cpp
class Solution
{
public:
    std::pair<int, int> getRange(...)
    {
        // Fill this in.
    }

};
  
// Test program 
arr = [1, 2, 2, 2, 2, 3, 4, 7, 8, 8] 
x = 2

std::pair<int, int> result = solution.getRange(arr, x);
std::cout << result.first << " " << result.second << std::endl;
// [1, 4]
```