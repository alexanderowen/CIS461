#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>
#include <list>

#include "type.hpp"

using std::unordered_map;
using std::list;
using std::string;

/*** Classes defined in this file***/
class SymbolTable;
class Symbol;
class VariableSym;
class MethodSym;

class SymbolTable
{
    public:
        SymbolTable *parent;
        unordered_map<string, VariableSym *> vMap;

        SymbolTable(SymbolTable *p);
       ~SymbolTable();

        VariableSym *lookupVariable(char *name);
        void addVariable(char *name, VariableSym *value);

        SymbolTable *intersection(list<SymbolTable*> sts, TypeTree *tt);
    private:
        VariableSym *lookupVariableNoParent(char *name);

};

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


#endif