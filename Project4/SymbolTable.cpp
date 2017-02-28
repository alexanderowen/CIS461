#include <unordered_map>
#include <list>
#include <string>
#include <string.h>
#include "stdio.h"

#include "SymbolTable.h"
#include "type.h"

using std::unordered_map;
using std::list;
using std::string;

VariableSym::VariableSym(char *i, char *t) : id(i), type(t) {}

MethodSym::MethodSym(char *i, list<VariableSym *> *a, char *r) : id(i), args(a), returnType(r) {}

SymbolTable::SymbolTable(SymbolTable *p) : parent(p) {}

// note: this intersection does not travel all the way up the symboltable (ignores parent)
SymbolTable *SymbolTable::intersection(list<SymbolTable*> sts, TypeTree *tt)
{
    SymbolTable *total = new SymbolTable(parent);
    bool found = true;
    VariableSym *v;
    //fprintf(stderr, "About to do intersection on map with size %lu\n", vMap.size());
    for (unordered_map<string, VariableSym*>::const_iterator key = vMap.begin(); key != vMap.end(); ++key)
    {
        char *type = key->second->type;
        for (list<SymbolTable*>::const_iterator it = sts.begin(); it != sts.end(); ++it)
        {
            v = (*it)->lookupVariableNoParent(strdup(key->first.c_str()));
            if (v == NULL)
            {
                //fprintf(stderr, "No match found: %s\n", key->first.c_str());
                found = false;
                break;
            } 
            else 
            {
                type = tt->LCA(type, v->type);
            } 
        }

        if (found) 
        {
            //fprintf(stderr, "Found a match: %s\n", key->first.c_str());
            VariableSym *newVar = new VariableSym(strdup(key->first.c_str()),type);
            total->addVariable(strdup(key->first.c_str()), newVar);
        }
        found = true;
    }
    //fprintf(stderr, "All done with intersection\n");
    return total;    
}

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
VariableSym *SymbolTable::lookupVariableNoParent(char *name)
{
    string key = name;
    auto search = vMap.find(key);

    if (search != vMap.end())
        return search->second;
    else
        return NULL;
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
