#include <unordered_map>
#include <list>
#include <string.h>
#include "SymbolTable.h"

using std::unordered_map;
using std::list;

VariableSym::VariableSym(char *i, char *t) : id(i), type(t) {}

MethodSym::MethodSym(char *i, list<VariableSym *> *a, char *r) : id(i), args(a), returnType(r) {}

SymbolTable::SymbolTable(SymbolTable *p) : parent(p) {}

VariableSym *SymbolTable::lookupVariable(char *name)
{
    auto search = vMap.find(name);
    if (search != vMap.end())
    {
        return search->second;
    } 
    else if (parent != NULL) 
    {
        return parent->lookupVariable(name);    
    }
    else
    {
        return NULL;
    }
}

void SymbolTable::addVariable(char *name, VariableSym *value)
{
    vMap.insert({name, value});
}
/*
MethodSym *SymbolTable::lookupMethod(char *name)
{
    auto search = mMap.find(name);
    if (search != mMap.end())
    {
        return search->second;
    } 
    else if (parent != NULL) 
    {
        return parent->lookupMethod(name);    
    }
    else
    {
        return NULL;
    }
}
void SymbolTable::addMethod(char *name, MethodSym *value)
{
    mMap.insert({name, value});
}
*/
