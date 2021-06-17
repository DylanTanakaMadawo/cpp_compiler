#include <bits/stdc++.h>
#include <iostream>
#include <string>

using namespace std;

class Parser
{
public:
    Parser(char *line);
    ~Parser();

    Expression *statement();

private:
    Tokenizer *tokens;

    Expression *assignment();
    Expression *calculation();
    Expression *sum();
    Expression *product();
    Expression *factor();
    Expression *power();
    Expression *term();
    Expression *group();
    Expression *number();
    Expression *variable();
};

Expression *Parser::assignment()
{
    int mark = tokens->mark();
    VariableExpression *var = nullptr;
    Expression *rhs = nullptr;
    if ((var = tokens->variable()) && tokens->character('=') && (rhs = sum()) && tokens->atEnd())
        return new AssignmentExpression(var, rhs);
    if (var)
        delete var;
    if (rhs)
        delete rhs;
    tokens->reset(mark);
    return nullptr;
}