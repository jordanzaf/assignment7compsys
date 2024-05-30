#ifndef COMPILERPARSER_H
#define COMPILERPARSER_H

#include <vector>
#include <list>
#include <exception>

#include "ParseTree.h"
#include "Token.h"

class CompilerParser {
    private:
        std::vector<Token*> tokens;
        int currToken=0;
    public:
        CompilerParser(std::list<Token*> tokens);

        ParseTree* compileProgram();
        ParseTree* compileClass();
        ParseTree* compileClassVarDec();
        ParseTree* compileSubroutine();
        ParseTree* compileParameterList();
        ParseTree* compileSubroutineBody();
        ParseTree* compileVarDec();

        ParseTree* compileStatements();
        ParseTree* compileLet();
        ParseTree* compileIf();
        ParseTree* compileWhile();
        ParseTree* compileDo();
        ParseTree* compileReturn();

        ParseTree* compileExpression();
        ParseTree* compileTerm();
        ParseTree* compileExpressionList();

        void addChild(ParseTree* a);
        void addChild(ParseTree* a, ParseTree* b);
        std::string currTokVal();
        
        void next();
        Token* current();
        bool have(std::string expectedType, std::string expectedValue);
        Token* mustBe(std::string expectedType, std::string expectedValue);
};

class ParseException : public std::exception {
    public:
        const char* what();
};

#endif /*COMPILERPARSER_H*/