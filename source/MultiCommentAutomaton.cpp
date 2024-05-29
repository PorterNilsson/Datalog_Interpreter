#include "MultiCommentAutomaton.h"


void MultiCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#' && input[index + 1] == '|') {
        index+= 2;
        inputRead+= 2;
        S1(input);
    }
    else {
        Serr();
    }
}

void MultiCommentAutomaton::S1(const std::string& input) {
    if (index == input.size()) {
        Serr();
    }
    else
    {
        if (input[index] == '|')
        {
            ++index;
            ++inputRead;
            S2(input);
        }
        else
        {
            if (input[index] == '\n') {
                newLines++;
            }
            ++index;
            ++inputRead;
            S1(input);
        }
    }
}

void MultiCommentAutomaton::S2(const std::string& input) {
    if (index == input.size()) {
        Serr();
    }
    else
    {
        if (input[index] == '#')
        {
            index++;
            inputRead++;
        }
        else
        {
            if (input[index] == '\n') {
                newLines++;
            }
            index++;
            inputRead++;
            S1(input);
        }
    }
}