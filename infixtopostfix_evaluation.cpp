#include <iostream>
#include <stdlib.h>
using namespace std;

struct stack
{
    char c;
    stack *next;
    stack *prev;
};
stack *top = NULL;
struct stack1
{
    int c1;
    stack1 *next1;
    stack1 *prev1;
};
stack1 *top1 = NULL;

int prec(char c1)
{
    if (c1 == '*' || c1 == '/')
    {
        return 5;
    }
    else if (c1 == '+' || c1 == '-')
    {
        return 4;
    }
    else if (c1 == '>' || c1 == '<' || c1 == '!')
    {
        return 3;
    }
    else if (c1 == '&')
    {
        return 2;
    }
    else if (c1 == '|')
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
void insert_2(int c1)
{
    struct stack1 *temp1 = (struct stack1 *)malloc(sizeof(struct stack1));
    temp1->c1 = c1;
    temp1->next1 = NULL;
    temp1->prev1 = NULL;
    if (top1 == NULL)
    {
        top1 = temp1;
    }
    else
    {
        temp1->next1 = top1;
        top1->prev1 = temp1;
        top1 = temp1;
    }
}
void insert(char c1)
{
    struct stack *temp = (struct stack *)malloc(sizeof(struct stack));
    temp->c = c1;
    temp->next = NULL;
    temp->prev = NULL;
    if (top == NULL)
    {
        top = temp;
    }
    else
    {
        temp->next = top;
        top->prev = temp;
        top = temp;
    }
}
void pop1()
{
    struct stack1 *curr = top1;
    top1 = top1->next1;
    free(curr);
}
struct stack *pop()
{
    struct stack *curr = top;
    struct stack *curr1 = top;
    top = top->next;
    free(curr);
    return top;
}
string postfix()
{
    string c;
    string res;
    cout << "Enter the equation: " << endl;
    cin >> c;
    for (int i = 0; i < c.length(); i++)
    {
        if (c[i] >= '0' && c[i] <= '9')
        {
            res += c[i];
        }
        else if (c[i] == '(')
        {
            insert(c[i]);
        }
        else if (c[i] == ')')
        {
            while (top != NULL && top->c != '(')
            {
                res += top->c;
                pop();
            }
            if (top != NULL)
            {
                pop();
            }
        }
        else
        {
            if (c[i] == '&' || c[i] == '|' || c[i] == '!')
            {
                i++;
            }
            while (top != NULL && prec(top->c) >= prec(c[i]))
            {
                res += top->c;
                pop();
            }
            insert(c[i]);
        }
    }
    while (top != NULL)
    {
        res = res + top->c;
        pop();
    }
    return res;
}
int main()
{
    string ptfix = postfix();
    string res;
    cout << ptfix << endl;
    for (int i = 0; i < ptfix.length(); i++)
    {
        if (ptfix[i] >= '0' && ptfix[i] <= '9')
        {
            insert_2(int(ptfix[i]) - '0');
        }
        else
        {
            int op2 = top1->c1;
            pop1();
            int op1 = top1->c1;
            pop1();
            switch (ptfix[i])
            {
            case '+':
                insert_2(op1 + op2);
                break;
            case '-':
                insert_2(op1 - op2);
                break;

            case '/':
                insert_2(op1 / op2);
                break;

            case '&':
                insert_2(op1 && op2);
                break;

            case '*':
                insert_2(op1 * op2);
                break;

            case '|':
                insert_2(op1 || op2);
                break;
            case '>':
                insert_2(op1 > op2);
                break;

            case '<':
                insert_2(op1 < op2);
                break;
            }
        }
    }
    cout << top1->c1;
}
