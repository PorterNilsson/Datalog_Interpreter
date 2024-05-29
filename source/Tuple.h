#ifndef PROJECT_1_TUPLE_H
#define PROJECT_1_TUPLE_H

#include "Parameter.h"

#include <iostream>
#include <vector>
#include <sstream>

using std::string;
using std::vector;
using std::stringstream;
using std::endl;
using std::cout;

class Tuple {
private:
    vector<string> rowValues;

public:
    Tuple() {}

    bool operator< (const Tuple &rhs) const {
        return rowValues < rhs.rowValues;
    }

    string ToString();
    string ToStringSpecial(vector<string> myRelation);

    void SetRowValues(vector<Parameter> parameters);

    string GetValue(int index) const;
    Tuple GetTuple() const;

    Tuple CombineTuple(Tuple toAdd, vector<int> tupleIndexesOne, vector<int> tupleIndexesTwo);
};


#endif //PROJECT_1_TUPLE_H
