#ifndef PROJECT_1_PREDICATE_H
#define PROJECT_1_PREDICATE_H

#include "Parameter.h"

#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;
using std::stringstream;
using std::endl;

class Predicate {
private:
    string ID = "";
    vector<Parameter> parameters;

public:
    void SetID(string ID);
    string GetID();
    void SetParameters(vector<Parameter> parameters);
    vector<Parameter> GetParameters();

    string ToString();
};


#endif //PROJECT_1_PREDICATE_H
