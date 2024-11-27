#include <iostream>
#include <cstring>
#include "token.h"
#include "scanner.h"

using namespace std;

// EL scanner solo maneja token si individuales
Scanner::Scanner(const char *s) : input(s), first(0), current(0) {}

bool is_white_space(char c)
{
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

Token *Scanner::nextToken()
{
    Token *token;
    // Ignorar espacios en blanco
    while (current < input.length() && is_white_space(input[current]))
        current++;
    if (current >= input.length())
        return new Token(Token::END);

    char c = input[current];
    first = current;

    // Números
    if (isdigit(c))
    {
        current++;
        while (current < input.length() && isdigit(input[current]))
            current++;
        token = new Token(Token::NUM, input, first, current - first);
    }

    // Identificadores y palabras clave
    else if (isalpha(c))
    {
        current++;
        while (current < input.length() && (isalnum(input[current]) || input[current] == '!'))
            current++;
        string word = input.substr(first, current - first);

        // Declaracion variables
        if (word == "let")
            token = new Token(Token::VAR, word, 0, word.length());
        else if (word == "mut")
            token = new Token(Token::MUT, word, 0, word.length());

        // Condicional
        else if (word == "if")
            token = new Token(Token::IF, word, 0, word.length());
        else if (word == "else")
            token = new Token(Token::ELSE, word, 0, word.length());

        // Print
        else if (word == "println!")
            token = new Token(Token::PRINT, word, 0, word.length());

        // Funcion
        else if (word == "fn")
            token = new Token(Token::FUN, word, 0, word.length());

        else if (word == "return")
            token = new Token(Token::RETURN, word, 0, word.length());
        // Bucles
        else if (word == "for")
        {
            token = new Token(Token::FOR, word, 0, word.length());
        }
        else if (word == "in")
        {
            token = new Token(Token::IN, word, 0, word.length());
        }
        // Main
        else if (word == "main")
            token = new Token(Token::ID, word, 0, word.length()); // Puede tener un tipo específico

        // Tipo
        else if (word == "i32" || word == "i64")
            token = new Token(Token::TYPE, word, 0, word.length());

        else
            token = new Token(Token::ID, word, 0, word.length());
    }

    // Cadenas de texto
    else if (c == '"')
    {
        current++;
        while (current < input.length() && input[current] != '"')
            current++;
        if (current < input.length())
            current++; // Cierra la cadena
        token = new Token(Token::STRING, input, first, current - first);
    }

    // Comentarios
    else if (c == '/')
    {
        if (current + 1 < input.length() && input[current + 1] == '/')
        {
            // Comentario de línea
            current += 2;
            while (current < input.length() && input[current] != '\n')
                current++;
            cout << "COMMENT" << endl;
            return nextToken();
        }
        else
        {
            current++;
            token = new Token(Token::DIV, c);
        }
    }

    // Operadores y delimitadores
    else if (strchr("+-*/()=;,<>{}:.", c))
    {
        switch (c)
        {
        case '+':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::PLUS_ASSIGN, "+=", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::PLUS, c);
            }
            break;
        case '-':
            if (current + 1 < input.length() && input[current + 1] == '>') 
            {
                token = new Token(Token::ARROW, "->", 0, 2); 
                current++;                                   
            }
            else
            {
                token = new Token(Token::MINUS, c); // Token para '-'
            }
            break;
        case '*':
            token = new Token(Token::MUL, c);
            break;
        case '/':
            token = new Token(Token::DIV, c);
            break;
        case ',':
            token = new Token(Token::COMA, c);
            break;
        case '(':
            token = new Token(Token::PI, c);
            break;
        case ')':
            token = new Token(Token::PD, c);
            break;
        case '{':
            token = new Token(Token::LBRACE, c);
            break;
        case '}':
            token = new Token(Token::RBRACE, c);
            break;
        case ':':
            token = new Token(Token::COLON, c);
            break;
        case '.':
            if (current + 1 < input.length() && input[current + 1] == '.')
            {
                current++;
                token = new Token(Token::RANGE, "..", 0, 2);
            }
            else
            {

                token = new Token(Token::ERR, c);
            }
            break;

        case '=':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::EQ, "==", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::ASSIGN, c);
            }
            break;
        case '<':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::LE, "<=", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::LT, c);
            }
            break;
        case '>':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::GE, ">=", 0, 2); // "Greater or Equal"
                current++;
            }
            else
            {
                token = new Token(Token::GT, c); // "Greater Than"
            }
            break;

        case ';':
            token = new Token(Token::PC, c);
            break;
        default:
            token = new Token(Token::ERR, c);
        }
        current++;
    }

    // Error para caracteres desconocidos
    else
    {
        token = new Token(Token::ERR, c);
        current++;
    }
    return token;
}

void Scanner::reset()
{
    first = 0;
    current = 0;
}

Scanner::~Scanner() {}

void test_scanner(Scanner *scanner)
{
    Token *current;
    cout << "Iniciando Scanner:" << endl
         << endl;
    while ((current = scanner->nextToken())->type != Token::END)
    {
        if (current->type == Token::ERR)
        {
            cout << "Error en scanner - carácter inválido: " << current->text << endl;
            break;
        }
        else
        {
            cout << *current << endl;
        }
        delete current;
    }
    cout << "TOKEN(END)" << endl;
    delete current;
}