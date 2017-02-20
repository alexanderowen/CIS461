#ifndef TYPE_H
#define TYPE_H

#include <list>

using std::list;

class TypeNode
{
    public:
        char *name;
        TypeNode *parent;
        list<TypeNode *> children;

        TypeNode(char *n, TypeNode *p);
        int addChild(TypeNode *type);
        int addChild(char *type);
        int equals(TypeNode *type);
        int equals(char *name);
        void print();
};

class TypeTree 
{
    private:
        TypeNode *root;
    public:
        TypeTree();

        int addSubtype(TypeNode *sub, char *super);
        int addSubtype(char *sub, char *super);
        TypeNode *findType(char *name);
        TypeNode *search(TypeNode *root, char *name);
        void print();
        void print(TypeNode *t);
};

#endif 
