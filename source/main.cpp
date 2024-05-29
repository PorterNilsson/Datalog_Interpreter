#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

#include <iostream>
#include <fstream>
#include <cctype>

using std::cout;
using std::ifstream;
using std::string;

int main(int argc, char** argv) {

    ifstream in(argv[1]);
    string textFile;

    if (!in.eof()) {
        char current;
        do {
            current = in.get();
            textFile.push_back(current);
        }
        while (in.peek() != EOF);

        if (textFile.size() == 1) {
            textFile = "";
        }
    }

    Lexer lexer;
    lexer.Run(textFile);

//    lexer.ToString();
//
//    cout << endl << endl;

    Parser parser(lexer.GetTokenVector());
    try {
        parser.Parse();
//        cout << parser.ToString();
    }
    catch (const string& s)
    {
        cout << s << endl;
    }

    Interpreter interpreter(parser.GetDatalogProgram());
    interpreter.InterpretSchemes();
    interpreter.InterpretFacts();

    interpreter.OptimizeRules();

    cout << "Rule Evaluation" << endl;

    //cout << "JUMPSTART" << endl;

    for (unsigned int i = 0; i < interpreter.GetSccVector().size(); ++i)
    {
        cout << "SCC: " << interpreter.GetGraphString(i) << endl;

        unsigned int passes = 1;
        while (interpreter.InterpretRules(i))
        {
            ++passes;
        }

        //cout << endl << "Schemes populated after " << passes << " passes through the Rules." << endl << endl;
        cout << passes << " passes: " << interpreter.GetGraphString(i) << endl;
    }


    //interpreter.InterpretRules();
    //cout << interpreter.DatabaseToString();

    cout << endl;
    interpreter.InterpretQueries();

    return 0;
}