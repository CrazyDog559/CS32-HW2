//
//  eval.cpp
//  HW2
//
//  Created by Drew Wan on 4/29/23.
//


#include <iostream>
#include <stack>
#include <cassert>

using namespace std;

bool isValid(string str) {
    if (str.size() == 0) {
        return false;
    } else if (str.size() == 1 && str[0] == ' ') {
        return false;
    } else {
        int numP = 0;
        char prev = ' ';
        for (int i = 0; i < str.size(); i++) {
            //cout << prev << endl;
            if (prev == ' ') {
                //cout << 1 << endl;
                prev = str[i];
            } else {
                if (prev == '(' || prev == '!') {
                    if (prev == '(') {
                        numP++;
                    }
                    if (str[i] != 'T' && str[i] != 'F' && str[i] != '(' && str[i] != ' ') {
                        return false;
                    }
                        
                } else if (prev == ')') {
                    numP++;
                    if (str[i] != '&' && str[i] != '^' && str[i] != ' ' && str[i] != ')') {
                        return false;
                    }
                        
                } else if (prev == 'T' || prev == 'F') {
                    if (str[i] != ')' && str[i] != '&' && str[i] != '^' && str[i] != ' ') {
                        return false;
                    }
                        
                } else if (prev == '^' || prev == '&') {
                    if (str[i] != '(' && str[i] != 'T' && str[i] != 'F' && str[i] != '!' && str[i] != ' ') {
                        return false;
                    }
                        
                } else {
                    return false;
                }
                    
                if(str[i] != ' ') {
                    prev = str[i];
                }
            
                    
            }

        }
        if (str[str.size() - 1] == ')'){
            numP++;
        }
        if (prev == ' ') {
            return false;
        }
        return (prev == ' ' || prev == 'T' || prev == 'F' || prev == ')') && numP % 2 == 0;
    }
}

bool higherPrec(char i, char j) {
    if (i == '!') {
        return true;
    } else if (j == '!') {
        return false;
    } else if (i == '&') {
        return j != '!';
    } else {
        return j == '^';
    }
}

char eval(char op1, char op2, char op) {
    if (op == '&') {
        if (op1 == 'T' && op2 == 'T') {
            return 'T';
        } else {
            return 'F';
        }
            
    } else {
        if(op1 == 'T' || op2 == 'T') {
            return 'T';
        } else {
            return 'F';
        }
            
    }
}



int evaluate(string infix, string& postfix, bool& result)
{
    if (!isValid(infix)) {
        //cout << "hola" << endl;
        return 1;
    }

    stack<char> charStack;
    
    postfix = "";
    for (int i = 0; i < infix.length(); i++) {
        switch (infix[i]) {
        case 'T':
        case 'F':
            postfix += infix[i];
            break;

        case '(':
           
            charStack.push(infix[i]);
            break;

        case ')':
            
            while (charStack.top() != '(') {
                
                postfix += charStack.top();
                charStack.pop();
            }
            
            charStack.pop();
            break;
        case '^':
        case '&':
        case '!':
            while (!charStack.empty() && charStack.top() != '(' && !higherPrec(infix[i], charStack.top())) {
                
                postfix += charStack.top();
                charStack.pop();
            }
            charStack.push(infix[i]);
            break;
      
        }
    }
    while (!charStack.empty()) {
        
        postfix += charStack.top();
        charStack.pop();
    }

    stack <char> opStack;
    
    for (int i = 0; i < postfix.length(); i++) {
        if (postfix[i] == 'T' || postfix[i] == 'F') {
            opStack.push(postfix[i]);
        } else if (postfix[i] == '!') {
            char curr = opStack.top();
            opStack.pop();
            if(curr == 'T') {
                opStack.push('F');
            } else {
                opStack.push('T');
            }
                
        } else {
            char op2 = opStack.top();
            opStack.pop();
            char op1 = opStack.top();
            opStack.pop();
            char balanced = eval(op1, op2, postfix[i]);
            opStack.push(balanced);
        }
    }
    
        result = opStack.top() == 'T';
        return 0;
   
}




int main() {
    string pf;
    bool answer;
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
    
    assert(evaluate("bruh", pf, answer) == 1);
    assert(evaluate("1^F", pf, answer) == 1);
    assert(evaluate("!()", pf, answer) == 1);
    assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate("(F)", pf, answer) == 0 && pf == "F" && !answer);
    
    
    
    assert(evaluate("(T))", pf, answer) == 1);
    
    assert(evaluate("(  )", pf, answer) == 1);
    
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("  ", pf, answer) == 1);
}





//int evaluate(string infix, string& postfix, bool& result) {
//
//    postfix = "";
//    stack<char> opStack;
//
//    for(int i = 0; i < infix.size(); i++) {
//        switch(infix[i]) {
//            case 'T':
//            case 'F':
//                postfix += infix[i];
//                break;
//            case '(':
//                opStack.push(infix[i]);
//                break;
//            case ')':
//                while (opStack.top() != '(') {
//                    postfix += opStack.top();
//                    opStack.pop();
//                }
//                opStack.pop();
//                break;
//            case '|':
//            case '&':
//            case '!':
//                while (!opStack.empty() && opStack.top() != '(' && )
//
//
//        }
//    }
//    while(!opStack.empty()) {
//        postfix += opStack.top();
//        opStack.pop();
//    }
//}

//int operandNum(string str) {
//    int count = 0;
//    for (int i = 0; i < str.size(); i++) {
//        if (str[i] == 'T' || str[i] == 'F') {
//            count++;
//        }
//
//    }
//    return count;
//}
    


