#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"

#include <vector>
#include <sstream>
#include <set>

using std::vector;
using std::stringstream;
using std::endl;
using std::set;

class DatalogProgram {
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domain;

public:
    string ToString();
    void AddScheme(Predicate scheme);
    void AddFact(Predicate fact);
    void AddRule(Rule rule);
    void AddQuery(Predicate query);
    void SetDomain(set<string> tempDomain);

    vector<Predicate> GetSchemes();
    vector<Predicate> GetFacts();
    vector<Rule> GetRules();
    vector<Predicate> GetQueries();
};


#endif //PROJECT_1_DATALOGPROGRAM_H
