/*******************************************************************************
 *
 *      Autor:      Jan Johansson (ejanjoh)
 *      Copyright:  Copyright (c) 2017 Jan Johansson (ejanjoh)
 *      Created:    2017-04-07
 *      Updated:
 *
 *      Project:    Calculate Matematical Expression (Math_Parser)
 *      File name:  gramma.cpp
 *
 *
 *      Version history mapped on changes in this file:
 *      -----------------------------------------------
 *      ver 1       Created
 *
 *
 *      Reference: 
 *
 ******************************************************************************/

#include "gramma.hpp"


static unsigned int IsExpression(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError);
static unsigned int IsTerm(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError);
static unsigned int IsOperator(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError);
static unsigned int IsNumber(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError);
static unsigned int IsPhrase(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError);


void CheckGramma(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError)
{
    unsigned int next;
    
    if (first > last) {
        throw GrammaError("syntax error (CheckGramma(1))");
    }
    
    next = IsExpression(first, last, tokenList);
    
    if (next != (last + 1)) {
        throw GrammaError("syntax error (CheckGramma(2))");
    }
     
    return;
}


static unsigned int IsExpression(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError)
{
    unsigned int next;
    
    if (first > last) {
        throw GrammaError("syntax error (IsExpression(1))");
    }
    
    next = IsTerm(first, last, tokenList);
    
    while (next < last) {
        next = IsOperator(next, last, tokenList);
        next = IsTerm(next, last, tokenList);
    }
    
    return next;
}


static unsigned int IsTerm(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError)
{
    unsigned int next;
    
    if (first > last) {
        throw GrammaError("syntax error (IsTerm(1))");
    }
    
    switch (tokenList[first]->GetTokenType()) {
        case eNumber:
            next = IsNumber(first, last, tokenList);
            break;
        case eLParent:
            next = IsPhrase(first, last, tokenList);
            break;
        default:
            throw GrammaError("syntax error (IsTerm(2))");
            break;
    }
    
    return next;
}


static unsigned int IsOperator(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError)
{
    if (first > last) {
        throw GrammaError("syntax error (IsOperator(1))");
    }
    
    switch (tokenList[first]->GetTokenType()) {
        case eAdd:
        case eSubtr:
        case eMult:
        case eDiv:
            break;
        default:
            throw GrammaError("syntax error (IsOperator(2))");
            break;
    }
    
    return first + 1;
}


static unsigned int IsNumber(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError)
{
    if (first > last) {
        throw GrammaError("syntax error (IsNumber(1))");
    }
    
    if (eNumber != tokenList[first]->GetTokenType()) {
        throw GrammaError("syntax error (IsNumber(2))");
    }
    
    return first + 1;
}


static unsigned int IsPhrase(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError)
{
    unsigned int cnt = 0, d = 0;
    
    if (first > last) {
        throw GrammaError("syntax error (IsPhrase(1))");
    }
    
    while (1) {
        if (eLParent == tokenList[first + d]->GetTokenType()) cnt++;
        else if (eRParent == tokenList[first + d]->GetTokenType()) cnt--;
        
        if (0 == cnt) break;
        d++;
        if (last < (first + d)) {
            throw GrammaError("syntax error (IsPhrase(2))");
        }
    }
    
    if (d > 1) {
        IsExpression(first + 1, first + d - 1, tokenList);
    }
    
    return first + d + 1;
}




