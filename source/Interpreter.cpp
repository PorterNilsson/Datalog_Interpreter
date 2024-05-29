#include "Interpreter.h"


Interpreter::Interpreter(DatalogProgram program) {
    this->program = program;
}

void Interpreter::InterpretSchemes() {
    for (Predicate scheme : program.GetSchemes()) {
        Header myHeader;
        myHeader.SetColumnNames(scheme.GetParameters());
        Relation myRelation(scheme.GetID(), myHeader);
        database.AddRelation(myRelation);
    }
}

void Interpreter::InterpretFacts() {
    for (Predicate fact : program.GetFacts()) {
        Tuple myTuple;
        myTuple.SetRowValues(fact.GetParameters());
        database.FindRelation(fact.GetID())->AddTuple(myTuple);
    }
}

void Interpreter::OptimizeRules() {
    dependencyGraph.BuildGraphs(program.GetRules());
    cout << "Dependency Graph" << endl << dependencyGraph.ToString() << endl;

    //cout << "Reverse Dependency Graph" << endl << dependencyGraph.ReverseToString() << endl;

    //Depth First search on the reverse to find the post-order (use a stack)
    dependencyGraph.PostOrderDepthFirstSearch();
    //cout << dependencyGraph.PostOrderToString() << endl;

    //Depth first search on the post-order to find the sccs (return a vector of sets)
    dependencyGraph.SCCDepthFirstSearch();
    //cout << dependencyGraph.SccToString() << endl;
}

vector<set<int>> Interpreter::GetSccVector() {
    return dependencyGraph.GetSccVector();
}

bool Interpreter::InterpretRules(int scc) {
    bool rerun = false;

//    bool testingIteration = false;

    //Run Strongly connected components one set at a time
    vector<Rule> myRules;
    set<int> mySet = dependencyGraph.GetSccVector().at(scc);
    set<int>::iterator itr;
    itr = mySet.begin();
    while (itr != mySet.end()) {

//        cout << "ITR: " << *itr << endl;
//        cout << "ID: " << program.GetRules().at(*itr).GetRuleHead().GetID() << endl;
//        cout << "PROGRAM SIZE: " << program.GetRules().size() << endl;

        myRules.push_back(program.GetRules().at(*itr));

        ++itr;
    }

    for (Rule rule : myRules) {
    //for (Rule rule: program.GetRules()) {

//    for (unsigned int h = 0; h < program.GetRules().size(); ++h) {

        cout << rule.ToString() << "." << endl;

//        if (rule.ToString() == "Transitive(X,Z) :- Transitive(X,Y),Transitive(Y,Z)") {
//            cout << endl << "THIS ITERATION" << endl;
//            testingIteration = true;
//        }

        Relation oldRelation;
        Relation newRelation;
        unsigned int predicateNumber = 0;
        for (Predicate rulePredicate: rule.GetRulePredicates()) {
            //cout << endl << rulePredicate.ToString() << endl;

            newRelation = EvaluatePredicate(rulePredicate);

            //cout << endl << newRelation.TestToString() << endl;

//            newRelation = *database.FindRelation(rulePredicate.GetID());
//            cout << endl << newRelation.TestToString() << endl;

            if (predicateNumber >= 1) {
                //Join

                //cout << newRelation.GetTuples().begin()->GetValue(0) << endl;

                newRelation = oldRelation.Join(newRelation);
            }

            ++predicateNumber;

//            if (testingIteration)
//            {
//                cout << endl << newRelation.GetHeader().ToString() << endl;
//                cout << newRelation.TestToString();
//            }

//            cout << endl << newRelation.GetHeader().ToString() << endl;
//            cout << newRelation.TestToString();

            oldRelation = newRelation;
        }

//        cout << oldRelation.GetHeader().ToString() << endl;
//        cout << oldRelation.TestToString() << endl;

        //Project
        vector<int> columnsToProject;

        for (unsigned int i = 0; i < rule.GetRuleHead().GetParameters().size(); ++i) {
            //cout << endl << rule.GetRuleHead().GetParameters().at(i).ToString() << endl;
            for (int j = 0; j < oldRelation.GetHeader().GetSize(); ++j) {
                //cout << endl << char(tolower(oldRelation.GetHeader().GetName(j)[0])) << endl;

                if (rule.GetRuleHead().GetParameters().at(i).ToString() == oldRelation.GetHeader().GetName(j)) {
                    //cout << endl << "Test: " << j << endl;
                    columnsToProject.push_back(j);
                }
            }
        }

//        Relation newRelation;

        //cout << "TEST: " << oldRelation.TestToString() << endl;

        newRelation = oldRelation.Project(columnsToProject);

        //cout << endl << newRelation.TestToString() << endl;

        //Rename
        vector<string> newColumnNames;
        for (unsigned int k = 0; k < rule.GetRuleHead().GetParameters().size(); ++k) {
            newColumnNames.push_back(rule.GetRuleHead().GetParameters().at(k).ToString());
        }

        newRelation = newRelation.Rename(newColumnNames);

        //cout << endl << newRelation.GetHeader().ToString() << endl;

        //cout << "TEST" << rule.GetRuleHead().GetID() << endl;
        //Union
        if (MyUnion(newRelation, rule.GetRuleHead().GetID())) {
            rerun = true;
        }

//        testingIteration = false;

    }

    bool selfLoop = false;
    if (myRules.size() == 1) {
        for (unsigned int i = 0; i < myRules.at(0).GetRulePredicates().size(); ++i) {

//        cout << "VALUE 1: " << myRules.at(0).GetRulePredicates().at(i).GetID() << endl;
//        cout << "VALUE 2: " << myRules.at(0).GetRuleHead().GetID() << endl;

            if (myRules.at(0).GetRulePredicates().at(i).GetID() == myRules.at(0).GetRuleHead().GetID())
            {
                selfLoop = true;
            }
        }
    }

    if (myRules.size() == 1 && !selfLoop) {
        rerun = false;
    }

    return rerun;
}

