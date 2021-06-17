#include <bits/stdc++.h>

using namespace std;
// Function to find precedence of
// operators.
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}
// Function to perform arithmetic operations.

double applyOp(double a, double b, char op)
{
    int i = 0;
    int result = 1;
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        while (i < b)
        {
            result *= a;
            i++;
        }
        return result;
    default:
        return a;
    }
    return 1;
}

// int applyAssignment(char op, int x)
// {
//     int y = op - '0';
//     int *ptr = &x;
//     y = *ptr;
//     if (op == '=')
//     {
//         return y;
//     }
//     return 1;
// }

// Function that returns value of
// expression after evaluation.
int evaluate(string tokens)
{
    int i;

    // stack to store integer values.
    stack<double> values;

    // stack to store operators.
    stack<char> ops;

    for (i = 0; i < tokens.length(); i++)
    {

        // Current token is a whitespace,
        // skip it.
        if (tokens[i] == ' ')
            continue;

        // Current token is an opening
        // brace, push it to 'ops'
        else if (tokens[i] == '(')
        {
            ops.push(tokens[i]);
        }

        // Current token is a number, push
        // it to stack for numbers.
        else if (isdigit(tokens[i]))
        {
            int val = 0;

            // There may be more than one
            // digits in number.
            while (i < tokens.length() && isdigit(tokens[i]))
            {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }

            values.push(val);

            // right now the i points to
            // the character next to the digit,
            // since the for loop also increases
            // the i, we would skip one
            // token position; we need to
            // decrease the value of i by 1 to
            // correct the offset.
            i--;
        }
        else if (tokens[i] >= 'a' && tokens[i] <= 'z')
        {
            int x = tokens[i] - '0';
            int next_value = (tokens[i + 2] - '0');
            int j = 2;
            while (i < tokens.length() && (tokens[i] >= 'a' && tokens[i] <= 'z'))
            {
                next_value = next_value + (tokens[i] - '0');
                i++;
            }

            int *ptr = &next_value;
            x = *ptr;
            x = x - 48;

            values.push(x);
        }

        //--------------------------------------------------
        // else if (tokens[i] == '=')
        // {
        //     int val = values.top();
        //     char op = tokens[i];

        //     cout << " above " << endl;
        //     values.push(applyAssignment(op, val));
        //     cout << " below " << endl;
        // }
        //----------------------------------------------------

        // Closing brace encountered, solve
        // entire brace.
        else if (tokens[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // pop opening brace.
            if (!ops.empty())
                ops.pop();
        }

        // Current token is an operator.
        else
        {
            // While top of 'ops' has same or greater
            // precedence to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in values stack.
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i]))
            {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }

    // Entire expression has been parsed at this
    // point, apply remaining ops to remaining
    // values.
    while (!ops.empty())
    {
        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    // Top of 'values' contains result, return it.
    // cout << values.size() << endl;
    return values.top();
}
int main()
{

    cout << "waiting input....." << endl;
    char s[100], f = 0;
    for (int i = 0; s[0] != '!'; i++)
    {
        cin >> s;

        if (s[0] == '!')
        {
            f = 1;
            cout << "end\n";
            cout << s << "\n";
            break;
        }
        else
        {
            cout << evaluate(s) << "\n";
        }
    }
    return 0;
}