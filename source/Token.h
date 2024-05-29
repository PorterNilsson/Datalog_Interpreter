#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::cout;
using std::stringstream;

enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOF_TYPE,
};

class Token
{
private:
    string tokenString = "";
    int lineNumber = 0;
    TokenType tokenType;

public:
    Token(TokenType type, std::string description, int line);

    string ToString();
    string GetTokenString();
    string TokenTypeToString(TokenType type);

    TokenType GetTokenType();
};

#endif // TOKEN_H

