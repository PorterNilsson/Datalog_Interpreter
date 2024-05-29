#ifndef PROJECT_1_GRAPH_H
#define PROJECT_1_GRAPH_H

#include "Rule.h"

#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <stack>

using std::set;
using std::map;
using std::vector;
using std::cout;
using std::stack;

class Graph {
private:
    map<int, set<int> > adjacencyList;
    map<int, set<int> > reverseAdjacencyList;

    vector<bool> visited;
    stack<int> depthFirstSearchForPostOrder;
    stack<int> reversePostOrder;
    vector<int> postOrder;

    set<int> scc;
    vector<set<int> > stronglyConnectedComponents;

public:
    void BuildGraphs(vector<Rule> programRules);

    void PostOrderDepthFirstSearch();
    void IterateThroughEdges(int head);

    void SCCDepthFirstSearch();
    void IterateThroughEdgesScc(int head);

    vector<set<int> > GetSccVector();

    string ToString();
    string ReverseToString();
    string PostOrderToString();
    string SccToString();

};


#endif //PROJECT_1_GRAPH_H
