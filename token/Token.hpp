//
// Created by michto on 30.05.16.
//

#ifndef TKOM_TOKEN_HPP
#define TKOM_TOKEN_HPP


#include <string>
#include "TokenType.h"

class Token {
private:
    std::string value;
    TokenType tokenType;
public:

    virtual ~Token() { }

    Token(const std::string &value, TokenType tokenType) : value(value), tokenType(tokenType) { }

    Token(TokenType tokenType) : tokenType(tokenType), value("") { }

    const std::string &getValue() const {
        return value;
    }

    void setValue(const std::string &value) {
        Token::value = value;
    }

    TokenType getTokenType() const {
        return tokenType;
    }

    void setTokenType(TokenType tokenType) {
        Token::tokenType = tokenType;
    }
};


#endif //TKOM_TOKEN_HPP
