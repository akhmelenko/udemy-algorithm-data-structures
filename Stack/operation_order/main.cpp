
#include <stdio.h>
#include <string>
#include <stack>
#include <map>

std::map<char, int> presedenceIn{
    {'+', 2},
    {'-', 2},
    {'*', 4},
    {'/', 4},
    {'(', 0},
    {')', 7},
};

std::map<char, int> presedenceOut{
    {'+', 1},
    {'-', 1},
    {'*', 3},
    {'/', 3},
    {'(', 7},
    {')', 0},
};

bool IsOperand(char c)
{
    if (presedenceIn.find(c) != presedenceIn.end())
        return true;
    if (presedenceOut.find(c) != presedenceOut.end())
        return true;
    return false;
}

std::string Postfix(std::string &expr)
{
    std::stack<char> st;
    std::string postfix;
    for (auto c : expr)
    {
        if (IsOperand(c))
        {
            if (st.empty() ||
                presedenceOut[c] >= presedenceIn[st.top()])
                st.push(c);
            else
            {
                // copy stack (inside braces, if exists, or all, if not exists) to postfix
                while (!st.empty() && st.top() != '(')
                {
                    postfix += st.top();
                    st.pop();
                }
                if (c == ')' && st.top() == '(')
                    st.pop(); // remove '('
                else
                    st.push(c);
            }
        }
        else
            postfix += c;
    }
    // copy stack to postfix
    while (!st.empty())
    {
        postfix += st.top();
        st.pop();
    }
    return postfix;
}

char Operation(char operation, char lhs, char rhs)
{
    switch (operation)
    {
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    case '*':
        return lhs * rhs;
    case '/':
        return lhs / rhs;
    default:
        return 0;
    }
}

int Calc(std::string &expr)
{
    std::string postfix = Postfix(expr);
    std::stack<char> st;
    for (auto c : postfix)
    {
        if (IsOperand(c))
        {
            char rhs = st.top();
            st.pop();
            char lhs = st.top();
            st.pop();
            char result = Operation(c, lhs, rhs);
            st.push(result);
        }
        else
            // char to digit
            st.push(c - '0');
    }
    return st.top();
}

int main()
{
    printf("Start main\n\r");
    std::string input1{"1*3+4"};     // (13*)4+
    std::string input2{"1+2*3+4*5"}; // 1(34*)+
    std::string input3{"1+2*3-4/5"};
    std::string input4{"(1+2)*3-4"};
    std::string input5{"1+(2+3)*4"}; // 21
    std::string input6{"1+(2+(9-2)*2)*4"};
    std::string input7{"1+(2+2*2)/4"};

    printf("input: %s, postfix: %s, result: %d\n\r", input1.c_str(), Postfix(input1).c_str(), Calc(input1));
    printf("input: %s, postfix: %s, result: %d\n\r", input2.c_str(), Postfix(input2).c_str(), Calc(input2));
    printf("input: %s, postfix: %s, result: %d\n\r", input3.c_str(), Postfix(input3).c_str(), Calc(input3));
    printf("input: %s, postfix: %s, result: %d\n\r", input4.c_str(), Postfix(input4).c_str(), Calc(input4));
    printf("input: %s, postfix: %s, result: %d\n\r", input5.c_str(), Postfix(input5).c_str(), Calc(input5));
    printf("input: %s, postfix: %s, result: %d\n\r", input6.c_str(), Postfix(input6).c_str(), Calc(input6));
    printf("input: %s, postfix: %s, result: %d\n\r", input7.c_str(), Postfix(input7).c_str(), Calc(input7));

    return 0;
}