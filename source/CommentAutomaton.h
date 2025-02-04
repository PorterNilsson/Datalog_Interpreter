#ifndef PROJECT_1_COMMENTAUTOMATON_H
#define PROJECT_1_COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}

    void S0(const std::string& input);
};


#endif //PROJECT_1_COMMENTAUTOMATON_H
