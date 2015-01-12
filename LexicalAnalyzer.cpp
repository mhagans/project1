#include "LexicalAnalyzer.hpp"
#include <strings.h>



LexicalAnalyzer::LexicalAnalyzer(string in) : input(in), charClass(ERROR), nextChar(' '), lexenum("") {
    printInput = in;
    getChar();
}

LexicalAnalyzer::~LexicalAnalyzer() {
}

void LexicalAnalyzer::setNewInput(string in)   {
    input = in;
    printInput = in;
    getChar();
}

void LexicalAnalyzer::linePrint() {

    cout << "INPUT: "<< printInput << endl;
}

bool LexicalAnalyzer::isKeyword(string in){

    bool keyword = false;
    for (int i = 0; i < 7; i++) {
        if(sKeywords[i].compare(in) == 0){
            keyword = true;
            break;
        }

    }
    return keyword;

}

void LexicalAnalyzer::getChar(){
    if(input.size() > 0) {
        nextChar = input[0];
        input.erase(0, 1);
    } else{
        nextChar = '$';
    }

    charClass = ERROR;

    if((nextChar > 64 && nextChar < 91) || (nextChar > 96 && nextChar < 123))
        charClass = LETTER;

    if(nextChar > 47 && nextChar < 58)
        charClass = DIGIT;

    if(nextChar == ' ')
        charClass = SPACE;

    if(nextChar == '$')
        charClass = STOP;

    if(nextChar == '+')
        charClass = SYMBOL;
}

void LexicalAnalyzer::addChar() {
    lexenum +=nextChar;
}

int LexicalAnalyzer::lex() {
    lexenum = "";

    while (charClass == SPACE) getChar();

    if (charClass == ERROR){
        addChar();
        getChar();
        return ERROR;
    }

    if (charClass == STOP){
        return STOP;
    }

    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            return isKeyword(lexenum) ? KEYWORD : ID;
            break;
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            return INT;
            break;
        case SYMBOL:
            addChar();
            getChar();
            return SYMBOL;
            break;

    }
}