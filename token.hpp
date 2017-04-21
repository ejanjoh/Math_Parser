/*******************************************************************************
 *
 *      Autor:      Jan Johansson (ejanjoh)
 *      Copyright:  Copyright (c) 2017 Jan Johansson (ejanjoh)
 *      Created:    2017-04-05
 *      Updated:
 *
 *      Project:    Calculate Matematical Expression (Math_Parser)
 *      File name:  token.hpp
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

#ifndef token_hpp
#define token_hpp


#include <iostream>
#include <cstring>
#include <stdexcept>
#include <typeinfo>
using namespace std;


#define TOKEN_LIST_SIZE 128
#define TOKEN_SIZE 16


// Note: keep the order due to precedence (needed in the Shutting-Yard algorithm...)
typedef enum {eUninit = 0, eUnknown, eNumber, eSubtr, eAdd, eDiv, eMult, eLParent, eRParent} tokentype_t;


class Token;
class TokenNumber;
class TokenList;


class Token {
public:
    Token();
    Token(const char *str, tokentype_t type);
    Token(const Token& tok);
    //~Token();
    
    const Token& operator= (const Token& tok);
    
    virtual const string GetToken(void) const;
    virtual const tokentype_t GetTokenType(void) const;
    
protected:
    string token;
    tokentype_t tokenType;
};

inline Token::Token(): token("\0"), tokenType(eUninit) {}
inline Token::Token(const char *str, tokentype_t type): token(str), tokenType(type) {}
inline Token::Token(const Token& tok):token(tok.token), tokenType(tok.tokenType) {}
inline const string Token::GetToken(void) const { return token;}    // use with care, involvs copying of a string...
inline const tokentype_t Token::GetTokenType(void) const {return tokenType;}


class TokenNumber: public Token {
public:
    TokenNumber();
    TokenNumber(const char *str, tokentype_t type, double nbr);
    TokenNumber(const TokenNumber& tokNbr);
    //~TokenNumber();
    
    const TokenNumber& operator= (const TokenNumber& tokNbr);
    
    virtual const string GetToken(void) const;
    virtual const tokentype_t GetTokenType(void) const;
    virtual const double GetNumber(void) const;
    
protected:
    double number;
};

inline TokenNumber::TokenNumber(): Token(), number(0) {}
inline TokenNumber::TokenNumber(const char *str, tokentype_t type, double nbr): Token(str,type), number(nbr) {}
inline TokenNumber::TokenNumber(const TokenNumber& tokNbr):Token(dynamic_cast<const Token&>(tokNbr)), number(tokNbr.number) {}
inline const double TokenNumber::GetNumber(void) const {return number;}


class TokenList {
public:
    TokenList();
    virtual ~TokenList();
    
    Token *operator[] (unsigned int index);
    
    void Add(const char *str, tokentype_t type, double nbr = 0) throw (out_of_range);
    unsigned int GetNbrTokens(void) const;
    
private:
    Token *tokenList[TOKEN_LIST_SIZE];
    unsigned int cnt;
};

inline Token *TokenList::operator[] (unsigned int index) { return tokenList[index]; }
inline unsigned int TokenList::GetNbrTokens(void) const {return cnt;}



#endif /* token_hpp */
