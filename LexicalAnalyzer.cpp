#include "LexicalAnalyzer.hpp"
#include <string>
#include <stack>


LexicalAnalyzer::LexicalAnalyzer(string in) : input(in), charClass(ERROR), currentChar(' '), lexenum("") {

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

bool LexicalAnalyzer::isSymbol() {
    bool symbol = false;
    if (currentChar == '(' || currentChar == ')' || currentChar == ',' || currentChar =='{' || currentChar == '}' ||
            currentChar == ';' || currentChar == '[' || currentChar == ']' ||
            currentChar == ':' || currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '=' ||
            currentChar == '<' || currentChar == '>' || currentChar == '!'){
        symbol = true;
    }
    return symbol;
}

void LexicalAnalyzer::getChar(){

    Start:
    if(input.size() > 0) {
        currentChar = input[0];
        input.erase(0, 1);
    } else{
        currentChar = '$';
    }
    if(currentChar == '/' && input[0] == '*'){
        xComment.push(1);
        currentChar == input[0];
        input.erase(0, 1);
        getChar();

    }

    if(xComment.empty() == false && currentChar != '$'){

        if(currentChar == '*' && input[0] == '/'){
            xComment.pop();
            currentChar = input[0];
            input.erase(0, 1);

        }else{
            if(currentChar == '/' && input[0] == '*'){
                xComment.push(1);
                currentChar == input[0];
                input.erase(0, 1);
            }
        }
        getChar();

    }

    charClass = ERROR;


    if((currentChar > 64 && currentChar < 91) || (currentChar > 96 && currentChar < 123))
        charClass = LETTER;

    if(currentChar > 47 && currentChar < 58)
        charClass = DIGIT;

    if(currentChar == ' ')
        charClass = SPACE;

    if(currentChar == '$')
        charClass = STOP;

    if(isSymbol()){

        if(currentChar == '/'){


            if(currentChar == '/' && input[0] == '/'){
                Inline:
                while(input.size() > 0){
                    getChar();
                }
                getChar();
            }else{

                charClass = SYMBOL;

            }


        }else{

            charClass = SYMBOL;
        }

    }

}

void LexicalAnalyzer::addChar() {
    lexenum += currentChar;
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
                if(input[0] == '.'){
                    addChar();
                    getChar();
                }else{
                    getChar();
                }

                // This will be to check for a float
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