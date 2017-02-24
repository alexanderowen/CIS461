
#include <list>
#include "type.h"
#include "stdio.h"
#include "string.h"

using std::list;

MethodNode::MethodNode(char *i, list<char*> a, char *r) : id(i), argsType(a), returnType(r) {}

int MethodNode::argsMatch(list<char*> args)
{
    if (args.size() != argsType.size())
        return 0;
    list<char*>::const_iterator thisArgs = argsType.begin();
    list<char*>::const_iterator otherArgs = args.begin();
    for (int i = 0; i < args.size(); i++)
    {
        if (strcmp((*thisArgs), (*otherArgs)) != 0)
            return 0;
        std::advance(thisArgs, 1);  // Turns out std::list is not the right structure for this
        std::advance(otherArgs, 1); // Requires this silly stuff
    }
    return 1;
}

void MethodNode::print()
{
    //fprintf(stderr, "About to print info\n");
    fprintf(stderr, "  Method: '%s' takes: '", id);
    //fprintf(stderr, "Printed the name\n");
    for (list<char*>::const_iterator it = argsType.begin(); it != argsType.end(); ++it)
    {
        printf("%s ", (*it));
    }
    printf("' and returns '%s'\n", returnType);
}

TypeNode::TypeNode(char *n, TypeNode *p) : name(n), parent(p) 
{
}

int TypeNode::addChild(TypeNode *type)
{
    children.push_back(type);  //TODO: when does this fail?
    type->parent = this;
    //type->print();
    return 1; 
}

int TypeNode::addChild(char *name)
{
    TypeNode *n = new TypeNode(name, NULL);
    this->addChild(n);
    return 1;
}

int TypeNode::addMethod(MethodNode *m)
{
    methods.push_back(m);
    return 1;
}

int TypeNode::hasMethod(char *name)
{
    for (list<MethodNode *>::const_iterator it = this->methods.begin(); it != this->methods.end(); ++it)
    {
        if ( strcmp((*it)->id, name) == 0)
            return 1;
    }
    if (this->parent != NULL)
    {
        return parent->hasMethod(name);
    }
    return 0;
}

MethodNode *TypeNode::getMethod(char *name)
{
    for (list<MethodNode *>::const_iterator it = this->methods.begin(); it != this->methods.end(); ++it)
    {
        if ( strcmp((*it)->id, name) == 0)
            return (*it);
    }
    if (this->parent != NULL)
    {
        return parent->getMethod(name);
    }
    return NULL;
}

int TypeNode::equals(TypeNode *type)
{
    return !strcmp(this->name, type->name); // since strcmp returns 0 if equal
}

int TypeNode::equals(char *n)
{
    return !strcmp(this->name, n);
}

void TypeNode::print()
{
    printf("Type: %s\n",this->name);
    for (list<MethodNode*>::const_iterator it = methods.begin(); it != methods.end(); ++it)
    {
        //fprintf(stderr, "Printing a method\n");
        (*it)->print();
    }

}
/***/

