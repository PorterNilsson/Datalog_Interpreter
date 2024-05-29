#ifndef PROJECT_1_RELATION_H
#define PROJECT_1_RELATION_H

#include "Header.h"
#include "Tuple.h"

#include <iostream>
#include <set>

using std::string;
using std::set;
using std::endl;
using std::cout;

class Relation {
private:
    string name;
    Header columnNames;
    set<Tuple> tuples;
    bool newTuplesAdded = false;

public:
    Relation();
    Relation(Header columnNames);
    Relation(string name, Header columnNames);

    string GetName();

    bool AddTuple(Tuple newTuple);

    string ToString();
    string TestToString();

    Relation SelectOne(int columnIndex, string value);
    Relation SelectTwo(int columnIndexOne, int columnIndexTwo);
    Relation Project(vector<int> columnsToProject);
    Relation Rename(vector<string> newColumnNames);

    Relation Join(Relation relationToAdd);
    Header GetHeader();

    bool IsJoinable(Tuple one, Tuple two, vector<int> tupleIndexesOne, vector<int> tupleIndexesTwo);

    set<Tuple> GetTuples();

    string ToStringForRules(string str);

    bool CheckIfNewTuplesAdded();

};


#endif //PROJECT_1_RELATION_H
