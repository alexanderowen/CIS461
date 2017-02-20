
#include <list>
#include "type.h"
#include "stdio.h"
#include "string.h"

using std::list;

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

int TypeNode::equals(TypeNode *type)
{
    return strcmp(this->name, type->name);
}

int TypeNode::equals(char *n)
{
    return strcmp(this->name, n);
}

void TypeNode::print()
{
    printf("%s\n",this->name);
}
/***/

TypeTree::TypeTree()
{
    TypeNode *o = new TypeNode((char*)"Obj", NULL);
    root = o;
    root->addChild((char*)"Int");
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

TypeNode *TypeTree::findType(char *name)
{
    return search(root, name);
}

TypeNode *TypeTree::search(TypeNode *r, char *name)
{
    //printf("root: ");
    //r->print();
    //printf("name: %s\n", name);
    if (r->equals(name) == 0)
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

