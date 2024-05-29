#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Parameter.h"

#include <vector>

using std::vector;
using std::endl;

class Parser {
private:
    vector<Token*> tokens;
    DatalogProgram program;
    int input = 0;

    void ParseDatalogProgram();
    void ParseScheme();
    void ParseIdList();
    void ParseSchemeList();
    void ParseFactList();
    void ParseFact();
    void ParseStringList();
    void ParseRuleList();
    void ParseRule();
    void ParseHeadPredicate();
    void ParsePredicate();
    void ParseParameter();
    void ParseParameterList();
    void ParsePredicateList();
    void ParseQuery();
    void ParseQueryList();

    Predicate tempPredicate;
    string tempID = "";
    vector<Parameter> tempParameters;

    Rule tempRule;
    bool query = false;

    set<string> tempDomain;

public:
    Parser(vector<Token*> tokens);

    void Parse();
    string ToString();

    DatalogProgram GetDatalogProgram();
};


#endif //PROJECT_1_PARSER_H
