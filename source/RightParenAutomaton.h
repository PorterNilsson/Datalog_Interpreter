#ifndef PROJECT_1_RIGHTPARENAUTOMATON_H
#define PROJECT_1_RIGHTPARENAUTOMATON_H

#include "Automaton.h"

class RightParenAutomaton : public Automaton
{
public:
    RightParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}

    void S0(const std::string& input);
};

#endif //PROJECT_1_RIGHTPARENAUTOMATON_H
