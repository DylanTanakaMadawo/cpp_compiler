            int x = tokens[i] - '0';
            int next_value;
            int *ptr;
            while ((i < tokens.length()) && isdigit(tokens[i]))
            {
                next_value = tokens[i + 2];
                ptr = &next_value;
                x = *ptr;
                x = x - 48;
            }

            values.push(x);
            i--;