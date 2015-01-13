#if !defined(_LA_)
#define _LA_

#include <iostream>
#include <string>
#include <ctype.h>


using namespace std;

enum {DIGIT, LETTER, KEYWORD, ID, INT, FLOAT, ERROR, SPACE, STOP, SYMBOL};




class LexicalAnalyzer{

public:
    char nextChar;
    int charClass;
    string lexenum;
    string printInput;
    string sKeywords [7] = {"if", "else", "int", "float", "return", "void", "while"};
    //char sSymbols [21] = {'+', '-', '*', '/', '<', '<=', '>', '>=', '==', '!=', '=', ';', ',', '(', ')', '[', ']', '{', '}', '/*', '*/'};


private:
    string input;

public:
    int lex();
    bool isKeyword(string in);
   // bool isSymbol();
    void setNewInput(string in);
    LexicalAnalyzer(string in="");
    void linePrint();
    virtual ~LexicalAnalyzer();

private:
    void addChar();
    void getChar();
};


#endif