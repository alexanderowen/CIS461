#include <unordered_map>
#include <list>

using std::unordered_map;
using std::list;

class Symbol
{};

class VariableSym : public Symbol
{
    public:
        char *id;
        char *type;
        VariableSym(char *, char *);
};

class MethodSym : public Symbol
{
    public:
        char *id;
        list<VariableSym *> *args;
        char *returnType;
        MethodSym(char *, list<VariableSym *> *, char *);
};

/*
class SymbolTable 
{
    public:
        SymbolTable   *parent;
        unordered_map<char *, VariableSym *> vMap;
        unordered_map<char *, MethodSym *> mMap;

        SymbolTable(SymbolTable *p);
        VariableSym *lookupVariable(char *name);
        MethodSym *lookupMethod(char *name);
        void  addVariable(char *name, VariableSym *value); 
        void  addMethod(char *name, MethodSym *value); 
};
*/

class SymbolTable
{
    public:
        SymbolTable *parent;
        unordered_map<char *, VariableSym *> vMap;

        SymbolTable(SymbolTable *p);
        VariableSym *lookupVariable(char *name);
        void addVariable(char *name, VariableSym *value);
};
