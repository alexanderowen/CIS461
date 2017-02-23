
#include <list>
#include "type.h"
#include "stdio.h"
#include "string.h"

using std::list;

MethodNode::MethodNode(char *i, list<char*> a, char *r) : id(i), argsType(a), returnType(r) {}

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
    return 0;
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
    printf("%s\n",this->name);
}
/***/

TypeTree::TypeTree()
{
    char *OBJ = (char*)"Obj";
    char *INT = (char*)"Int";
    char *STR = (char*)"String";
    char *NOT = (char*)"Nothing";
    char *BOOL = (char*)"Boolean";

    TypeNode *o = new TypeNode((char*)"Obj", NULL);
    root = o;
    root->addChild((char*)"Int");

    //this->addMethodToType((char*)"OBJ", MethodNode((char*)"STR",&(list<char*>((char*)"OBJ")),(char*)"OBJ"));
    list<char*> args;
    args.push_back(OBJ);
    MethodNode m((char*)"STR", args, STR);
    this->addMethodToType(OBJ, &m);
    MethodNode ObjPrint((char*)"PRINT", args, NOT);
    this->addMethodToType(OBJ, &ObjPrint); 
    MethodNode ObjEquals((char*)"EQUALS", args, BOOL);

    // Assignment built-in methods of Int to the typechecker
    list<char*> int_args;
    int_args.push_back(INT);
    MethodNode IntPlus((char*)"PLUS", int_args, INT);
    this->addMethodToType(INT, &IntPlus);
    MethodNode IntMinus((char*)"MINUS", int_args, INT);
    this->addMethodToType(INT, &IntMinus);
    MethodNode IntTimes((char*)"TIMES", int_args, INT);
    this->addMethodToType(INT, &IntTimes);
    MethodNode IntDivide((char*)"DIVIDE", int_args, INT);
    this->addMethodToType(INT, &IntDivide);
    MethodNode IntAtMost((char*)"ATMOST", int_args, BOOL);
    this->addMethodToType(INT, &IntAtMost);
    MethodNode IntLess((char*)"LESS", int_args, BOOL);
    this->addMethodToType(INT, &IntLess);
    MethodNode IntAtLeast((char*)"ATLEAST", int_args, BOOL);
    this->addMethodToType(INT, &IntAtLeast);
    MethodNode IntMore((char*)"MORE", int_args, BOOL);
    this->addMethodToType(INT, &IntMore);

    // TODO: Methods for String, Boolean, and Nothing
    root->addChild((char*)"String");
    root->addChild((char*)"Boolean");
    root->addChild((char*)"Nothing");
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
    t->print();
    for (list<TypeNode *>::const_iterator it = t->children.begin(); it != t->children.end(); ++it)
    {
        (*it)->print();
    }
}   

