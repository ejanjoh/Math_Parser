/*******************************************************************************
 *
 *      Autor:      Jan Johansson (ejanjoh)
 *      Copyright:  Copyright (c) 2017 Jan Johansson (ejanjoh)
 *      Created:    2017-04-04
 *      Updated:
 *
 *      Project:    Calculate Matematical Expression (Math_Parser)
 *      File name:  main.cpp
 *
 *
 *      Version history mapped on changes in this file:
 *      -----------------------------------------------
 *      ver 1       Created
 *
 *
 *      Reference: Shunting-yard algorithm https://en.m.wikipedia.org/wiki/Shunting-yard_algorithm
 *                 Reverse Polish notation https://en.m.wikipedia.org/wiki/Reverse_Polish_notation
 *
 ******************************************************************************/

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <typeinfo>
#include <stack>
#include <vector>
#include "token.hpp"
#include "localexcept.hpp"
#include "gramma.hpp"


using namespace std;


static unsigned long RemoveWhite(const string& str_in, string& str_out);
static void Tokenize(const char *str, TokenList& toklist) throw (overflow_error, runtime_error);
static unsigned int GetNextToken(const char *str, unsigned int index, char *tok) throw (overflow_error);
static void ShuttingYard(TokenList& tokenList, TokenList& outputList) throw (out_of_range, SortingError);
static int Calculate(TokenList& reversedList) throw (overflow_error, invalid_argument);
static void DisplayResult(TokenList& tokenList, bool comma = false) throw (logic_error);


int main(int argc, const char * argv[]) {
    
    try {
        TokenList tokenList, reversedList;
        string expr;
        double result;
        
        if (2 != argc) {
            throw invalid_argument("CalcMathExpr takes one argument only...");
        }
        
        RemoveWhite(argv[1], expr);
        Tokenize(expr.c_str(), tokenList);
        CheckGramma(0, tokenList.GetNbrTokens() - 1, tokenList);
        ShuttingYard(tokenList, reversedList);
        result = Calculate(reversedList);
        
        //DisplayResult(reversedList, true);    // Show the result of the Shutting Yard algorithm
        DisplayResult(tokenList);
        cout << result << endl;
        
    }
    catch (exception &e) {
        cout << typeid(e).name() << ": " << e.what() << endl;
        cout << "program terminating" << endl;
    }
    catch (...) {
        cout << "program terminating due to unexpected exception" << endl;
    }
    return 0;
}


static unsigned long RemoveWhite(const string& str_in, string& str_out)
{
    for (unsigned int i = 0; i < str_in.length(); i++) {
        if (' ' != str_in.at(i) and '\t' != str_in.at(i)) {
            str_out += str_in.at(i);
        }
    }
    
    // don't use remove_if(...); it just moves the whites to the end on the string and then...
    
    return str_out.length();
}


static void Tokenize(const char *str, TokenList& toklist) throw (overflow_error, runtime_error)
{
    char tok[TOKEN_SIZE + 1];
    unsigned int i = 0;
    
    while(1) {
        if ('\0' == str[i]) {
            break;
        }
        
        i += GetNextToken(str, i, tok);
        
        switch (tok[0]) {
            case '(':
                toklist.Add(tok, eLParent);
                break;
            case ')':
                toklist.Add(tok, eRParent);
                break;
            case '*':
                toklist.Add(tok, eMult);
                break;
            case '+':
                toklist.Add(tok, eAdd);
                break;
            case '-':
                toklist.Add(tok, eSubtr);
                break;
            case '/':
                toklist.Add(tok, eDiv);
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                toklist.Add(tok, eNumber, atoi(tok));
                break;
            default:
                throw runtime_error("unknown token in Tokenize");
                ;
        }   // switch...
    }   // for...

    return;
}


static unsigned int GetNextToken(const char *str, unsigned int index, char *tok) throw (overflow_error)
{
    unsigned int t = 0;
    
    if ('0' <= str[index] and str[index] <='9') {
        while('0' <= str[index + t] and str[index + t] <='9') {
            tok[t] = str[index + t];
            t++;
            if (TOKEN_SIZE == t) {
                throw overflow_error("overflow in GetNextToken");
            }
        }
    }
    else {
        tok[t] = str[index + t];
        t++;
    }
    tok[t] = '\0';
    
    return t;
}


