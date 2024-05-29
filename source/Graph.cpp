#include "Graph.h"

void Graph::BuildGraphs(vector<Rule> programRules) {
    set<int> mySetTwo;
    vector<set<int>> reverseSets(programRules.size(), mySetTwo);

    for (unsigned int i = 0; i < programRules.size(); ++i) {

        set<int> mySet;
        for (unsigned int j = 0; j < programRules.at(i).GetRulePredicates().size(); ++j) {
            for (unsigned int k = 0; k < programRules.size(); ++k) {
                if (programRules.at(k).GetRuleHead().GetID() == programRules.at(i).GetRulePredicates().at(j).GetID()) {
                    //cout << "test: " << endl;
                    mySet.insert(k);

                    reverseSets.at(k).insert(i);
                }
            }
        }

        adjacencyList.insert({i, mySet});
    }

    for (unsigned int i = 0; i < reverseSets.size(); ++i) {
        reverseAdjacencyList.insert({i, reverseSets.at(i)});
    }
}

void Graph::PostOrderDepthFirstSearch() {

    vector<bool> myVector(reverseAdjacencyList.size(), false);
    visited.clear();
    visited = myVector;

    for (unsigned int i = 0; i < reverseAdjacencyList.size(); ++i) {
        if (!visited.at(i))
        {
            depthFirstSearchForPostOrder.push(i);
            //cout << "TEST: " << i << endl;
            IterateThroughEdges(i);
        }
        while (depthFirstSearchForPostOrder.size() != 0) {

//            cout << "SIZE: " << depthFirstSearchForPostOrder.size() << endl;
            cout << "TOP: " << depthFirstSearchForPostOrder.top() << endl;

            reversePostOrder.push(depthFirstSearchForPostOrder.top());
            depthFirstSearchForPostOrder.pop();
        }
    }

    while (reversePostOrder.size() != 0) {
        postOrder.push_back(reversePostOrder.top());
        reversePostOrder.pop();
    }

}

void Graph::IterateThroughEdges(int head) {

//    cout << endl << "HEAD: " << head << endl;
    visited.at(head) = true;

    set<int>::iterator itr;
    itr = reverseAdjacencyList.at(head).begin();

    while (reverseAdjacencyList.at(head).end() != itr) {
//        cout << "ITR: " << *itr << endl;

        if (!visited.at(*itr)) {
            depthFirstSearchForPostOrder.push(*itr);
            //cout << "TEST: " << *itr << endl;
            IterateThroughEdges(*itr);
        }
        ++itr;
    }

    reversePostOrder.push(depthFirstSearchForPostOrder.top());
    depthFirstSearchForPostOrder.pop();
}

void Graph::SCCDepthFirstSearch() {
    vector<bool> myVector(postOrder.size(), false);
    visited = myVector;

    for (unsigned int i = 0; i < postOrder.size(); ++i) {
        if (!visited.at(postOrder.at(i)))
        {
            scc.insert(postOrder.at(i));
            //cout << "TEST SCC: " << postOrder.at(i) << endl;
            IterateThroughEdgesScc(postOrder.at(i));
            stronglyConnectedComponents.push_back(scc);
            scc.clear();
        }
    }
}

void Graph::IterateThroughEdgesScc(int head) {
    //cout << "HEAD: " << head << endl;
    visited.at(head) = true;

    set<int>::iterator itr;
    itr = adjacencyList.at(head).begin();

    while (itr != adjacencyList.at(head).end()) {
        //cout << "ITR: " << *itr << endl;

        if (!visited.at(*itr)) {
            scc.insert(*itr);
            //cout << "TEST: " << *itr << endl;
            IterateThroughEdgesScc(*itr);
        }
        ++itr;
    }
}

vector<set<int>> Graph::GetSccVector() {
    return stronglyConnectedComponents;
}

string Graph::ToString() {
    stringstream out;

    for (unsigned int i = 0; i < adjacencyList.size(); ++i) {
        out << "R" << i << ":";

        set<int>::iterator itr;
        itr = adjacencyList.at(i).begin();

        unsigned int k = 0;
        while (itr != adjacencyList.at(i).end()) {
            out << "R" << *itr;

            if (k != adjacencyList.at(i).size() - 1) {
                out << ",";
            }

            ++itr;
            ++k;
        }

        out << endl;
    }

    return out.str();
}

string Graph::ReverseToString() {
    stringstream out;

    for (unsigned int i = 0; i < reverseAdjacencyList.size(); ++i) {
        out << "R" << i << ":";

        set<int>::iterator itr;
        itr = reverseAdjacencyList.at(i).begin();

        unsigned int k = 0;
        while (itr != reverseAdjacencyList.at(i).end()) {
            out << "R" << *itr;

            if (k != reverseAdjacencyList.at(i).size() - 1) {
                out << ",";
            }

            ++itr;
            ++k;
        }

        out << endl;
    }

    return out.str();
}

string Graph::PostOrderToString() {
    stringstream out;

    out << "Post-Order: ";

    for (unsigned int i = 0; i < postOrder.size(); ++i) {
        out << postOrder.at(i) << " ";
    }

    out << endl;

    return out.str();
}

string Graph::SccToString() {
    stringstream out;

    out << "Strongly Connected Components: " << endl;

    for (unsigned int i = 0; i < stronglyConnectedComponents.size(); ++i) {

        out << "SCC " << i << ": ";

        set<int>::iterator itr;
        itr = stronglyConnectedComponents.at(i).begin();
        while (itr != stronglyConnectedComponents.at(i).end()) {
            out << "R" << *itr << ",";
            ++itr;
        }

        out << endl;
    }

    return out.str();
}