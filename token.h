#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
public:
    enum Type
    {
        PLUS,
        MINUS,
        MUL,
        DIV,
        NUM,
        ERR,
        PD,
        PI,
        END,
        ID,
        PRINT,
        ASSIGN,
        PC,
        LT,
        LE,
        GE,
        GT,
        EQ,
        IF,
        THEN,
        ELSE,
        ENDIF,
        WHILE,
        DO,
        ENDWHILE,
        COMA,
        IFEXP,
        VAR,
        FOR,
        ENDFOR,
        TRUE,
        FALSE,
        RETURN,
        FUN,
        ENDFUN,
        LBRACE,
        RBRACE,
        MUT,
        TYPE,
        COLON,
        RANGE ,
        STRING,
        IN,
        PLUS_ASSIGN,
        ARROW
    };

    Type type;
    std::string text;

    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const std::string &source, int first, int last);

    friend std::ostream &operator<<(std::ostream &outs, const Token &tok);
    friend std::ostream &operator<<(std::ostream &outs, const Token *tok);
};

#endif // TOKEN_H