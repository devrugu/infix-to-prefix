#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool IsOp(char character)
{
    return(character=='*' || character=='+' || character=='/' || character=='-');
}

int OperatorPrecedence(char Operator)
{
    switch (Operator)
    {
        case '*' : return 3;
        case '/' : return 3;
        case '+' : return 2;
        case '-' : return 2;
        case '(' : return 1;
    }
}

int SizeOfString(string infix)
{
    int counter = 0;
    char *ptr = &infix[0];
    while(*ptr!='\0')
    {
        ptr++;
        counter++;
    }
    return counter;
}
string ReverseExpression(string infix)
{
    string RevInfix = "";
    int counter = 0;
    char *ptr = &infix[0];
    while(*ptr!='\0')
    {
        ptr++;
        counter++;
    }
    ptr--;
    
    for(int i=0; i<counter; i++)
    {
        if(*ptr=='(')
        {
            RevInfix += ')';
            ptr--;
            continue;
        }
        else if(*ptr==')')
        {
            RevInfix += '(';
            ptr--;
            continue;
        }
        RevInfix += *ptr;
        ptr--;
    }
    
    return RevInfix;
}

string InfixToPostfix(string RevInfix)
{
    stack <char> OperatorStack;
    string Postfix = "";
    char *ptr = &RevInfix[0];
    int size = SizeOfString(RevInfix);
    for(int i = 0; i<size; i++)
    {
        if(IsOp(*ptr))
        {
            while(!OperatorStack.empty() && OperatorPrecedence(*ptr) <= OperatorPrecedence(OperatorStack.top()))
            {
                if(*ptr == OperatorStack.top() && (*ptr == '^'))
                    break;
                Postfix += OperatorStack.top();
                OperatorStack.pop();
            }
            OperatorStack.push(*ptr);
            ptr++;
        }
        else if(*ptr == '(' || *ptr == ')')
        {
            if(*ptr == '(')
            {
                OperatorStack.push(*ptr);
                ptr++;
            }
            else
            {
                while(OperatorStack.top()!='(')
                {
                    Postfix += OperatorStack.top();
                    OperatorStack.pop();
                }
                OperatorStack.pop();
                ptr++;
            }
        }
        else
        {
            Postfix += *ptr;
            ptr++;
        }
    }
    while(!OperatorStack.empty())
    {
        Postfix += OperatorStack.top();
        OperatorStack.pop();
    }
    return Postfix;
}

int main()
{
    string infix;
    cout<<"Input Infix expression"<<endl;
    cin>>infix;
    cout<<"Infix Expression (Original) --> "<<infix<<endl;
    string RevInfix = ReverseExpression(infix);
    //cout<<"Reversed Infix Expression --> "<<RevInfix<<endl;
    string Postfix = InfixToPostfix(RevInfix);
    //cout<<"Reversed Infix Expression with Postfix Notation --> "<<Postfix<<endl;
    string Prefix = ReverseExpression(Postfix);
    cout<<"Prefix Expression --> "<<Prefix<<endl;
}