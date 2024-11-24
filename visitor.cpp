#include <iostream>
#include "exp.h"
#include "visitor.h"
#include <unordered_map>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////
int BinaryExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}
int IFExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}
int NumberExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}
int StringExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int BoolExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int IdentifierExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int AssignStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int FCallStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int PrintStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int IfStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int WhileStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}
int ForStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int VarDec::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int VarDecList::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}
int StatementList::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}
int Body::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int Program::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int FunDec::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int FunDecList::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int ReturnStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int FCallExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

///////////////////////////////////////////////////////////////////////////////////

int PrintVisitor::visit(BinaryExp *exp)
{
    exp->left->accept(this);
    cout << ' ' << Exp::binopToChar(exp->op) << ' ';
    exp->right->accept(this);
    return 0;
}
int PrintVisitor::visit(StringExp *exp)
{
    cout << "" << exp->value << "";
    return 0;
}

int PrintVisitor::visit(NumberExp *exp)
{
    cout << exp->value;
    return 0;
}

int PrintVisitor::visit(BoolExp *exp)
{
    if (exp->value)
        cout << "true";
    else
        cout << "false";
    return 0;
}

int PrintVisitor::visit(IdentifierExp *exp)
{
    cout << exp->name;
    return 0;
}

void PrintVisitor::visit(AssignStatement *stm)
{
    cout << stm->id << " = ";
    stm->rhs->accept(this);
    cout << ";";
}

void PrintVisitor::visit(PrintStatement *stm)
{
    cout << "println!(";

    // Visitar la primera expresión
    if (stm->e1 != nullptr)
    {
        stm->e1->accept(this);
    }
    else
    {
        cout << "Error: expresión 1 no válida.";
    }

    cout << ", ";

    // Visitar la segunda expresión
    if (stm->e2 != nullptr)
    {
        stm->e2->accept(this);
    }
    else
    {
        cout << "Error: expresión 2 no válida.";
    }

    cout << ");";
}

void PrintVisitor::visit(IfStatement *stm)
{
    cout << "if ";
    stm->condition->accept(this);
    cout << " {" << endl;
    stm->then->accept(this);
    if (stm->els)
    {
        printIndent();
        cout << "else" << endl;
        stm->els->accept(this);
    }
    printIndent();
    cout << "}";
}

void PrintVisitor::imprimir(Program *program)
{
    program->accept(this);
}

void PrintVisitor::visit(Program *program)
{
    program->vardecs->accept(this);
    program->fundecs->accept(this);
};

int PrintVisitor::visit(IFExp *pepito)
{
    cout << "ifexp(";
    pepito->cond->accept(this);
    cout << ",";
    pepito->left->accept(this);
    cout << ",";
    pepito->right->accept(this);
    cout << ")";
    return 0;
}

void PrintVisitor::visit(WhileStatement *stm)
{
    cout << "while ";
    stm->condition->accept(this);
    cout << " {" << endl;
    stm->b->accept(this);
    printIndent();
    cout << "}";
}

void PrintVisitor::visit(ForStatement *stm)
{
    cout << "for ";
    stm->start->accept(this);
    cout << " to ";
    stm->end->accept(this);
    // cout << " step ";
    // stm->step->accept(this);
    cout << " do" << endl;
    stm->b->accept(this);
    cout << "endfor";
}

void PrintVisitor::visit(VarDec *stm)
{
    cout << "var ";

    if (stm->isMutable)
    {
        cout << "mut ";
    }

    cout << stm->type << " ";

    cout << stm->name << ";";
}

void PrintVisitor::visit(VarDecList *stm)
{
    for (auto i : stm->vardecs)
    {
        printIndent();
        i->accept(this);
        cout << endl;
    }
}

void PrintVisitor::visit(StatementList *stm)
{
    for (auto i : stm->stms)
    {
        printIndent();
        i->accept(this);
        cout << endl;
    }
}

void PrintVisitor::visit(Body *stm)
{
    increaseIndent();
    stm->vardecs->accept(this);
    stm->slist->accept(this);
    decreaseIndent();
}

void PrintVisitor::visit(FunDec *stm)
{

    cout << "fn " << stm->fname << "(";

    bool first = true;
    list<string>::iterator type, name;

    for (type = stm->types.begin(), name = stm->vars.begin(); type != stm->types.end(); ++type, ++name)
    {
        if (!first)
        {
            cout << ", ";
        }
        cout << *name << ": " << *type;
        first = false;
    }

    cout << ")";

    if (stm->rtype != "")
    {
        cout << " -> " << stm->rtype;
    }

    cout << " { " << endl;

    stm->body->accept(this);

    cout << "}" << endl;
}

void PrintVisitor::visit(FunDecList *stm)
{
    for (auto i : stm->flist)
    {
        i->accept(this);
        cout << endl;
    }
}

void PrintVisitor::visit(ReturnStatement *s)
{
    // cout << "return (";
    if (s->e != NULL)
        s->e->accept(this);
    // cout << ")";
    return;
}

int PrintVisitor::visit(FCallExp *e)
{
    cout << e->fname << "(";
    list<Exp *>::iterator it;
    bool first = true;
    for (it = e->args.begin(); it != e->args.end(); ++it)
    {
        if (!first)
            cout << ",";
        first = false;
        (*it)->accept(this);
    }
    cout << ')';
    return 0;
}

void PrintVisitor::visit(FCallStatement *e)
{
    cout << e->fname << "(";
    list<Exp *>::iterator it;
    bool first = true;
    for (it = e->args.begin(); it != e->args.end(); ++it)
    {
        if (!first)
            cout << ",";
        first = false;
        (*it)->accept(this);
    }
    cout << ')';
}

void PrintVisitor::printIndent()
{
    for (int i = 0; i < indentLevel * 2; i++)
    {
        cout << ' ';
    }
}
