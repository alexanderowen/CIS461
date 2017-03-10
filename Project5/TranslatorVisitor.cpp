
#include "stdio.h"
#include "stdlib.h"

#include "visitor.h"
#include "TranslatorVisitor.hpp"

TranslatorVisitor::TranslatorVisitor(char *fn)
{
    f = fopen(fn, "w");    
    if (f == NULL)
    {
        fprintf(stderr, "Error opening %s in TranslatorVisitor constructor\n", fn);
        exit(1);
    }
    typeMap.insert({"Obj", "obj_Obj"});
    typeMap.insert({"Int", "obj_Int"});
}

TranslatorVisitor::~TranslatorVisitor()
{
    if (f != NULL)
        fclose(f);
}

void TranslatorVisitor::visitProgram(Program *p)
{
    fprintf(f, "#include \"Builtins.h\"\n");
    /*  //TODO: Uncomment when ready for classes
    for (list<Class *>::const_iterator it = p->classes->begin(); it != p->classes->end(); ++it)
    {
        (*it)->accept(this);
    }
    */
    fprintf(f, "int main() {\n");
    for (list<Statement *>::const_iterator it = p->statements->begin(); it != p->statements->end(); ++it)
    {
        (*it)->accept(this);
        fprintf(f, "\n");
    }
    fprintf(f, "\n}");
}

void TranslatorVisitor::visitAssignmentStatement(AssignmentStatement *a)
{
    string t = getType(a->rexpr);
    fprintf(stderr, "Found type :'%s'\n", t.c_str());
    auto v = typeMap.find(t);
    if (v != typeMap.end()) 
    {
        fprintf(f, "%s ", v->second.c_str());
    }
    a->lexpr->print(f);
    fprintf(f, ";\n");
    a->lexpr->accept(this);
    fprintf(f, " = ");
    a->ident->accept(this);

    a->rexpr->accept(this);
    fprintf(f, ";");
}

void TranslatorVisitor::visitIntNode(IntNode *i)
{
    fprintf(f, "int_literal(%d)", i->value);
}

void TranslatorVisitor::visitStringNode(StringNode *s)
{
    fprintf(f, "string_literal(%s)", s->id);
}

void TranslatorVisitor::visitBinaryOperatorNode(BinaryOperatorNode *b)
{
    b->left->accept(this);
    fprintf(f, "->clazz->");
    switch(b->operation) {
        case 0:
            fprintf(f, "PLUS");
            break;
        case 1:
            fprintf(f, "MINUS");
            break;
        case 2:
            fprintf(f, "TIMES");
            break;
        case 3:
            fprintf(f, "DIVIDE");
            break;
        case 4:
            fprintf(f, "EQUALS");
            break;
        case 5:
            fprintf(f, "ATMOST");
            break;
        case 6:
            fprintf(f, "LESS");
            break;
        case 7:
            fprintf(f, "ATLEAST");
            break;
        case 8:
            fprintf(f, "MORE");
            break;
        case 9:
            fprintf(f, "AND");
            break;
        case 10:
            fprintf(f, "OR");
            break;
        default:
            break;
    }
    fprintf(f, "(");
    b->left->accept(this); // Just a way of visiting printing left again
    fprintf(f, ", ");
    b->right->accept(this);
    fprintf(f, ")");

}

void TranslatorVisitor::visitIdentNode(IdentNode *i)
{
    fprintf(f, "%s", i->id);
}

void TranslatorVisitor::visitDotRExpr(DotRExpr *d) 
{
    d->rexpr->accept(this);
    fprintf(f, "->clazz->%s(", d->id);
    d->rexpr->accept(this); // Just a way to print out first argument of methods
    for (list<RExpr *>::const_iterator it = d->args->begin(); it != d->args->end(); ++it)
    {
        (*it)->accept(this);
    }
    fprintf(f, ");");
}    


/*****************
 *
 * TranslatorVisitor private methods
 *
 * ***************/

IdentNode *TranslatorVisitor::isIdent(RExpr *r)
{
    RExprToLExpr *rl = dynamic_cast<RExprToLExpr*>(r);
    if (rl != NULL) //if it is an lexpr
    {
        IdentNode *id = dynamic_cast<IdentNode*>(rl->lexpr);
        if (id != NULL) //and the lexpr is an ident node
        {
            return id; 
        }
    }
    return NULL;

}

ObjectFieldLExpr *TranslatorVisitor::isOFL(RExpr *r)
{
    RExprToLExpr *rl = dynamic_cast<RExprToLExpr*>(r);
    if (rl != NULL) //if it is an lexpr
    {
        ObjectFieldLExpr *ofl = dynamic_cast<ObjectFieldLExpr*>(rl->lexpr);
        if (ofl != NULL)
        {
            return ofl;
        }
    }
    return NULL;
}

char *TranslatorVisitor::getType(RExpr *r)
{
    char *type;
    type = r->type();
    if (strcmp(type, (char*)"-") != 0) //type covered because it's a literal or easy to identify
        return type;
/*
    IdentNode *ident = isIdent(r);
    if (ident != NULL) //type is in the variable information
    {
        if (strcmp(ident->id, (char*)"this") == 0)
        {
            return className;
        }
        VariableSym *v = st->lookupVariable(ident->id);
        return v->type;
    }

    DotRExpr *dot = dynamic_cast<DotRExpr*>(r);
    if (dot != NULL)
    {
        char *_type = getType(dot->rexpr);
        MethodNode *m = tt->typeGetMethod(_type, dot->id);
        if (m == NULL)
        {
            return strdup((char*)"-");
        }
        return m->returnType;
    }
    ObjectFieldLExpr *ofl = isOFL(r);
    if (ofl != NULL)
    {
        char *rType = getType(ofl->rexpr);
        if (rType == NULL)
            return strdup((char*)"-");
        char *__type = tt->getVarFromType(rType, ofl->id);
        if (__type == NULL)
        {
            char *msg = (char*) malloc(sizeof(char)*256);
            sprintf(msg, "%d: Syntax Error\n\tType '%s' has no instance variable '%s'\n", r->lineno, rType, ofl->id);
            addError(msg);
            return strdup((char*)"-");
        }
        return __type;
    }
*/

    PlusNode *plus = dynamic_cast<PlusNode*>(r);
    if (plus != NULL)
    {
        return getType(plus->left);
    }
    MinusNode *minus = dynamic_cast<MinusNode*>(r);
    if (minus != NULL)
    {
        return getType(minus->left);
    }
    TimesNode *times = dynamic_cast<TimesNode*>(r);
    if (times != NULL)
    {
        return getType(times->left);
    }
    DivideNode *divide = dynamic_cast<DivideNode*>(r);
    if (divide != NULL)
    {
        return getType(divide->left);
    }
    return strdup((char*)"-");
}

void TranslatorVisitor::printRExpr(RExpr *r)
{
    IdentNode *ident = isIdent(r);
    if (ident != NULL) //type is in the variable information
    {
        /*
        if (strcmp(ident->id, (char*)"this") == 0)
        {
            return className;
        }
        VariableSym *v = st->lookupVariable(ident->id);
        return v->type;
        */
        fprintf(f, "%s", ident->id);
    }
     
}
