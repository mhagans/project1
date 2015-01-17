#include "LexicalAnalyzer.hpp"
#include <string>
#include <stack>


LexicalAnalyzer::LexicalAnalyzer(string in) : input(in), charClass(ERROR), nextChar(' '), lexenum("") {
    Comment = false;
    Start:
    if(xComment.empty()){
        for(int i = 0; i < input.size(); i++){
            if(input[i] == '/' && input[i+1] == '*'){
                xComment.push((char) input[i]);
                input.erase(i, 1);
                input.erase(i, 1);
                i = 0;
            }
        }
        if(!xComment.empty())
            goto Start;

    }else{
        for (int i = 0; i < input.size(); i++) {
            if(input[i] == '*' && input[i+1] == '/'){
                xComment.pop();
                input.erase(i, 1);
                input.erase(i, 1);
                i = 0;
            }
            input.erase(i,1);
        }
    }

    printInput = in;
    if(!xComment.empty()){

    }
    getChar();
}

LexicalAnalyzer::~LexicalAnalyzer() {
}

void LexicalAnalyzer::setNewInput(string in)   {
    input = in;

    Start:
    if(xComment.empty()){
        for(int i = 0; i < input.size(); i++){
            if(input[i] == '/' && input[i+1] == '*'){
                xComment.push((char) input[i]);
                input.erase(i, 1);
                input.erase(i, 1);
                i = 0;
            }
        }
        if(!xComment.empty())
            goto Start;

    }else{
        for (int i = 0; i < input.size(); i++) {
            if(input[i] == '*' && input[i+1] == '/'){
                xComment.pop();
                input.erase(i, 1);
                input.erase(i, 1);
                i = 0;
            }
            input.erase(i,1);
        }
    }
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
    if (nextChar == '(' || nextChar == ')' || nextChar == ',' || nextChar =='{' || nextChar == '}' ||
            nextChar == ';' || nextChar == '[' || nextChar == ']' ||
            nextChar == ':' || nextChar == '+' || nextChar == '-' || nextChar == '*' || nextChar == '/' || nextChar == '=' ||
            nextChar == '<' || nextChar == '>' || nextChar == '!'){
        symbol = true;
    }
    return symbol;
}

void LexicalAnalyzer::getChar(){

    if(input.size() > 0) {
        nextChar = input[0];
        input.erase(0, 1);
        if(isComment)
            goto Inline;
        if(isBlock)
            goto Block;

    } else{
        nextChar = '$';
    }

    charClass = ERROR;
    isComment = false;
    isBlock = false;

    if((nextChar > 64 && nextChar < 91) || (nextChar > 96 && nextChar < 123))
        charClass = LETTER;

    if(nextChar > 47 && nextChar < 58)
        charClass = DIGIT;

    if(nextChar == ' ')
        charClass = SPACE;

    if(nextChar == '$')
        charClass = STOP;

    if(isSymbol()){
        if(nextChar == '/'){
            tempChar = input[0];

            if(nextChar == '/' && tempChar == '/'){
                isComment = true;
                Inline:
                while(input.size() > 0){
                    getChar();
                }
                isComment = false;
                getChar();
            }else{
                if(nextChar == '/' && tempChar == '*'){
                    isBlock = true;
                    getChar();
                    Block:
                        tempChar = input[0];
                    if(nextChar == '*' && tempChar == '*'){
                        getChar();
                    }
                    while(nextChar != '*' && tempChar != '/'){

                        getChar();
                        if(input.size() == 0)
                            goto End;

                    }





                }else{
                    charClass = SYMBOL;
                }

            }
        }else{
            charClass = SYMBOL;
        }
        End:
            ;
    }




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