#ifndef TYPE_H
#define TYPE_H

#include <list>

using std::list;

class MethodNode 
{                                                                                                      
    public:                                                                                            
        char *id;                                                                                      
        list<char *> *argsType;                                                                     
        char *returnType;                                                                              
        MethodNode(char *, list<char *> *, char *);                                              
}; 

class TypeNode
{
    public:
        char *name;
        TypeNode *parent;
        list<TypeNode *> children;
        list<MethodNode *> methods;

        TypeNode(char *n, TypeNode *p);
        int addChild(TypeNode *type);
        int addChild(char *type);
        int addMethod(MethodNode *m);
        int hasMethod(char *name);
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
        int addMethodToType(char *type, MethodNode *m);
        int typeHasMethod(char *type, char* method); //TODO: Make sure args match
        TypeNode *findType(char *name);
        TypeNode *search(TypeNode *root, char *name);
        void print();
        void print(TypeNode *t);
};

#endif 
