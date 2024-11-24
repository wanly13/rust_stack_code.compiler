#include <iostream>
#include <stdexcept>
#include "token.h"
#include "scanner.h"
#include "exp.h"
#include "parser.h"

using namespace std;
// Inicio del Programa
Program *Parser::parseProgram()
{
    VarDecList *v = parseVarDecList(); // Declaraciones de variables
    FunDecList *b = parseFunDecList(); // Declaraciones de funciones
    return new Program(v, b);
}

bool Parser::match(Token::Type ttype)
{
    if (check(ttype))
    {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype)
{
    if (isAtEnd())
        return false;
    return current->type == ttype;
}

bool Parser::advance()
{
    if (!isAtEnd())
    {
        Token *temp = current;
        if (previous)
            delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERR))
        {
            cout << "Error de análisis, carácter no reconocido: " << current->text << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd()
{
    return (current->type == Token::END);
}

Parser::Parser(Scanner *sc) : scanner(sc)
{
    previous = NULL;
    current = scanner->nextToken();
    if (current->type == Token::ERR)
    {
        cout << "Error en el primer token: " << current->text << endl;
        exit(1);
    }
}

VarDec *Parser::parseVarDec()
{
    VarDec *vd = NULL;
    cout << "parseVarDec" << *current << endl;
    if (match(Token::VAR))
    {
        if (!match(Token::MUT))
        {
            cout << "Error: se esperaba 'mut' después de 'let'." << endl;
            exit(1);
        }
        if (!match(Token::ID))
        {
            cout << "Error: se esperaba un identificador después de 'mut'." << endl;
            exit(1);
        }

        string varName = previous->text;

        if (!match(Token::COLON))
        {
            cout << "Error: se esperaba ':' después del identificador." << endl;
            exit(1);
        }

        if (!match(Token::TYPE))
        {
            cout << "Error: se esperaba un tipo después de ':'." << endl;
            exit(1);
        }
        string varType = previous->text;

        if (!match(Token::PC))
        {
            cout << "Error: se esperaba ';' al final de la declaración." << endl;
            exit(1);
        }
        vd = new VarDec(varName, varType, true);
    }

    return vd;
}

VarDecList *Parser::parseVarDecList()
{
    VarDecList *vdl = new VarDecList();
    VarDec *aux;
    aux = parseVarDec();
    while (aux != NULL)
    {
        vdl->add(aux);
        aux = parseVarDec();
    }
    return vdl;
}

StatementList *Parser::parseStatementList()
{
    StatementList *sl = new StatementList();
    sl->add(parseStatement());

    while (match(Token::PC))
    {
        sl->add(parseStatement());
    }

    return sl;
}

Body *Parser::parseBody()
{
    cout << "parseBody" << endl;
    if (!match(Token::LBRACE))
    {
        cout << "Error: se esperaba '{' al inicio del cuerpo." << endl;
        exit(1);
    }
    VarDecList *vdl = parseVarDecList();
    StatementList *sl = parseStatementList();
    /* if (!match(Token::RBRACE))
    {
        cout << "Error: se esperaba '}' al final del cuerpo." << endl;
        exit(1);
    } */
    return new Body(vdl, sl);
}

FunDec *Parser::parseFunDec()
{
    cout << "parseFunDec" << endl;
    FunDec *fd = NULL;
    if (match(Token::FUN))
    {

        if (!match(Token::ID))
        {
            cout << "Error: se esperaba un nombre de función después de 'fn'." << endl;
            exit(1);
        }
        string fname = previous->text;

        if (!match(Token::PI))
        {
            cout << "Error: se esperaba un '(' después del nombre de la función." << endl;
            exit(1);
        }

        list<string> types;
        list<string> vars;

        if (!check(Token::PD))
        {
            do
            {
                if (!match(Token::ID))
                {
                    cout << "Error: se esperaba un identificador para el nombre del parámetro." << endl;
                    exit(1);
                }
                string paramName = previous->text;

                if (!match(Token::COLON))
                {
                    cout << "Error: se esperaba ':' entre el nombre y el tipo del parámetro." << endl;
                    exit(1);
                }

                if (!match(Token::TYPE))
                {
                    cout << "Error: se esperaba un tipo después del ':'." << endl;
                    exit(1);
                }
                string paramType = previous->text;

                types.push_back(paramType);
                vars.push_back(paramName);

            } while (match(Token::COMA));
        }

        if (!match(Token::PD))
        {
            cout << "Error: se esperaba un ')' después de la lista de parámetros." << endl;
            exit(1);
        }

        string returnType = "";
        if (match(Token::ARROW)) // "->" para tipo de retorno
        {
            if (!match(Token::TYPE))
            {
                cout << "Error: se esperaba un tipo después de '->'." << endl;
                exit(1);
            }
            returnType = previous->text;
        }

        // Parsear el cuerpo de la función

        Body *body = parseBody();
        cout << "Despues." << *current << endl;

        // Crear la declaración de la función
        fd = new FunDec(fname, types, vars, returnType, body);
    }

    return fd;
}

FunDecList *Parser::parseFunDecList()
{
    FunDecList *fdl = new FunDecList();
    FunDec *aux;
    aux = parseFunDec();
    while (aux != NULL)
    {
        fdl->add(aux);
        aux = parseFunDec();
    }
    return fdl;
}

list<Stm *> Parser::parseStmList()
{
    list<Stm *> slist;
    slist.push_back(parseStatement());
    while (match(Token::PC))
    {
        slist.push_back(parseStatement());
    }
    return slist;
}

Stm *Parser::parseStatement()
{
    cout << "parseStatement" << endl;
    Stm *s = NULL;
    Exp *e = NULL;
    Body *tb = NULL; // true case
    Body *fb = NULL; // false case
    cout << "ACTUAL: " << *current << endl;
    if (current == NULL)
    {
        cout << "Error: Token actual es NULL" << endl;
        exit(1);
    }

    if (match(Token::ID))
    {

        string lex = previous->text;

        if (match(Token::ASSIGN))
        {
            e = parseCExp();
            s = new AssignStatement(lex, e);
        }
        else
        {
            if (match(Token::PI)) // Caso especial para el for
            {
                list<Exp *> args;
                if (!check(Token::PD))
                {
                    args.push_back(parseCExp());
                    while (match(Token::COMA))
                    {
                        args.push_back(parseCExp());
                    }
                }
                if (!match(Token::PD))
                {
                    cout << "Falta paréntesis derecho" << endl;
                    exit(0);
                }
                s = new FCallStatement(lex, args);
            }
        }
    }
    else if (match(Token::PRINT))
    {
        if (!match(Token::PI)) // Verifica que haya un '('
        {
            cout << "Error: se esperaba un '(' después de 'print'." << endl;
            exit(1);
        }
        list<Exp *> args;

        args.push_back(parseCExp());
        
        while (match(Token::COMA))
        {
            args.push_back(parseCExp());
        }

        if (!match(Token::PD))
        {
            cout << "Error: se esperaba un ')' después de la expresión." << endl;
            exit(1);
        }
        s = new PrintStatement(e);
    }
    else if (match(Token::IF))
    {

        e = parseCExp();

        tb = parseBody();

        if (match(Token::ELSE))
        {
            fb = parseBody();
        }
        s = new IfStatement(e, tb, fb);
    }
    else if (match(Token::WHILE))
    {

        e = parseCExp();

        tb = parseBody();

        s = new WhileStatement(e, tb);
    }
    else if (match(Token::FOR))
    {

        if (!match(Token::ID))
        {
            cout << "Error: se esperaba un identificador después de 'for'." << endl;
            exit(1);
        }
        string var = previous->text;

        if (!match(Token::IN))
        {
            cout << "Error: se esperaba 'in' después del identificador." << endl;
            exit(1);
        }

        Exp *start = parseCExp();

        if (!match(Token::RANGE))
        {
            cout << "Error: se esperaba '..' después de la expresión inicial." << endl;
            exit(1);
        }

        Exp *end = parseCExp();

        Exp *step = nullptr;

        Body *tb = parseBody();

        s = new ForStatement(var, start, end, step, tb);
    }

    else if (match(Token::RETURN))
    {
        if (!match(Token::PI))
        {
            cout << "Error: se esperaba '(' después de 'return'." << endl;
            exit(1);
        }
        if (!check(Token::PD))
        {
            e = parseCExp();
        }
        if (!match(Token::PD))
        {
            cout << "Error: se esperaba ')' después de la expresión." << endl;
            exit(1);
        }
        s = new ReturnStatement(e); // Si es null, no hay problema
    }
    else if (match(Token::RBRACE))
    {

        s = new ReturnStatement(e); // Si es null, no hay problema
    }
    else
    {
        cout << "Error: Se esperaba un identificador o 'print', pero se encontró: " << *current << endl;
        exit(1);
    }
    return s;
}

Exp *Parser::parseCExp()
{
    cout << "parseCExp " << *current << endl;
    Exp *left = parseExpression();
    if (match(Token::LT) || match(Token::LE) || match(Token::EQ))
    {
        BinaryOp op;
        if (previous->type == Token::LT)
        {
            op = LT_OP;
        }
        else if (previous->type == Token::LE)
        {
            op = LE_OP;
        }
        else if (previous->type == Token::EQ)
        {
            op = EQ_OP;
        }
        Exp *right = parseExpression();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp *Parser::parseExpression()
{

    Exp *left = parseTerm();
    while (match(Token::PLUS) || match(Token::MINUS))
    {
        BinaryOp op;
        if (previous->type == Token::PLUS)
        {
            op = PLUS_OP;
        }
        else if (previous->type == Token::MINUS)
        {
            op = MINUS_OP;
        }
        Exp *right = parseTerm();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp *Parser::parseTerm()
{

    Exp *left = parseFactor();
    while (match(Token::MUL) || match(Token::DIV))
    {
        BinaryOp op;
        if (previous->type == Token::MUL)
        {
            op = MUL_OP;
        }
        else if (previous->type == Token::DIV)
        {
            op = DIV_OP;
        }
        Exp *right = parseFactor();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp *Parser::parseFactor()
{
    cout << "parseFactor " << *current << endl;
    Exp *e;
    Exp *e1;
    Exp *e2;
    if (match(Token::TRUE))
    {

        return new BoolExp(1);
    }
    else if (match(Token::FALSE))
    {

        return new BoolExp(0);
    }
    else if (match(Token::NUM))
    {

        return new NumberExp(stoi(previous->text));
    }
    else if (match(Token::STRING))
    {
        cout << "STRING " << endl;
        return new StringExp(previous->text);
    }
    else if (match(Token::ID))
    {

        string texto = previous->text;
        // Parse FCallExp
        if (match(Token::PI))
        {
            list<Exp *> args;
            if (!check(Token::PD))
            {
                args.push_back(parseCExp());
                while (match(Token::COMA))
                {
                    args.push_back(parseCExp());
                }
            }
            if (!match(Token::PD))
            {
                cout << "Falta paréntesis derecho" << endl;
                exit(0);
            }
            return new FCallExp(texto, args);
        }
        else
        {
            return new IdentifierExp(previous->text);
        }
    }
    else if (match(Token::IFEXP))
    {

        match(Token::PI);
        e = parseCExp();
        match(Token::COMA);
        e1 = parseCExp();
        match(Token::COMA);
        e2 = parseCExp();
        match(Token::PD);
        return new IFExp(e, e1, e2);
    }
    else if (match(Token::PI))
    {

        e = parseCExp();
        if (!match(Token::PD))
        {
            cout << "Falta paréntesis derecho" << endl;
            exit(0);
        }
        return e;
    }

    cout << "Error: se esperaba un número o identificador." << endl;
    exit(0);
}