// NOTE:
// To increase performance this fuction and Calculate should be merged. ShuttingYard involves a lot of
// copying (not needed). Keep it if you want the expression in a Reverse Polish Notation (i.e. in postfix notation)...
static void ShuttingYard(TokenList& tokenList, TokenList& outputList) throw (out_of_range, SortingError)
{
    const unsigned int nbrTokens = tokenList.GetNbrTokens();
    stack<Token*> operatorStack;
    
    for (unsigned int i = 0; i < nbrTokens; i++) {
        tokentype_t type = tokenList[i]->GetTokenType();
        unsigned int sortOperator = 0;
        
        switch (type) {
            case eNumber:
                outputList.Add(".", tokenList[i]->GetTokenType(), (dynamic_cast<TokenNumber*>(tokenList[i]))->GetNumber());
                break;
            case eAdd:
            case eSubtr:
            case eMult:
            case eDiv:
                sortOperator = 1;
                
                while (sortOperator) {
                    if (operatorStack.empty()) {
                        operatorStack.push(tokenList[i]);
                        sortOperator = 0;
                    }
                    else if (eLParent == operatorStack.top()->GetTokenType()) {
                        operatorStack.push(tokenList[i]);
                        sortOperator = 0;
                    }
                    else if (type > operatorStack.top()->GetTokenType()) {
                        operatorStack.push(tokenList[i]);
                        sortOperator = 0;
                    }
                    else {
                        outputList.Add(".", operatorStack.top()->GetTokenType());
                        operatorStack.pop();
                    }
                }   // while
                break;
            case eLParent:
                operatorStack.push(tokenList[i]);
                break;
            case eRParent:
                sortOperator = 1;
                
                while (sortOperator) {
                    if (operatorStack.empty()) {
                        throw SortingError("sorting error in ShuttingYard(2)");
                    }
                    else if (eLParent == operatorStack.top()->GetTokenType()) {
                        operatorStack.pop();
                        sortOperator = 0;
                    }
                    else {
                        outputList.Add(".", operatorStack.top()->GetTokenType());
                        operatorStack.pop();
                    }
                }   // while
                break;
            default:
                throw SortingError("sorting error in ShuttingYard(1)");
                break;
        }   // switch
    }   // for
    
    
    while (!operatorStack.empty()) {
        outputList.Add(".", operatorStack.top()->GetTokenType());
        operatorStack.pop();
    }
    
    return;
}


static int Calculate(TokenList& reversedList) throw (overflow_error, invalid_argument)
{
    const unsigned int nbrTokens = reversedList.GetNbrTokens();
    unsigned int nbrLastNumbers = 0;
    double op1, op2;
    tokentype_t type;
    vector<double> output;
    
    for (unsigned int i = 0; i < nbrTokens; i++) {
        type = reversedList[i]->GetTokenType();
        switch (type) {
            case eNumber:
                output.push_back((dynamic_cast<TokenNumber*>(reversedList[i]))->GetNumber());
                nbrLastNumbers++;
                break;
            case eAdd:
            case eSubtr:
            case eMult:
            case eDiv:
                if (2 <= nbrLastNumbers) {      // all operators in this case are binary...
                    nbrLastNumbers--;           // the netto of this operation(s) is -1...
                    op1 = output.back();
                    output.pop_back();
                    op2 = output.back();
                    output.pop_back();
                    
                    if (eAdd == type) output.push_back(op2+op1);
                    else if (eSubtr == type) output.push_back(op2-op1);
                    else if (eMult == type) output.push_back(op2*op1);
                    else {
                        if (0 == op1) {
                            throw overflow_error("division by zero in Calculate");
                        }
                        output.push_back(op2/op1);
                    }
                }
                else {
                    throw invalid_argument("invalid argument in Calculate(2)");
                }
                break;
            default:
                throw invalid_argument("invalid argument in Calculate(1)");
                break;
        }   // switch
    }   // if
    
    if (1 != output.size()) {
        throw invalid_argument("invalid argument in Calculate(3)");
    }
    
    return int(output[0]);
}


static void DisplayResult(TokenList& tokenList, bool comma) throw (logic_error)
{
    const unsigned int nbrTokens = tokenList.GetNbrTokens();
    
    
    if (comma) {
        cout << '[';
    }
    
    for (unsigned int i = 0; i < nbrTokens; i++) {
        switch (tokenList[i]->GetTokenType()) {
            case eNumber:
                cout << (dynamic_cast<TokenNumber*>(tokenList[i]))->GetNumber();
                break;
            case eAdd:
                cout << '+';
                break;
            case eSubtr:
                cout << '-';
                break;
            case eMult:
                cout << '*';
                break;
            case eDiv:
                cout << '/';
                break;
            case eLParent:
                cout << '(';
                break;
            case eRParent:
                cout << ')';
                break;
            default:
                throw logic_error("can't print the expression");
                break;
        }   // switch
                
        
        if (comma and i != (nbrTokens - 1)) {
            cout << ", ";
        }
        else if (comma and i == (nbrTokens - 1)) {
            cout << ']' << endl;
        }// else if
        
    }   // for
    
    if (!comma) {
        cout << " = ";
    }
    return;
}











