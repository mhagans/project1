#include "LexicalAnalyzer.hpp"

LexicalAnalyzer::LexicalAnalyzer(string in) : input(in), charClass(ERROR), nextChar(' '), lexenum("") {
    getChar();
}

LexicalAnalyzer::~LexicalAnalyzer() {
}

void LexicalAnalyzer::setNewInput(string in) {
    input = in;
    getChar();
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
        charClass = PLUS_CODE;
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
            return ID;
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
        case PLUS_CODE:
            addChar();
            getChar();
            return PLUS_CODE;
            break;

    }
}