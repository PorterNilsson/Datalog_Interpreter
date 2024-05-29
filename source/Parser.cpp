#include "Parser.h"

Parser::Parser(vector<Token*> tokens) {
    this->tokens = tokens;
}

void Parser::Parse() {
    for (unsigned int i = 0; i < tokens.size(); ++i) {
        if (tokens.at(i)->GetTokenType() == TokenType::COMMENT
            || tokens.at(i)->GetTokenType() == TokenType::UNDEFINED) {
            tokens.erase(tokens.begin() + i);
            i--;
        }
    }

//    for (unsigned int i = 0; i < tokens.size(); ++i) {
//        cout << tokens.at(i)->ToString() << endl;
//    }
//
//    cout << endl;

    ParseDatalogProgram();
}

void Parser::ParseDatalogProgram() {
    //SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF

    //SCHEMES
    if (tokens.at(input)->GetTokenType() == TokenType::SCHEMES) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //COLON
    if (tokens.at(input)->GetTokenType() == TokenType::COLON) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //scheme
    ParseScheme();

    //schemeList
    ParseSchemeList();

    //FACTS
    if (tokens.at(input)->GetTokenType() == TokenType::FACTS) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //COLON
    if (tokens.at(input)->GetTokenType() == TokenType::COLON) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //factList
    ParseFactList();

    //RULES
    if (tokens.at(input)->GetTokenType() == TokenType::RULES) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //COLON
    if (tokens.at(input)->GetTokenType() == TokenType::COLON) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //ruleList
    ParseRuleList();

    //QUERIES
    if (tokens.at(input)->GetTokenType() == TokenType::QUERIES) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //COLON
    if (tokens.at(input)->GetTokenType() == TokenType::COLON) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //query
    ParseQuery();

    //queryList
    ParseQueryList();

    //EOF
    if (tokens.at(input)->GetTokenType() == TokenType::EOF_TYPE) {
//        cout << "Success!" << endl;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }
}

void Parser::ParseScheme() {
    //ID LEFT_PAREN ID idList RIGHT_PAREN

    //ID
    if (tokens.at(input)->GetTokenType() == TokenType::ID) {
        tempID = tokens.at(input)->GetTokenString();
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //LEFT_PAREN
    if (tokens.at(input)->GetTokenType() == TokenType::LEFT_PAREN) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //ID
    if (tokens.at(input)->GetTokenType() == TokenType::ID) {
        Parameter p(tokens.at(input)->GetTokenString());
        tempParameters.push_back(p);
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //idList
    ParseIdList();

    //RIGHT_PAREN
    if (tokens.at(input)->GetTokenType() == TokenType::RIGHT_PAREN) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    tempPredicate.SetID(tempID);
    tempPredicate.SetParameters(tempParameters);
    program.AddScheme(tempPredicate);
    tempParameters.clear();
}

void Parser::ParseIdList() {
    //COMMA ID idList | lambda

    //COMMA
    if (tokens.at(input)->GetTokenType() == TokenType::COMMA) {
        input++;
    }
    else {
        return;
    }

    //ID
    if (tokens.at(input)->GetTokenType() == TokenType::ID) {
        Parameter p(tokens.at(input)->GetTokenString());
        tempParameters.push_back(p);
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //idList
    ParseIdList();

}

void Parser::ParseSchemeList() {
    //scheme schemeList | lambda

    if (tokens.at(input)->GetTokenType() == TokenType::ID) {

    //scheme
        ParseScheme();

    //schemeList
        ParseSchemeList();
    }
}

void Parser::ParseFactList() {
    //fact factList | lambda

    if (tokens.at(input)->GetTokenType() == TokenType::ID) {

    //fact
        ParseFact();

    //factList
        ParseFactList();
    }
}

void Parser::ParseFact() {
    //ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD

    //ID
    if (tokens.at(input)->GetTokenType() == TokenType::ID) {
        tempID = tokens.at(input)->GetTokenString();
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //LEFT_PAREN
    if (tokens.at(input)->GetTokenType() == TokenType::LEFT_PAREN) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //STRING
    if (tokens.at(input)->GetTokenType() == TokenType::STRING) {
        Parameter p(tokens.at(input)->GetTokenString());
        tempParameters.push_back(p);
        tempDomain.insert(tokens.at(input)->GetTokenString());
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //stringList
    ParseStringList();

    //RIGHT_PAREN
    if (tokens.at(input)->GetTokenType() == TokenType::RIGHT_PAREN) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //PERIOD
    if (tokens.at(input)->GetTokenType() == TokenType::PERIOD) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    tempPredicate.SetID(tempID);
    tempPredicate.SetParameters(tempParameters);
    program.AddFact(tempPredicate);
    tempParameters.clear();
    program.SetDomain(tempDomain);
}

void Parser::ParseStringList() {
    //COMMA STRING stringList | lambda

    //COMMA
    if (tokens.at(input)->GetTokenType() == TokenType::COMMA) {
        input++;
    }
    else {
        return;
    }

    //STRING
    if (tokens.at(input)->GetTokenType() == TokenType::STRING) {
        Parameter p(tokens.at(input)->GetTokenString());
        tempParameters.push_back(p);
        tempDomain.insert(tokens.at(input)->GetTokenString());
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //stringList
    ParseStringList();
}

void Parser::ParseRuleList() {
    //rule ruleList | lambda

    if (tokens.at(input)->GetTokenType() == TokenType::ID) {

    //rule
        ParseRule();

    //ruleList
        ParseRuleList();
    }
}

void Parser::ParseRule() {
    //headPredicate COLON_DASH predicate predicateList PERIOD

    //headPredicate
    ParseHeadPredicate();

    tempPredicate.SetID(tempID);
    tempPredicate.SetParameters(tempParameters);
    tempRule.SetPredicateHead(tempPredicate);
    tempParameters.clear();

    //COLON_DASH
    if (tokens.at(input)->GetTokenType() == TokenType::COLON_DASH) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //predicate
    ParsePredicate();

    //predicateList
    ParsePredicateList();

    //PERIOD
    if (tokens.at(input)->GetTokenType() == TokenType::PERIOD) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    program.AddRule(tempRule);
    tempRule.clear();
    tempParameters.clear();
}

void Parser::ParseHeadPredicate() {
    //ID LEFT_PAREN ID idList RIGHT_PAREN

    //ID
    if (tokens.at(input)->GetTokenType() == TokenType::ID) {
        tempID = tokens.at(input)->GetTokenString();
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //LEFT_PAREN
    if (tokens.at(input)->GetTokenType() == TokenType::LEFT_PAREN) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //ID
    if (tokens.at(input)->GetTokenType() == TokenType::ID) {
        Parameter p(tokens.at(input)->GetTokenString());
        tempParameters.push_back(p);
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //idList
    ParseIdList();

    //RIGHT_PAREN
    if (tokens.at(input)->GetTokenType() == TokenType::RIGHT_PAREN) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }
}

void Parser::ParsePredicate() {
    //ID LEFT_PAREN parameter parameterList RIGHT_PAREN

    //ID
    if (tokens.at(input)->GetTokenType() == TokenType::ID) {
        tempID = tokens.at(input)->GetTokenString();
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //LEFT_PAREN
    if (tokens.at(input)->GetTokenType() == TokenType::LEFT_PAREN) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    //parameter
    ParseParameter();

    //parameterList
    ParseParameterList();

    //RIGHT_PAREN
    if (tokens.at(input)->GetTokenType() == TokenType::RIGHT_PAREN) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    if (!query)
    {
        tempPredicate.SetID(tempID);
        tempPredicate.SetParameters(tempParameters);
        tempRule.AddBodyPredicate(tempPredicate);
        tempParameters.clear();
    }

}

void Parser::ParseParameter() {
    //STRING | ID

    //STRING
    if (tokens.at(input)->GetTokenType() == TokenType::STRING) {
        Parameter p(tokens.at(input)->GetTokenString());
        tempParameters.push_back(p);
        input++;
    }
    //ID
    else if (tokens.at(input)->GetTokenType() == TokenType::ID) {
        Parameter p(tokens.at(input)->GetTokenString());
        tempParameters.push_back(p);
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }
}

void Parser::ParseParameterList() {
    //COMMA parameter parameterList | lambda

    //COMMA
    if (tokens.at(input)->GetTokenType() == TokenType::COMMA) {
        input++;
    }
    else {
        return;
    }

    //parameter
    ParseParameter();

    //parameterList
    ParseParameterList();
}

void Parser::ParsePredicateList() {
    //COMMA predicate predicateList | lambda

    //COMMA
    if (tokens.at(input)->GetTokenType() == TokenType::COMMA) {
        input++;
    }
    else {
        return;
    }

    //predicate
    ParsePredicate();

    //predicateList
    ParsePredicateList();
}

void Parser::ParseQuery() {
    query = true;

    //predicate Q_MARK

    //predicate
    ParsePredicate();

    //Q_MARK
    if (tokens.at(input)->GetTokenType() == TokenType::Q_MARK) {
        input++;
    }
    else {
        throw string("Failure!\n  " + tokens.at(input)->ToString());
    }

    tempPredicate.SetID(tempID);
    tempPredicate.SetParameters(tempParameters);
    program.AddQuery(tempPredicate);
    tempParameters.clear();
}

void Parser::ParseQueryList() {
    //query queryList | lambda

    if (tokens.at(input)->GetTokenType() == TokenType::ID) {

        //query
        ParseQuery();

        //queryList
        ParseQueryList();
    }
}

string Parser::ToString() {
    return program.ToString();
}

DatalogProgram Parser::GetDatalogProgram() {
    return program;
}