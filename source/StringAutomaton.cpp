#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'' || inputRead > 0) {
        if (input[index] == '\n') {
            newLines++;
        }
        if (input[index] == '\'' && inputRead != 0) {
            S1(input);
        }
        else if (index == input.size())
        {
            Serr();
        }
        else {
            inputRead++;
            index++;
            S0(input);
        }
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (input[index + 1] == '\'') {
        inputRead += 2;
        index += 2;
        S0(input);
    }
    else {
        inputRead++;
        index++;
        return;
    }
}