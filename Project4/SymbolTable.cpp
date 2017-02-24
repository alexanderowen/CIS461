#include <unordered_map>
#include <list>
#include <string>
#include <string.h>
#include "SymbolTable.h"
#include "stdio.h"

using std::unordered_map;
using std::list;
using std::string;

VariableSym::VariableSym(char *i, char *t) : id(i), type(t) {}

MethodSym::MethodSym(char *i, list<VariableSym *> *a, char *r) : id(i), args(a), returnType(r) {}

SymbolTable::SymbolTable(SymbolTable *p) : parent(p) {}

VariableSym *SymbolTable::lookupVariable(char *name)
{
    //fprintf(stderr, "Looking up variable '%s'\n", name);
    string key = name;
    auto search = vMap.find(key);

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
    string key = name;
    vMap.insert({key, value});
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