TypeTree::TypeTree()
{
    char *OBJ = strdup((char*)"Obj");
    char *INT = strdup((char*)"Int");
    char *STR = strdup((char*)"String");
    char *NOTHING = strdup((char*)"Nothing");
    char *BOOL = strdup((char*)"Boolean");

    TypeNode *o = new TypeNode(OBJ, NULL);
    root = o;
    root->addChild(INT);

    //this->addMethodToType((char*)"OBJ", MethodNode((char*)"STR",&(list<char*>((char*)"OBJ")),(char*)"OBJ"));
    list<char*> args;
    args.push_back(OBJ);
    MethodNode *m = new MethodNode(strdup((char*)"STR"), args, STR);
    this->addMethodToType(OBJ, m);
    MethodNode *ObjPrint = new MethodNode(strdup((char*)"PRINT"), args, NOTHING);
    this->addMethodToType(OBJ, ObjPrint); 
    MethodNode *ObjEquals = new MethodNode(strdup((char*)"EQUALS"), args, BOOL);

    // Assignment built-in methods of Int to the typechecker
    list<char*> int_args;
    int_args.push_back(INT);
    MethodNode *IntPlus = new MethodNode(strdup((char*)"PLUS"), int_args, INT);
    this->addMethodToType(INT, IntPlus);
    MethodNode *IntMinus = new MethodNode(strdup((char*)"MINUS"), int_args, INT);
    this->addMethodToType(INT, IntMinus);
    MethodNode *IntTimes = new MethodNode(strdup((char*)"TIMES"), int_args, INT);
    this->addMethodToType(INT, IntTimes);
    MethodNode *IntDivide = new MethodNode(strdup((char*)"DIVIDE"), int_args, INT);
    this->addMethodToType(INT, IntDivide);
    MethodNode *IntAtMost = new MethodNode(strdup((char*)"ATMOST"), int_args, BOOL);
    this->addMethodToType(INT, IntAtMost);
    MethodNode *IntLess = new MethodNode(strdup((char*)"LESS"), int_args, BOOL);
    this->addMethodToType(INT, IntLess);
    MethodNode *IntAtLeast = new MethodNode(strdup((char*)"ATLEAST"), int_args, BOOL);
    this->addMethodToType(INT, IntAtLeast);
    MethodNode *IntMore = new MethodNode(strdup((char*)"MORE"), int_args, BOOL);
    this->addMethodToType(INT, IntMore);

    // Methods for String
    root->addChild(STR);
    list<char*> str_args;
    str_args.push_back(STR);
    MethodNode *StrPlus = new MethodNode(strdup((char*)"PLUS"), str_args, STR);
    this->addMethodToType(STR, StrPlus);

    // Methods for Bool
    root->addChild(BOOL);
    /* 'not' is not a method
    list<char*> bool_args;
    bool_args.push_back(BOOL);
    MethodNode *BoolNot = new MethodNode(strdup((char*)"NOT"), bool_args, BOOL);
    this->addMethodToType(BOOL, BoolNot);
    */
    root->addChild(NOTHING);
}

int TypeTree::addSubtype(TypeNode *sub, char *super)
{
    TypeNode *type = findType(super);
    //type->print();
    if (type == NULL)
        return 0;

    return type->addChild(sub);
}

int TypeTree::addSubtype(char *sub, char *super)
{
    TypeNode *n = new TypeNode(sub, NULL);
    return this->addSubtype(n, super);
}

int TypeTree::addMethodToType(char *_type, MethodNode *m)
{
    TypeNode *type = findType(_type);
    if (type == NULL)
        return 0;
    return type->addMethod(m);
}

int TypeTree::typeHasMethod(char *_type, char *method)
{
    TypeNode *type = findType(_type);
    if (type == NULL)
        return 0;
    return type->hasMethod(method);
}

MethodNode *TypeTree::typeGetMethod(char *_type, char *method)
{
    TypeNode *type = findType(_type);
    if (type == NULL)
        return NULL;
    return type->getMethod(method);
}

TypeNode *TypeTree::findType(char *name)
{
    return search(root, name);
}

TypeNode *TypeTree::search(TypeNode *r, char *name)
{
    //printf("root: ");
    //r->print();
    //printf("name: %s\n", name);
    if (r->equals(name))
        return r;
    //printf("doesn't equal: %d\n", r->equals(name));
    for (list<TypeNode *>::const_iterator it = r->children.begin(); it != r->children.end(); ++it)
    {
        TypeNode *t = search((*it), name);
        if (t != NULL)
            return t;
    }
    return NULL;
}

void TypeTree::print()
{
    this->print(root); 
}

void TypeTree::print(TypeNode *t)
{
    //fprintf(stderr, "Printing a parent\n");
    t->print();
    for (list<TypeNode *>::const_iterator it = t->children.begin(); it != t->children.end(); ++it)
    {
        //fprintf(stderr, "Printing a child\n");
        //(*it)->print();
        printf("Children of %s:\n", t->name);
        print((*it));
    }
}   

