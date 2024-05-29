#include "Rule.h"

void Rule::SetPredicateHead(Predicate head) {
    this->head = head;
}

void Rule::AddBodyPredicate(Predicate body) {
    this->body.push_back(body);
}

void Rule::clear() {
    body.clear();
}

vector<Predicate> Rule::GetRulePredicates() {
    return body;
}

Predicate Rule::GetRuleHead() {
    return head;
}

string Rule::ToString() {
    stringstream out;
    out << head.ToString() << " :- ";
    for (long unsigned int i = 0; i < body.size(); ++i) {
        if (i != body.size() - 1)
        {
            out << body.at(i).ToString() << ",";
        }
        else {
            out << body.at(i).ToString();
        }
    }
    return out.str();
}