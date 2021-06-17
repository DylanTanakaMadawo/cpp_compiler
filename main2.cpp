#include <bits/stdc++.h>

using namespace std;

// Function to perform arithmetic operations.
int operator_application(int lhs, int rhs, char current_operator)
{
    int i = 0, result = 1;
    if (current_operator == '+')
    {
        return lhs + rhs;
    }
    else if (current_operator == '-')
    {
        return lhs - rhs;
    }
    else if (current_operator == '/')
    {
        return lhs / rhs;
    }
    else if (current_operator == '*')
    {
        return lhs * rhs;
    }
    else if (current_operator == '^')
    {
        while (i < rhs)
        {
            result *= lhs;
            i++;
        }
        return result;
    }
    else
    {
        return lhs;
    }

    return 1;
}

//check for the precedence of the operator
int check_precedence(char current_operator)
{
    if (current_operator == '/' || current_operator == '*')
    {
        return 2;
    }

    if (current_operator == '-' || current_operator == '+')
    {
        return 1;
    }
    if (current_operator == '^')
    {
        return 3;
    }

    return 0;
}

//get value value of the standard expression
int get_value(string my_string)
{
    int i;

    // store numbers
    stack<int> my_numbers;

    //store operators.
    stack<char> my_characters;

    for (i = 0; i < my_string.length(); i++)
    {

        //skip white space
        if (my_string[i] == ' ')
            continue;

        //accomodate negative numbers
        else if (my_string[i] == '-')
        {
            my_numbers.top() *= -1;
            continue;
        }

        else if (my_string[i] == '(')
        {
            my_characters.push(my_string[i]);
        }

        // Current token is a number, push
        // it to stack for numbers.
        else if (isdigit(my_string[i]))
        {
            int x = 0;

            // There may be more than one
            // digits in number.
            while (i < my_string.length() && isdigit(my_string[i]))

            {
                x = (x * 10) + (my_string[i] - '0');
                i++;
            }

            my_numbers.push(x);

            // right now the i points to
            // the character next to the digit,
            // since the for loop also increases
            // the i, we would skip one
            // token position; we need to
            // decrease the xue of i by 1 to
            // correct the offset.
            i--;
        }
        else if (my_string[i] >= 'a' && my_string[i] <= 'z')
        {
            int x = my_string[i] - '0';
            int next_value = (my_string[i + 2] - '0');
            int j = 2;

            //a number can be multiple digits
            while (i < my_string.length() && (my_string[i] >= 'a' && my_string[i] <= 'z'))
            {
                next_value = next_value + (my_string[i] - '0');
                i++;
            }

            int *ptr = &next_value;
            x = *ptr;
            x = x - 48;

            my_numbers.push(x);
        }

        // Closing brace encountered, solve
        // entire brace.
        else if (my_string[i] == ')')
        {
            while (!my_characters.empty() && my_characters.top() != '(')
            {
                int x2 = my_numbers.top();
                my_numbers.pop();

                int x1 = my_numbers.top();
                my_numbers.pop();

                char op = my_characters.top();
                my_characters.pop();

                my_numbers.push(operator_application(x1, x2, op));
            }

            // pop opening brace.
            if (!my_characters.empty())
                my_characters.pop();
        }

        // Current token is an operator.
        else
        {
            // While top of 'my_characters' has same or greater
            // check_precedence to current token, which
            // is an operator. Apply operator on top
            // of 'my_characters' to top two elements in my_numbers stack.
            while (!my_characters.empty() && check_precedence(my_characters.top()) >= check_precedence(my_string[i]))
            {
                int x2 = my_numbers.top();
                my_numbers.pop();

                int x1 = my_numbers.top();
                my_numbers.pop();

                char op = my_characters.top();
                my_characters.pop();

                my_numbers.push(operator_application(x1, x2, op));
            }

            // Push current token to 'my_characters'.
            my_characters.push(my_string[i]);
        }
    }

    // Entire expression has been parsed at this
    // point, apply remaining my_characters to remaining
    // my_numbers.
    while (!my_characters.empty())
    {
        int x2 = my_numbers.top();
        my_numbers.pop();

        int x1 = my_numbers.top();
        my_numbers.pop();

        char op = my_characters.top();
        my_characters.pop();

        my_numbers.push(operator_application(x1, x2, op));
    }

    // Top of 'my_numbers' contains result, return it.
    return my_numbers.top();
}

int main()
{
    char my_string[100], check = 0;

    int i = 0;
    while (my_string[0] != '!')
    {
        cout << "------waiting for input--------" << endl;
        cout << "------press ! to exit--------" << endl;

        //get whole line
        cin.getline(my_string, 100);

        if (my_string[0] != '!')
        {
            cout << get_value(my_string) << "\n";
        }
        else
        {
            check = 1;
            cout << "exit\n";
            cout << my_string << "\n";
            break;
        }

        i = i + 1;
    }
    return 0;
}