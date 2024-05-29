#include "DatalogProgram.h"

string DatalogProgram::ToString() {
    stringstream out;
    out << "Schemes(" << schemes.size() << "):" << endl;
    for (long unsigned int i = 0; i < schemes.size(); ++i) {
        out << "  " << schemes.at(i).ToString() << endl;
    }
    out << "Facts(" << facts.size() << "):" << endl;
    for (long unsigned int i = 0; i < facts.size(); ++i) {
        out << "  " << facts.at(i).ToString() << "." << endl;
    }
    out << "Rules(" << rules.size() << "):" << endl;
    for (long unsigned int i = 0; i < rules.size(); ++i) {
        out << "  " << rules.at(i).ToString() << "." << endl;
    }
    out << "Queries(" << queries.size() << "):" << endl;
    for (long unsigned int i = 0; i < queries.size(); ++i) {
        out << "  " << queries.at(i).ToString() << "?" << endl;
    }
    out << "Domain(" << domain.size() << "):" << endl;
    set<string>::iterator itr;
    for (itr = domain.begin(); itr != domain.end(); ++itr) {
        out << "  " << *itr << endl;
    }

    return out.str();
}

void DatalogProgram::AddScheme(Predicate scheme) {
    schemes.push_back(scheme);
}

void DatalogProgram::AddFact(Predicate fact) {
    facts.push_back(fact);
}

void DatalogProgram::AddQuery(Predicate query) {
    queries.push_back(query);
}

void DatalogProgram::AddRule(Rule rule) {
    rules.push_back(rule);
}

void DatalogProgram::SetDomain(set<string> tempDomain) {
    this->domain = tempDomain;
}

vector<Predicate> DatalogProgram::GetSchemes() {
    return schemes;
}

vector<Predicate> DatalogProgram::GetFacts() {
    return facts;
}

vector<Rule> DatalogProgram::GetRules() {
    return rules;
}

vector<Predicate> DatalogProgram::GetQueries() {
    return queries;
}