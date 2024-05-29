#ifndef PROJECT_1_MULTICOMMENTAUTOMATON_H
#define PROJECT_1_MULTICOMMENTAUTOMATON_H

#include "Automaton.h"

class MultiCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);

public:
    MultiCommentAutomaton() : Automaton(TokenType::COMMENT) {}

    void S0(const std::string& input);
};


#endif //PROJECT_1_MULTICOMMENTAUTOMATON_H
