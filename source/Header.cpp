#include "Header.h"

string Header::GetName(int index) {
    return columnNames.at(index);
}

void Header::SetColumnNames(vector<Parameter> parameters) {
    for (unsigned int i = 0; i < parameters.size(); ++i) {
        columnNames.push_back(parameters.at(i).ToString());
    }
}

int Header::GetSize() {
    return columnNames.size();
}

vector<string> Header::GetColumnNames() {
    return columnNames;
}

Header Header::SetHeader(Header rhs) {
    tupleIndexesOne.clear();
    tupleIndexesTwo.clear();

    vector<int> indexesToErase;
    for (unsigned int i = 0; i < this->columnNames.size(); ++i) {
        for (unsigned int j = 0; j < rhs.columnNames.size(); ++j) {

            if (rhs.columnNames.at(j) == this->columnNames.at(i)) {
                //cout << "TEST: " << i << " " << j << endl;

                //cout << "TEST: " << this->columnNames.at(i) << rhs.columnNames.at(j) << endl;

                tupleIndexesOne.push_back(i);
                tupleIndexesTwo.push_back(j);
                indexesToErase.push_back(j);
            }
        }
    }
//
//    cout << "Test 1" << endl;

    for (unsigned int i = 0; i < indexesToErase.size(); ++i) {
        rhs.columnNames.at(indexesToErase.at(i)) = "codeWord";
    }
    for (unsigned int i = 0; i < rhs.columnNames.size(); ++i) {
        if (rhs.columnNames.at(i) == "codeWord") {
            rhs.columnNames.erase(rhs.columnNames.begin() + i);
            --i;
        }
    }

//    cout << "Test 2" << endl;

    for (unsigned int i = 0; i < rhs.columnNames.size(); ++i) {
        this->columnNames.push_back(rhs.columnNames.at(i));
    }

    return *this;
}

vector<int> Header::GetTupleIndexes(int vectorNumber) {
    if (vectorNumber == 1) {
        return tupleIndexesOne;
    }
    else {
        return tupleIndexesTwo;
    }
}

string Header::ToString() {
    stringstream out;

    for (unsigned int i = 0; i < this->columnNames.size(); ++i) {
        out << columnNames.at(i) << " ";
    }

    return out.str();
}

vector<string> Header::ToStringSpecial() {
    return columnNames;
}
