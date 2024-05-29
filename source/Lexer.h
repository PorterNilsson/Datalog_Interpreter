#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

using std::endl;
using std::vector;

class Lexer
{
private:
    vector<Automaton*> automata;
    vector<Token*> tokens;

    void CreateAutomata();

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);
    void ToString();

    vector<Token*> GetTokenVector() {
        return tokens;
    }
};

#endif // LEXER_H

