#include "Predicate.h"

void Predicate::SetID(string ID) {
    this->ID = ID;
}

void Predicate::SetParameters(vector<Parameter> parameters) {
    this->parameters = parameters;
}

string Predicate::ToString() {
    stringstream out;
    out << ID << "(";
    for (unsigned int i = 0; i < parameters.size(); ++i) {
        if (i != parameters.size() - 1)
        {
            out << parameters.at(i).ToString() << ",";
        }
        else {
            out << parameters.at(i).ToString();
        }
    }
    out << ")";
    return out.str();
}

string Predicate::GetID() {
    return ID;
}

vector<Parameter> Predicate::GetParameters() {
    return parameters;
}