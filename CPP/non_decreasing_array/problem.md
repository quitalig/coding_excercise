# Non-decreasing Array with Single Modification

<em>This problem was recently asked by Microsoft</em>

<p>
You are given an array of integers in an arbitrary order. Return whether or not it is possible to make the array non-decreasing by modifying at most 1 element to any value.

We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).

**Example:**<br />

[13, 4, 7] should return true, since we can modify 13 to any value 4 or less, to make it non-decreasing.

[13, 4, 1] however, should return false, since there is no way to modify just one element to make the array non-decreasing.

Here is the function signature:
</p>

```cpp
std::string check(...)
{
  // Fill this in.
}

std::list<int> A = {13, 4, 7};
std::list<int> B = {5,1,3,2,5};

std::cout << check(A) << std::endl;
// True
std::cout << check(B) << std::endl;
// False
```
<p>
Can you find a solution in O(n) time?
</p>
