#include "Tuple.h"

string Tuple::ToString() {
    stringstream out;
    for (string myString : rowValues) {
        out << myString << " ";
    }
    return out.str();
}

void Tuple::SetRowValues(vector<Parameter> parameters) {
    for (unsigned int i = 0; i < parameters.size(); ++i) {
        rowValues.push_back(parameters.at(i).ToString());
    }
}

string Tuple::GetValue(int index) const {
//    if (rowValues.size() > index)
//    {
//        return rowValues.at(index);
//    }
    return rowValues.at(index);
}

Tuple Tuple::GetTuple() const {
    return *this;
}

Tuple Tuple::CombineTuple(Tuple toAdd, vector<int> tupleIndexesOne, vector<int> tupleIndexesTwo) {
    Tuple newTuple;
//
//    cout << "TUPLES" << endl;
//    cout << this->ToString() << endl;
//    cout << toAdd.ToString() << endl;

//    for (unsigned int i = 0; i < tupleIndexesOne.size(); ++i) {
//        cout << tupleIndexesOne.at(i) << " " << tupleIndexesTwo.at(i) << endl;
//    }
//    cout << endl;

    //cout << "TEST" << endl;

//    for (unsigned int i = 0; i < tupleIndexesOne.size(); ++i) {
//
//        cout << this->rowValues.at(tupleIndexesOne.at(i)) << endl;
//        cout << toAdd.rowValues.at(tupleIndexesTwo.at(i)) << endl;
//
//        if (this->rowValues.at(tupleIndexesOne.at(i)) != toAdd.rowValues.at(tupleIndexesTwo.at(i))) {
//            cannotCombine = true;
//        }
//    }

    //cout << "TESTTWO" << endl;

    for (unsigned int i = 0; i < this->rowValues.size(); ++i) {
        newTuple.rowValues.push_back(this->rowValues.at(i));
    }

    //cout << "TESTTHREE" << endl;
    bool doNotAdd = false;
    for (unsigned int i = 0; i < toAdd.rowValues.size(); ++i) {
        for (unsigned int j = 0; j < tupleIndexesTwo.size(); ++j) {
            if (tupleIndexesTwo.at(j) == (int)i) {
                doNotAdd = true;
            }
        }

        if (doNotAdd == false) {
            newTuple.rowValues.push_back(toAdd.rowValues.at(i));
        }
        else {
            doNotAdd = false;
        }
    }

        //cout << "TESTFOUR" << endl;

        //cout << newTuple.ToString() << endl;

    return newTuple;
}

string Tuple::ToStringSpecial(vector<string> myRelation) {
    stringstream out;

    out << "  ";

    for (unsigned int i = 0; i < rowValues.size(); ++i) {
        if (i != 0) {
            out << " ";
        }
        out << myRelation.at(i) << "=" << rowValues.at(i);
        if (i != rowValues.size() - 1) {
            out << ",";
        }
    }

    return out.str();
}