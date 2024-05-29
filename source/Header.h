#ifndef PROJECT_1_HEADER_H
#define PROJECT_1_HEADER_H

#include "Parameter.h"

#include <iostream>
#include <vector>
#include <sstream>

using std::string;
using std::vector;
using std::stringstream;
using std::endl;
using std::cout;

class Header {
private:
    vector<string> columnNames;
    vector<int> tupleIndexesOne;
    vector<int> tupleIndexesTwo;

public:
    string GetName(int index);
    void SetColumnNames(vector<Parameter> parameters);

    int GetSize();

    vector<string> GetColumnNames();
    Header SetHeader(Header rhs);

    vector<int> GetTupleIndexes(int vectorNumber);

    string ToString();
    vector<string> ToStringSpecial();
};

#endif //PROJECT_1_HEADER_H
