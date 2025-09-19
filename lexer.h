#pragma once
#include <vector>
#include <string>
#include <unordered_set>

enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_ASSIGN,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_FUNCTION,
    TOKEN_BRACKET,
    TOKEN_SEMICOLON,
    TOKEN_DELIMITER,
    TOKEN_COMMENT,
    TOKEN_LITERAL,
    TOKEN_UNKNOWN,
    TOKEN_EOF
};


struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize(const std::string& code);
bool isKeyword(const std::string& word);