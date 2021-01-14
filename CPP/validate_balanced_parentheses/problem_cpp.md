# Validate Balanced Parentheses

<p>
<em>This problem was recently asked by Uber!</em>

Imagine you are building a compiler. Before running any code, the compiler must check that the parentheses in the program are balanced. Every opening bracket must have a corresponding closing bracket. We can approximate this using strings.

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
An input string is valid if:
- Open brackets are closed by the same type of brackets.
- Open brackets are closed in the correct order.
- Note that an empty string is also considered valid.

**Example:**<br />
**Input:** "((()))"<br />
**Output:** True<br />

**Input:** "[()]{}"<br />
**Output:** True<br />

**Input:** "({[)]"<br />
**Output:** False<br />
</p>

```cpp
class Solution
{
public:
    bool isValid(s)
    {
        // Fill this in.
    }
};

// Test Program
std::string s = "()(){(())";
// should return False
std::cout << solution.isValid(s));

s = ""
// should return True
std::cout << solution.isValid(s));

s = "([{}])()"
// should return True
std::cout << solution.isValid(s));
```