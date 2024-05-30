#include "CompilerParser.h"
#include <iostream>


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    for (std::list<Token*>::iterator it = tokens.begin(); it!= tokens.end(); it++){
        this->tokens.push_back(*it);
    }
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    ParseTree* parent = new ParseTree("class", "null");
    addChild(parent);
    mustBe("keyword", "class");
    addChild(parent);
    mustBe("identifier", "Main"); 
    addChild(parent);
    mustBe("symbol", "{");
    try {
        addChild(parent, compileClassVarDec());
    } catch (ParseException()){

    }
    addChild(parent);
    mustBe("symbol", "}");
    return parent;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    ParseTree* parent = new ParseTree("class", "null");
    addChild(parent);
    mustBe("keyword", "class");
    addChild(parent);
    mustBe("identifier", currTokVal());
    addChild(parent);
    mustBe("symbol", "{");
    try {
        addChild(parent, compileClassVarDec());
    } catch (ParseException()){

    }
    addChild(parent);
    mustBe("symbol", "}");
    return parent;
}

ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* parent = new ParseTree("classVarDec", "null");
    if (currTokVal()!="field" && currTokVal()!="static"){
        throw ParseException();
    } 
    addChild(parent);
    mustBe("keyword", tokens[currToken]->getValue());
    addChild(parent);
    if (currTokVal()!="int" && currTokVal()!="boolean" && currTokVal()!="char"){
        throw ParseException();
    } 
    mustBe("keyword", currTokVal());
    addChild(parent);
    mustBe("identifier", tokens[currToken]->getValue());
    addChild(parent);
    //do this later
    while (currTokVal() != ";"){
        mustBe(tokens[currToken]->getType(), currTokVal());
        addChild(parent);
    }
    mustBe("symbol", ";");
    return parent;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    int parent = currToken;
    if (currTokVal()!="constructor" && currTokVal()!="function" ){

    }

    return tokens[parent];
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    return NULL;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    if (currToken >= tokens.size()){
        throw ParseException();
    }
    currToken++;
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    return tokens[currToken];
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    if (expectedType == tokens[currToken]->getType() && expectedValue == tokens[currToken]->getValue()){
        return true;
    }
    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if (expectedType == tokens[currToken]->getType() && expectedValue == tokens[currToken]->getValue()){
        next();
        return current();
    }
    throw ParseException();
    return NULL;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}

void CompilerParser::addChild(ParseTree* a){
    a->addChild(tokens[currToken]);
}

void CompilerParser::addChild(ParseTree* a, ParseTree* b){
    a->addChild(b);
}

std::string CompilerParser::currTokVal(){
    return (tokens[currToken]->getValue());
}