#ifndef PROJECT_1_RULE_H
#define PROJECT_1_RULE_H

#include "Predicate.h"

#include <vector>

using std::vector;

class Rule {
private:
    Predicate head;
    vector<Predicate> body;

public:
    void SetPredicateHead(Predicate head);
    void AddBodyPredicate(Predicate body);

    void clear();

    vector<Predicate> GetRulePredicates();

    Predicate GetRuleHead();

    string ToString();
};


#endif //PROJECT_1_RULE_H
