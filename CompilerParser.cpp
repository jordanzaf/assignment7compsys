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
    std::cout << "1" << std::endl;
    if (currTokVal() == "field" || currTokVal() == "static"){
        addChild(parent, compileClassVarDec());
    }
    if (currTokVal() == "constructor" || currTokVal() == "function" || currTokVal() == "method"){
        std::cout << "2" << std::endl;
        addChild(parent, compileSubroutine());
    }
    std::cout << "2.3" << std::endl;
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
    if (currTokVal() == "field" || currTokVal() == "static"){
        addChild(parent, compileClassVarDec());
    }
    if (currTokVal() == "constructor" || currTokVal() == "function" || currTokVal() == "method"){
        addChild(parent, compileSubroutine());
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
    std::cout << "3" << std::endl;
    if (currTokVal() != "constructor" && currTokVal() != "function" && currTokVal() != "method"){
        throw ParseException();
    }
    ParseTree* parent = new ParseTree("subroutine", "null");
    mustBe("keyword", currTokVal());
    addChild(parent);
    if (currTokVal() != "void" && currTokVal() != "int" && currTokVal() != "char" && currTokVal() != "boolean" ){
        throw ParseException();
    }
    mustBe("keyword", currTokVal());
    addChild(parent);
    mustBe("identifier", currTokVal());
    addChild(parent);
    mustBe("symbol", "(");
    if (currTokVal() != ")"){
        std::cout << "4" << std::endl;
           addChild(parent, compileParameterList());
    }
    addChild(parent);
    mustBe("symbol", ")");
    std::cout << "10" << std::endl;
    addChild(parent, compileSubroutineBody());
    std::cout << "2.2" << std::endl;
    return parent;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    std::cout << "5" << std::endl;
    ParseTree* parent = new ParseTree("parameterList", "null");
    std::cout << "6" << std::endl;
    addChild(parent);
    while (currTokVal() != ")"){
        if (currTokVal()!="int" && currTokVal()!="boolean" && currTokVal()!="char"){
            throw ParseException();
        }
        addChild(parent);
        mustBe("keyword", currTokVal());
        addChild(parent);
        mustBe("identifier", currTokVal());
        std::cout << "x" << std::endl;
        if (currTokVal()!=")" ){
            addChild(parent);
            std::cout << "7" << std::endl;
            mustBe("symbol", ",");
        }
    }
    std::cout << "9" << std::endl;
    return parent;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* parent = new ParseTree("subroutineBody", "null");
    addChild(parent);
    mustBe("symbol", "{");
    std::cout << "11" << std::endl;
    if (currTokVal() == "var"){ 
        std::cout << "12" << std::endl;
        addChild(parent, compileVarDec());
        //addChild(parent, compileStatements());
    } 
    std::cout << "2.1" << std::endl;
    addChild(parent);
    std::cout << currTokTyp() + " " + currTokVal() << std::endl;
    //mustBe("symbol", ";");
    //addChild(parent);
    std::cout << currTokTyp() + " " + currTokVal() << std::endl;
    mustBe("symbol", "}");
    std::cout << "2.11" << std::endl;
    return parent;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    std::cout << "13" << std::endl;
    ParseTree* parent = new ParseTree("varDec", "null");
    addChild(parent);
    while (currTokVal() != ";"){
        std::cout << "x" << std::endl;
        addChild(parent);
        std::cout << currTokVal() << std::endl;
        mustBe("keyword", "var");
        std::cout << "16" << std::endl;
        if (currTokVal() != "char" && currTokVal() != "int" && currTokVal() != "boolean"){
            std::cout << "17" << std::endl;
            throw ParseException();
        }
        std::cout << "14" << std::endl;
        addChild(parent);
        mustBe("keyword", currTokVal());
        addChild(parent);
        mustBe("identifier", currTokVal());
        std::cout << "15" << std::endl;
        if (currTokVal()!=";" ){
            addChild(parent);
            mustBe("symbol", ",");
        }
    }
    std::cout << "y" << std::endl;
    return parent;
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
    if (currToken >= tokens.size()){
        throw ParseException();
    }
    a->addChild(tokens[currToken]);
}

void CompilerParser::addChild(ParseTree* a, ParseTree* b){
    a->addChild(b);
}

std::string CompilerParser::currTokVal(){
    if (currToken >= tokens.size()){
        throw ParseException();
    }
    return (tokens[currToken]->getValue());
}

std::string CompilerParser::currTokTyp(){
    if (currToken >= tokens.size()){
        throw ParseException();
    }
    return (tokens[currToken]->getType());
}