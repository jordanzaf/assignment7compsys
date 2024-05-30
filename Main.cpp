#include <iostream>
#include <list>
#include <vector>

#include "CompilerParser.cpp"
#include "Token.cpp"
#include "ParseTree.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    /* Tokens for:
     *     class MyClass {
     *
     *     }
     */
    list<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "Main"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("keyword", "function"));
    tokens.push_back(new Token("keyword", "void"));
    tokens.push_back(new Token("identifier", "myFunc"));
    tokens.push_back(new Token("symbol", "("));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("keyword", "var"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ";"));
    tokens.push_back(new Token("keyword", "let"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", "="));
    tokens.push_back(new Token("integerConstant", "1"));
    tokens.push_back(new Token("symbol", ";"));
    tokens.push_back(new Token("symbol", "}"));
    tokens.push_back(new Token("symbol", "}"));

    try {
        CompilerParser parser(tokens);
        ParseTree* result = parser.compileProgram();
        if (result != NULL){
            cout << result->tostring() << endl;
        }
    } catch (ParseException e) {
        cout << "Error Parsing!" << endl;
    }
}