bool Interpreter::MyUnion(Relation newRelation, string relationName) {

    for (Tuple tuples: newRelation.GetTuples())
    {
        //cout << endl << newRelation.GetHeader().GetProxyID() << endl;
        if (database.FindRelation(relationName)->AddTuple(tuples)) {
            cout << tuples.ToStringSpecial(database.FindRelation(relationName)->GetHeader().ToStringSpecial()) << endl;
        }
    }

    if (database.FindRelation(relationName)->CheckIfNewTuplesAdded()) {
//        cout << newRelation.ToStringForRules(database.FindRelation(relationName)->GetHeader().ToStringSpecial()) << endl;
//        cout << endl << "TEST" << endl << database.FindRelation(relationName)->TestToString() << endl;
        return true;
    }
    else {
        return false;
    }
}

void Interpreter::InterpretQueries() {
    cout << "Query Evaluation" << endl;
    for (Predicate query : program.GetQueries()) {
        cout << query.ToString() << "? ";
        cout << EvaluatePredicate(query).ToString();
    }
}

Relation Interpreter::EvaluatePredicate(Predicate predicate) {
    Relation* oldRelation = database.FindRelation(predicate.GetID());
    Relation newRelation;

    for (unsigned int i = 0; i < predicate.GetParameters().size(); ++i) {

        if (predicate.GetParameters().at(i).IsConstant()) {
            newRelation = oldRelation->SelectOne(i ,predicate.GetParameters().at(i).ToString());
            oldRelation = &newRelation;
        }
        else {

            bool alreadyEncounteredVariable = false;
            for (unsigned int j = 0; j < variableNames.size(); ++j) {
                if (variableNames.at(j) == predicate.GetParameters().at(j).ToString()) {
                    alreadyEncounteredVariable = true;
                }
            }

            if (alreadyEncounteredVariable) {
                columnNumbers.push_back(i);
                variableNames.push_back(predicate.GetParameters().at(i).ToString());
                variableNamesAndColumnNumbers.insert({predicate.GetParameters().at(i).ToString(), i});

                //int test = variableNamesAndColumnNumbers[predicate.GetParameters().at(i).ToString()];
                //cout << endl << endl << "TEST: " << test << endl << endl;

                newRelation = oldRelation->SelectTwo(variableNamesAndColumnNumbers[predicate.GetParameters().at(i).ToString()], i);
                oldRelation = &newRelation;
            }
            else {
                columnNumbers.push_back(i);
                variableNames.push_back(predicate.GetParameters().at(i).ToString());
                variableNamesAndColumnNumbers.insert({predicate.GetParameters().at(i).ToString(), i});
            }
        }
    }

    //cout << oldRelation->TestToString() << endl;

    newRelation = oldRelation->Project(columnNumbers);
    oldRelation = &newRelation;

    newRelation = oldRelation->Rename(variableNames);
    oldRelation = &newRelation;

    columnNumbers.clear();
    variableNames.clear();
    variableNamesAndColumnNumbers.clear();

    return newRelation;
}

string Interpreter::DatabaseToString() {
    return database.ToString();
}

string Interpreter::GetGraphString(int index) {
    stringstream out;

    set<int> mySet = dependencyGraph.GetSccVector().at(index);
    set<int>::iterator itr;
    itr = mySet.begin();
    while (itr != mySet.end()) {
        out << "R" << *itr;

        if (++itr != mySet.end()) {
            out << ",";
        }
    }

    return out.str();
}