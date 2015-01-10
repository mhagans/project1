#if !defined(_LA_)
#define _LA_

#include <iostream>
#include <string>

using namespace std;

enum {DIGIT, LETTER, ID, INT, FLOAT, ERROR, SPACE, STOP, SYMBOL};

class LexicalAnalyzer{

public:
    char nextChar;
    int charClass;
    string lexenum;
    string printInput;

private:
    string input;

public:
    int lex();
    void setNewInput(string in);
    LexicalAnalyzer(string in="");
    void linePrint();
    virtual ~LexicalAnalyzer();

private:
    void addChar();
    void getChar();
};


#endif