#ifndef PROJECT_1_DATABASE_H
#define PROJECT_1_DATABASE_H

#include "Relation.h"

#include <map>

using std::map;
using std::cout;

class Database {
private:
    map<string, Relation> relations;

public:
    void AddRelation(Relation newRelation);

    Relation* FindRelation(string name);

    string ToString();
};


#endif //PROJECT_1_DATABASE_H
