// Aaron Chien
// 405498016
#include <iostream>
#include <stack>
#include <cassert>
#include <string>
using namespace std;

int helper(char x);

bool testCh(char x, char y);

bool assignCh(char x);

bool evalOp(char x, bool op2, bool op1);

int evaluate(string infix, string& postfix, bool& result)
{
    postfix = "";
    stack<char> S_operator;
    int countP = 0;
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] == ' ')
        {
            infix.erase(i, 1);
            i--;
        }
    }
    // first edge case
    // testing if the first char in infix is an operator (invalid)
    bool testStart = infix[0] != '(' && infix[0] != 'T' && infix[0] != 'F' && infix[0] != '!';
    if (testStart)
    {
        return 1;
    }

    for(int i = 0; i < infix.size(); i++)
    // loop through the infix string and ensure that it is valid 
    {
        if (infix[i] == 'T' || infix[i] == 'F')
        // if the character is an operand, append it to postfix
        {
            if (i+1 < infix.size())
            // check if the operand is valid first 
            {
                if (testCh(infix[i], infix[i+1]))
                // if the value next to the current operand is another operand or an open parenthesis
                // invalid string
                {
                    return 1;
                }
            }
            postfix += infix[i];
            // append the operand
        }
        else if (infix[i] == '(')
        // if the character is beginning of paranthesis, push the character on the operator stack
        {
            if (i+1 < infix.size())
            // checking validity
            // ensure that there is a value next to it
            // if the value next to it is NOT an operand or the NOT operator or is an empty paranthesis, it is invalid
            {
                if (testCh(infix[i], infix[i+1]))
                {
                    return 1;
                }
            }
            else
            {
                return 1;
            }
            countP++;
            // create a counter for the number of open paranthesis
            S_operator.push(infix[i]);
        }
        else if (infix[i] == ')')
        // if the character is the end of paranthesis, pop the stack until matching '('
        {
            if (countP == 0)
            // if the closing paranthesis has no matching open paranthesis, invalid
            {
                return 1;
            }
            if (i+1 < infix.size())
            // if there is more characters next to this closing paranthesis, make sure it's valid
            {
                if (testCh(infix[i], infix[i+1]))
                // if the value next to it is not an operand or !, invalid
                {
                    return 1;
                }
            }
            countP--;
            // decrement the open paranthesis count since the closing one has a match
            while(!S_operator.empty() && S_operator.top() != '(')
            // while the top of the stack is not '('
            // append the stack top to postfix and pop the stack
            {
                postfix += S_operator.top();
                S_operator.pop();
            }
            S_operator.pop();
            // remove '('
        }
        else if (infix[i] == '^' || infix[i] == '&' || infix[i] == '!')
        // if we get an operator 
        {
            int ch, top;
            ch = helper(infix[i]);
            // use the helper function to convert the current character into a numeric value for comparison
            if (!S_operator.empty())
            // if the operator stack is not empty, make the top operator a numeric value for comparison 
            {
                top = helper(S_operator.top());
            }

            if (i+1 < infix.size())
            // checking validity for the operator
            // if there is a value next to it and is not an operand, ( or !, invalid
            {
                if (testCh(infix[i], infix[i+1]))
                {
                    return 1;
                }
            }
            else
            {
                return 1;
            }

            if (infix[i] == '!')
            // handling special cases of ! for converting it into postfix
            {
                int pfTop = postfix.size() - 1;
                // value to get the first value of the postfix
                // before we can add ! into postfix, we must ensure that there is an operand on top of it 
                while (!S_operator.empty() && !(pfTop < 0) && (S_operator.top() == '!' && (postfix[pfTop] == 'F' || postfix[pfTop] == 'T')))
                // check to see if there is another !, and a valid postfix to add on 
                {
                    postfix += S_operator.top();
                    S_operator.pop();
                }
            }
            else 
            // add the binary operators 
            {
                while (!S_operator.empty() && S_operator.top() != '(' && ch <= top)
                // adding the operator into the postfix 
                {
                    postfix += S_operator.top();
                    S_operator.pop();
                    if (!S_operator.empty())
                    {
                        top = helper(S_operator.top());
                    }
                    // use the helper function to ensure precedence values 
                }
            }
            S_operator.push(infix[i]);
            // if the operator stack is empty, add in the operator
        }
    }

    while(!S_operator.empty())
    // add the rest into postfix
    {
        postfix += S_operator.top();
        S_operator.pop();
    }
    
    if (postfix.empty() || countP != 0)
    // if postfix is empty (paranthesis case) or countP is not 0 (mismatching paranthesis), invalid string
    {
        return 1;
    }

    stack<char> S_operand;
    char operand2;
    char operand1;

    // evaluating the postfix 
    for(int i = 0; i < postfix.size() && postfix.size() != 0; i++)
    {
        if (postfix[i] == 'T' || postfix[i] == 'F')
        // if we get an operand, put it in the operand stack
        {
            S_operand.push(postfix[i]);
        }
        else if (!S_operand.empty() && postfix[i] == '!')
        // if we get a !, take the operand's first value and input the opposite value into it 
        {
            operand1 = S_operand.top();
            S_operand.pop();
            if (operand1 == 'T')
            {
                S_operand.push('F');
            }
            else
            {
                S_operand.push('T');
            }
        }
        else if (!S_operand.empty() && (postfix[i] == '^' || postfix[i] == '&'))
        // if we get a ^, take the two operands from the stack
        {  
            operand2 = S_operand.top();
            S_operand.pop();
            operand1 = S_operand.top();
            S_operand.pop(); 

            bool op2, op1, r;
            
            op2 = assignCh(operand2);
            op1 = assignCh(operand1);
            // assign values for evaluation 
            r = evalOp(postfix[i], op2, op1);
            // if the operator is ^, means or so if op2 and op1 are the same, it's false due to exclusitivity
            // else if you are using &, use the && function as so
            if (r)                
            {
                S_operand.push('T');
            }
            else
            {
                S_operand.push('F');
            }
            // determine what values to push onto the stack
        }
    }
    result = (!S_operand.empty() && S_operand.top() == 'T');
    // return the evaluated result
    S_operand.pop();
    return !S_operand.empty();
    // S_operand should be empty, if it's not empty, then the function would return 1 and is invalid
        // final check 
    // 0 false, 1 true 
    // 0 if invalid, 1 valid 
}

