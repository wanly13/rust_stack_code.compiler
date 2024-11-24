#include <iostream>
#include "token.h"

using namespace std;

Token::Token(Type type):type(type) { text = ""; }

Token::Token(Type type, char c):type(type) { text = string(1, c); }

Token::Token(Type type, const string& source, int first, int last):type(type) {
    text = source.substr(first, last);
}

std::ostream& operator << ( std::ostream& outs, const Token & tok )
{
    switch (tok.type) {
        case Token::PLUS: outs << "TOKEN(PLUS) -> " << tok.text ; break;
        case Token::MINUS: outs << "TOKEN(MINUS) -> " << tok.text; break;
        case Token::MUL: outs << "TOKEN(MUL) -> " << tok.text; break;
        case Token::DIV: outs << "TOKEN(DIV) -> " << tok.text; break;
        case Token::NUM: outs << "TOKEN(NUM) -> " << tok.text; break;
        case Token::ERR: outs << "TOKEN(ERR) -> " << tok.text; break;
        case Token::PD: outs << "TOKEN(PD) -> " << tok.text; break;
        case Token::PI: outs << "TOKEN(PI) -> " << tok.text; break;
        case Token::LBRACE: outs << "TOKEN(LBRACE) -> " << tok.text; break;
        case Token::RBRACE: outs << "TOKEN(RBRACE) -> " << tok.text; break;
        case Token::END: outs << "TOKEN(END) -> " << tok.text; break;
        case Token::ID: outs << "TOKEN(ID) -> " << tok.text; break;
        case Token::PRINT: outs << "TOKEN(PRINT) -> " << tok.text; break;
        case Token::ASSIGN: outs << "TOKEN(ASSIGN) -> " << tok.text; break;
        case Token::PC: outs << "TOKEN(PC) -> " << tok.text; break;
        case Token::LT: outs << "TOKEN(LT) -> " << tok.text; break;
        case Token::LE: outs << "TOKEN(LE) -> " << tok.text; break;
        case Token::GE: outs << "TOKEN(GE) -> " << tok.text; break;
        case Token::GT: outs << "TOKEN(GT) -> " << tok.text; break;
        case Token::EQ: outs << "TOKEN(EQ) -> " << tok.text; break;
        case Token::IF: outs << "TOKEN(IF) -> " << tok.text; break;
        case Token::THEN: outs << "TOKEN(THEN) -> " << tok.text; break;
        case Token::ELSE: outs << "TOKEN(ELSE) -> " << tok.text; break;
        case Token::ENDIF: outs << "TOKEN(ENDIF) -> " << tok.text; break;
        case Token::WHILE: outs << "TOKEN(WHILE) -> " << tok.text; break;
        case Token::COMA: outs << "TOKEN(COMA) -> " << tok.text; break;
        case Token::IFEXP: outs << "TOKEN(IFEXP) -> " << tok.text; break;
        case Token::DO: outs << "TOKEN(DO) -> " << tok.text; break;
        case Token::ENDWHILE: outs << "TOKEN(ENDWHILE) -> " << tok.text; break;
        case Token::VAR: outs << "TOKEN(VAR) -> " << tok.text; break;
        case Token::FOR : outs << "TOKEN(FOR) -> " << tok.text; break;
        case Token::ENDFOR : outs << "TOKEN(ENDFOR) -> " << tok.text; break;
        case Token::TRUE : outs << "TOKEN(TRUE) -> " << tok.text; break;
        case Token::FALSE : outs << "TOKEN(FALSE) -> " << tok.text; break;
        case Token::RETURN : outs << "TOKEN(RETURN) -> " << tok.text; break;
        case Token::FUN : outs << "TOKEN(FUN) -> " << tok.text; break;
        case Token::ENDFUN : outs << "TOKEN(ENDFUN) -> " << tok.text; break;
        case Token::MUT : outs << "TOKEN(MUT) -> " << tok.text; break;
        case Token::COLON : outs << "TOKEN(COLON) -> " << tok.text; break;
        case Token::TYPE : outs << "TOKEN(TYPE) -> " << tok.text; break;
        case Token::STRING : outs << "TOKEN(STRING) -> " << tok.text; break;
        case Token::RANGE : outs << "TOKEN(RANGE) -> " << tok.text; break;
        case Token::IN : outs << "TOKEN(IN) -> " << tok.text; break;
        case Token::PLUS_ASSIGN : outs << "TOKEN(PLUS_ASSIGN) -> " << tok.text; break;
        case Token::ARROW : outs << "TOKEN(ARROW) -> " << tok.text; break;
        default: outs << "TOKEN(UNKNOWN) -> " << tok.text; break;
    }
    return outs;
}

std::ostream& operator << ( std::ostream& outs, const Token* tok ) {
    return outs << *tok;
}