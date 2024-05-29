#ifndef PROJECT_1_PARAMETER_H
#define PROJECT_1_PARAMETER_H

#include <string>

using std::string;

class Parameter {
private:
    string p;

public:
    Parameter(string p);

    bool IsConstant();
    string ToString();

    char ToChar();
};


#endif //PROJECT_1_PARAMETER_H
