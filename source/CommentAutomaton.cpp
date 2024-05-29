#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#' && input[index + 1] != '|') {
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    bool badComment = false;
    while (input[index + 1] != '\n') {
        if (index == input.size()) {
            Serr();
            badComment = true;
            break;
        }
        index++;
        inputRead++;
    }
    if (!badComment)
    {
        ++index;
        ++inputRead;
    }
}