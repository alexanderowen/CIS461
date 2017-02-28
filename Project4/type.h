#ifndef TYPE_H
#define TYPE_H

#include <list>

using std::list;

class MethodNode 
{                                                                                                      
    public:                                                                                            
        char *id;                                                                                      
        list<char *> argsType;
        char *returnType;
        MethodNode(char *, list<char *> , char *);                                              

        int argsMatch(list<char*> args);
        //int compareArgs(MethodNode *other);
        //int compareReturn(MethodNode *other);

        void print();
}; 

class VariableNode
{
    public:
        char *name;
        char *type;

        VariableNode(char *n, char *t);
};

class TypeTree;

class TypeNode
{
    public:
        char *name;
        TypeNode *parent;
        list<TypeNode *> children;
        list<MethodNode *> methods;
        list<VariableNode *> instanceVars;

        TypeNode(char *n, TypeNode *p);
        int addChild(TypeNode *type);
        int addChild(char *type);
        int hasDescendant(char *type);
        int addMethod(MethodNode *m);
        int hasMethod(char *name);
        MethodNode *getMethod(char *name);

        int hasInstanceVar(char *name);
        VariableNode *getInstanceVar(char *name);
        void addInstanceVar(VariableNode *v, TypeTree *tt);

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

        int isSubtype(char *_t1, char *_t2);
        int isSupertype(char *_t1, char *_t2);

        char *LCA(char *_t1, char *_t2);

        int addSubtype(TypeNode *sub, char *super);
        int addSubtype(char *sub, char *super);
        int addMethodToType(char *type, MethodNode *m);
        int typeHasMethod(char *type, char* method); 

        void addVarToType(char *type, VariableNode *v);
        char *getVarFromType(char *type, char *var);

        MethodNode *typeGetMethod(char *type, char *method);
        TypeNode *findType(char *name);
        TypeNode *search(TypeNode *root, char *name);
        void print();
        void print(TypeNode *t);
};

#endif 
