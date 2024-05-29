#include "Database.h"

void Database::AddRelation(Relation newRelation) {
    string name = newRelation.GetName();
    relations.insert({name, newRelation});
}

Relation* Database::FindRelation(string name) {
    return &relations.at(name);
}

string Database::ToString() {
    stringstream out;
    map<string, Relation>::iterator it = relations.begin();
    while (it != relations.end()) {
        out << it->first << endl << it->second.TestToString();
        ++it;
    }
    return out.str();
}