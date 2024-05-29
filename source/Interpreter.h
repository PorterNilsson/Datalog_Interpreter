#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

#include <iostream>

using std::cout;

class Interpreter {
private:
    DatalogProgram program;
    Database database;

    vector<int> columnNumbers;
    vector<string> variableNames;
    map<string, int> variableNamesAndColumnNumbers;

    Graph dependencyGraph;

public:
    Interpreter(DatalogProgram program);

    void InterpretSchemes();
    void InterpretFacts();

    void OptimizeRules();

    bool InterpretRules(int scc);

    vector<set<int> > GetSccVector();

    void InterpretQueries();
    Relation EvaluatePredicate(Predicate predicate);

    bool MyUnion(Relation newRelation, string relationName);

    string DatabaseToString();
    string GetGraphString(int index);
};


#endif //PROJECT_1_INTERPRETER_H
