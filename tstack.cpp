#include"stack.h"
#include"stack.hpp"

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

using std::cout;
using std::cin;
using std::endl;

void test_stack()
{
    srand(time(NULL));
    cout << "-----stack-----" << endl;
    stack<int> stk;
    cout << stk.is_empty() << endl;

    for(int i = 0; i < 10; i++)
    {
        stk.push(rand() % 1000);
        cout << "stack.top = " <<  stk.top() << endl;
        cout << "stack.size = " << stk.size() << endl;
    }

    cout << stk.empty() << endl;
    cout << "stack.size = " << stk.size() << endl;
    for(; stk.size() > 0;)
    {
        cout << "stack.size = " << stk.size() << endl;
        cout << "pop = " << stk.pop() << endl;
    }
    cout << stk.is_empty() << endl;
}

char optr_order(char optr, char expr)
{
    char comp[128] = {0};
    comp['+'] = 0;
    comp['-'] = 1;
    comp['*'] = 2;
    comp['/'] = 3;
    comp['^'] = 4;
    comp['!'] = 5;
    comp['('] = 6;
    comp[')'] = 7;
    comp['\0'] = 8;
    char prio[9][9] = {
        {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
        {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '>', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '>', '>', ' ', '>', '>'},
        {'<', '<', '<', '<', '<', '<', '<', '=', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'<', '<', '<', '<', '<', '<', '<', ' ', '='},
    };

    return prio[comp[optr]][comp[expr]];
}
double fact(double opnd)
{
    double n = 1;
    for(; opnd > 0; opnd--)
        n *= opnd;
    return n;
}
double calc(double opnd1, char op, double opnd2)
{
    double ret = 0;
    switch(op)
    {
    case '+':
        ret = (double)(opnd1 + opnd2);
        break;
    case '-':
        ret = (double)(opnd1 - opnd2);
        break;
    case '*':
        ret = (double)(opnd1 * opnd2);
        break;
    case '/':
        ret = (double)(opnd1 / opnd2);
        break;
    case '^':
        ret = (double)pow(opnd1, opnd2);
        break;
    }
    return ret;
}
void evaluate()
{
#include<string>
    using std::string;
    string RPN = "";
    cout << "----RPN evaluate----" << endl;
    const char * expr= "(1 + 2 ^ 3! - 4) * (5! - (6 - (7 - (89 - 0!))))";
    cout << expr << " = ";
    stack<char> optr;
    optr.push('\0');
    stack<double> opnd;
    for(; !optr.empty(); )
    {
        if(*expr == ' ')
            expr++;
        if(isdigit(*expr))
        {
            const char * p = expr;
            for(; isdigit(*p); p++) RPN += *p;
            opnd.push(strtod(expr, NULL));
            RPN += ' ';
            expr = p;
        }
        if(*expr == ' ')
            expr++;
        switch(optr_order(optr.top(), *expr))
        {
            case '<': //栈顶小于当前，入栈
                optr.push(*expr);
                expr++;
                break;
            case '=': // 当前/栈顶为 ')'/'\0'
                optr.pop();
                expr++;
                break;
            case '>': // 栈顶大于当前，计算
                char op = optr.pop();
                RPN += op;
                RPN += ' ';
                if(op == '!')
                    opnd.push(fact(opnd.pop()));
                else
                {
                    double opnd2 = opnd.pop(), opnd1 = opnd.pop();
                    opnd.push(calc(opnd1, op, opnd2));
                }
                break;
        }
    }
    cout << opnd.pop() << endl;
    cout << "RPN = " << RPN << endl;
}
void sys_convert()
{
    cout << "----sys convert----" << endl;
    int n = rand() % (int)1e6;
    n =  2013;
    char digit[] = "0123456789ABCDEF";
    int scale = 16;
    cout << n << " to " << scale << "sys" << endl;
    stack<char> s;
    while(n != 0)
    {
        s.push(digit[n % scale]);
        n /= scale;
    }
    for(; s.size();)
        cout << s.pop();
    cout << endl;
}
void apply_stk()
{
    cout << "-----stack apply-----" << endl;
    // sys_convert();
    evaluate();
}

