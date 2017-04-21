/*******************************************************************************
 *
 *      Autor:      Jan Johansson (ejanjoh)
 *      Copyright:  Copyright (c) 2017 Jan Johansson (ejanjoh)
 *      Created:    2017-04-05
 *      Updated:
 *
 *      Project:    Calculate Matematical Expression (Math_Parser)
 *      File name:  token.cpp
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

#include "token.hpp"



// ===== class Token =====

const Token& Token::operator= (const Token& tok)
{
    token = tok.token;
    tokenType = tok.tokenType;
    return *this;
}


// ===== class TokenNumber =====

const TokenNumber& TokenNumber::operator= (const TokenNumber& tokNbr)
{
    token = tokNbr.token;
    tokenType = tokNbr.tokenType;
    number = tokNbr.number;
    return *this;
}


const string TokenNumber::GetToken(void) const
{
    // use with care, involvs copying of a string....
    return Token::GetToken();
}


const tokentype_t TokenNumber::GetTokenType(void) const
{
    return Token::GetTokenType();
}


// ===== class TokenList =====

TokenList::TokenList()
{
    cnt = 0;
    for (unsigned int i = 0; i < TOKEN_LIST_SIZE; i++) {
        tokenList[i] = NULL;
    }
}


TokenList::~TokenList()
{
    for (unsigned int i = 0; i < cnt; i++) {
        delete tokenList[i];
    }
}


void TokenList::Add(const char *str, tokentype_t type, double nbr) throw (out_of_range)
{
    if (TOKEN_LIST_SIZE <= cnt) {
        throw out_of_range("cnt out of range in TokenList::Add");
    }
    
    if (eNumber == type) {
        tokenList[cnt] = new TokenNumber(str, type, nbr);
        cnt++;
    }
    else {
        tokenList[cnt] = new Token(str, type);
        cnt++;
    }

    return;
}




