#include "Relation.h"

Relation::Relation() {
    name = "";
}

Relation::Relation(Header columnNames) {
    this->columnNames = columnNames;
}

Relation::Relation(string name, Header columnNames) {
    this->name = name;
    this->columnNames = columnNames;
}

string Relation::GetName() {
    return name;
}

bool Relation::AddTuple(Tuple newTuple) {
    if(this->tuples.insert(newTuple).second) {
        newTuplesAdded = true;
        return true;
    }
    else {
        return false;
    }
}

string Relation::ToString() {
    stringstream out;
    if (tuples.size() > 0) {
        out << "Yes(" << tuples.size() << ")" << endl;
    }
    else {
        out << "No" << endl;
    }

    if (columnNames.GetSize() != 0)
    {
        set<Tuple>::iterator it = tuples.begin();
        while (it != tuples.end())
        {
            out << "  ";

            vector<string> alreadyDone;

            for (int i = 0; i < columnNames.GetSize(); ++i)
            {
                bool testAlreadyDone = false;
                for (unsigned int j = 0; j < alreadyDone.size(); ++j) {
                    if (alreadyDone.at(j) == columnNames.GetName(i)) {
                        testAlreadyDone = true;
                    }
                }

                if (!testAlreadyDone)
                {
                    if (i != 0)
                    {
                        out << ", ";
                    }

                    out << columnNames.GetName(i) << "=" << it->GetTuple().GetValue(i);

                    alreadyDone.push_back(columnNames.GetName(i));
                }

//                if (i != columnNames.GetSize() - 1 && !testAlreadyDone)
//                {
//                    out << ", ";
//                }
            }
            out << endl;
            ++it;
        }
    }

    return out.str();
}

Relation Relation::SelectOne(int columnIndex, string value) {
    Relation myRelation;

    set<Tuple>::iterator it = tuples.begin();
    while (it != tuples.end()) {
        if (it->GetValue(columnIndex) == value) {
            myRelation.AddTuple(it->GetTuple());
        }
        ++it;
    }

    //cout << endl << endl << "TEST SELECT ONE" << endl << myRelation.TestToString() << endl;

    return myRelation;
}

Relation Relation::SelectTwo(int columnIndexOne, int columnIndexTwo) {
    Relation myRelation;

    set<Tuple>::iterator it = tuples.begin();
    while (it != tuples.end()) {
        if (it->GetValue(columnIndexOne) == it->GetValue(columnIndexTwo))
        {
            myRelation.AddTuple(it->GetTuple());
        }
        ++it;
    }

    //cout << endl << endl << "TEST SELECT TWO" << endl << myRelation.TestToString() << endl;

    return myRelation;
}

Relation Relation::Project(vector<int> columnsToProject) {
    Relation myRelation;

    //cout << endl << "SIZE: " << columnsToProject.size() << endl;

    set<Tuple>::iterator it = tuples.begin();
    while (it != tuples.end()) {

        //cout << endl << endl << "COLUMnS TO PROJECT: " << columnsToProject.size() << endl;

        vector<Parameter> projection;
        for (unsigned int i = 0; i < columnsToProject.size(); ++i) {

            //cout << endl << endl << "COLUMN VALUE: " << columnsToProject << endl

            projection.push_back(it->GetValue(columnsToProject.at(i)));
        }

        Tuple newTuple;
        newTuple.SetRowValues(projection);
        myRelation.AddTuple(newTuple);

        ++it;
    }

    //cout << endl << endl << "TEST PROJECT" << endl << myRelation.TestToString() << endl;

    return myRelation;


}

Relation Relation::Rename(vector<string> newColumnNames) {
    Relation myRelation = *this;
    vector<Parameter> parameters;

    for (unsigned int i = 0; i < newColumnNames.size(); ++i) {
        Parameter myParameter(newColumnNames.at(i));
        parameters.push_back(myParameter);
    }

    myRelation.columnNames.SetColumnNames(parameters);

    //cout << endl << endl << "TEST RENAME" << endl << myRelation.TestToString() << endl;

    return myRelation;
}

