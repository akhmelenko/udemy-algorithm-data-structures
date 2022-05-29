#include <iostream>
#include "stack.h"
#include <string>

bool IsValidParences(std::string &str)
{
    Stack<char> st;
    for (auto &ch : str)
    {
        // check for open parences
        if (ch == '(' || ch == '[' || ch == '{')
        {
            st.Push(ch);
        }
        // check for close parences
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            if (st.Empty())
                return false;
            if (st.Top() == '(' && ch == ')' || st.Top() == '[' && ch == ']' || st.Top() == '{' && ch == '}')
                st.Pop();
            else
                return false;
        }
    }
    // check size of stack
    if (st.Empty())
        return true;
    else
        return false;
}

int main()
{
    std::string str = "(fd*{57})[]{}";
    std::cout << IsValidParences(str);

    return 0;
}