#include "Lexer.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QuestionMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IdAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "MultiCommentAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
//    for (Automaton* automata : automata)
//    {
//        delete automata;
//    }
    for (Token* token : tokens)
    {
        delete token;
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QuestionMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IdAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new MultiCommentAutomaton());
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    while (input.size() > 0) {

        //Testing for whitespace and line counter
        bool found = true;
        bool endingSpace = false;
        while (found) {
            found = false;
            if (input[0] == '\n')
            {
                lineNumber++;
                if (input.size() > 1) {
                    found = true;
                }
                if (input.size() == 1) {
                    endingSpace = true;
                }
                input = input.substr(1, input.size() - 1);
            }
            else if (isspace(input.at(0))) {
                if (input.size() > 1) {
                    found = true;
                }
                if (input.size() == 1) {
                    endingSpace = true;
                }
                input = input.substr(1, input.size() - 1);
            }
        }
        if (endingSpace) {
            break;
        }

        int maxRead = 0;
        Automaton* maxAutomaton = automata.at(1);

        for (Automaton* automaton : automata) {
            int inputRead = automaton->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automaton;
            }
        }

        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        else {
            maxRead = 1;

            if (input[0] == '\'' || input[0] == '#') {
                Token *newToken = new Token(TokenType::UNDEFINED, input.substr(0, input.size()), lineNumber);
                tokens.push_back(newToken);
                maxRead = input.size();

                for (long unsigned int i = 0; i < input.size(); ++i) {
                    if (input[i] == '\n') {
                        lineNumber++;
                    }
                }
            }

            else {
                Token *newToken = new Token(TokenType::UNDEFINED, input.substr(0, maxRead), lineNumber);
                tokens.push_back(newToken);
            }
        }
        input = input.substr(maxRead, input.size() - maxRead);
    }
    tokens.push_back(new Token(TokenType::EOF_TYPE, "", lineNumber));
}

void Lexer::ToString() {
    for (Token* token : tokens)
    {
        cout << token->ToString() << endl;
    }
    cout << "Total Tokens = " << tokens.size();
}