int helper(char x)
// helper function to label !, & and ^ to create precedence
{
    int z;
    if (x == '!')
    {
        z = 2;
    }
    else if (x == '&')
    {
        z = 1;
    }
    else if (x == '^')
    {
        z = 0;
    }

    return z;
}

bool testCh(char x, char y)
{
    bool z;
    if (x == 'T' || x == 'F')
    {
        z = !(y != 'T' && y != 'F' && y != '(');
    }
    else if (x == '(')
    {
        z = (y != '!' && y != 'T' && y != 'F' && y != '(');
    }
    else if (x == ')')
    {
        z = (y != '^' && y != '&' && y != ')');
    }
    else if (x == '^' || x == '&' || x == '!')
    {
        z = (y != '(' && y != 'T' && y != 'F' && y != '!');
    }

    return z;
}

bool assignCh(char x)
{
    if (x == 'T')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool evalOp(char x, bool op2, bool op1)
{
    bool result;
    if (x == '^')
    {
        if (op2 != op1)
        {
            result = op2 || op1;
        }
        else
        {
            result = false;
        }
    }
    else if (x == '&')
    {
        result = op2 && op1;
    }
    
    return result;
}

int main()
{
	string pf;
    bool answer;
    assert(evaluate("!T", pf, answer) == 0 && pf == "T!" && !answer);
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
                           &&  pf == "FF!TF&&^"  &&  !answer);             
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
	assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
	cout << "Passed all tests" << endl;
}