Relation Relation::Join(Relation relationToAdd) {
    //	make the header h for the result relation
    //	    (combine r1's header with r2's header)
    //
    Header newHeader;
    newHeader = this->columnNames.SetHeader(relationToAdd.columnNames);
    //cout << endl << newHeader.ToString() << endl;

    //	make a new empty relation r using header h
    //
    Relation newRelation(newHeader);
    //cout << endl << relationToAdd.GetName() << endl << this->GetName() << endl;


    //	for each tuple t1 in r1
    //	    for each tuple t2 in r2
    //
    //		if t1 and t2 can join
    //		    join t1 and t2 to make tuple t
    //		    add tuple t to relation r
    //		end if
    //
    //	    end for
    //	end for

//    cout << tuples.size() << endl;

//    cout << this->tuples.begin()->GetValue(0) << endl;
//    cout << this->tuples.size() << endl;
//    cout << this->tuples.begin() << endl;
//    cout << relationToAdd.tuples.size() << endl;

    for (Tuple tupleOne : this->tuples) {
        for (Tuple tupleTwo : relationToAdd.tuples) {


            if (IsJoinable(tupleOne, tupleTwo, newRelation.columnNames.GetTupleIndexes(1), newRelation.columnNames.GetTupleIndexes(2))) {
                //cout << endl << tupleOne.ToString() << endl << tupleTwo.ToString() << endl;

                newRelation.AddTuple(tupleOne.CombineTuple(tupleTwo, newRelation.columnNames.GetTupleIndexes(1), newRelation.columnNames.GetTupleIndexes(2)));
            }
        }
    }

//    cout << endl << endl << newRelation.columnNames.ToString() << endl;
//    cout << endl << endl << newRelation.TestToString() << endl << endl;

    return newRelation;
}

bool Relation::IsJoinable(Tuple one, Tuple two, vector<int> tupleIndexesOne, vector<int> tupleIndexesTwo) {
//    cout << one.GetValue(0) << one.GetValue(1) << endl;
//    cout << two.GetValue(0) << two.GetValue(1) << endl;
//    cout << tupleIndexesOne.at(0) << tupleIndexesTwo.at(0) << endl;

//    cout << one.GetValue(tupleIndexesOne.at(checkIfJoinable)) << endl;
//    cout << two.GetValue(tupleIndexesTwo.at(checkIfJoinable)) << endl;

//    if (one.GetValue(tupleIndexesOne.at(0)) == two.GetValue(tupleIndexesTwo.at(0))) {
//        //cout << "TEST" << endl;
//        return true;
//    }
//    else {
//        return false;
//    }

    for (unsigned int i = 0; i < tupleIndexesOne.size(); ++i) {
        if (one.GetValue(tupleIndexesOne.at(i)) != two.GetValue(tupleIndexesTwo.at(i))) {
            return false;
        }
    }

    return true;
}

Header Relation::GetHeader() {
    return columnNames;
}

set<Tuple> Relation::GetTuples() {
    return tuples;
}

string Relation::TestToString() {
    stringstream out;

    unsigned int i = 0;
    for (Tuple myTuple : tuples)
    {
        //out << columnNames.GetNames() << "=" << myTuple.ToString() << ",";
        out << myTuple.ToString() << " " << i << endl;
        ++i;
    }
    out << endl;

    string myString = out.str();
    if (out.str().size() != 0)
    {
        myString.pop_back();
    }
    return myString;
}

string Relation::ToStringForRules(string myStr) {
    stringstream out;

    if (columnNames.GetSize() != 0)
    {
        set<Tuple>::iterator it = tuples.begin();
        while (it != tuples.end())
        {
            out << "  ";

            vector<string> alreadyDone;

            for (int i = 0; i < columnNames.GetSize(); ++i)
            {
                bool testAlreadyDone = false;
                for (unsigned int j = 0; j < alreadyDone.size(); ++j) {
                    if (alreadyDone.at(j) == columnNames.GetName(i)) {
                        testAlreadyDone = true;
                    }
                }

                if (!testAlreadyDone)
                {
                    if (i != 0)
                    {
                        out << ", ";
                    }

                    out << myStr[i] << "=" << it->GetTuple().GetValue(i);

                    alreadyDone.push_back(columnNames.GetName(i));
                }

//                if (i != columnNames.GetSize() - 1 && !testAlreadyDone)
//                {
//                    out << ", ";
//                }
            }
            out << endl;
            ++it;
        }
    }

    string str = out.str();
    str.pop_back();

    return str;
}

bool Relation::CheckIfNewTuplesAdded() {
    if (newTuplesAdded) {
        newTuplesAdded = false;
        return true;
    }
    else {
        return false;
    }
}


