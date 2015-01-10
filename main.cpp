#if !defined(P1)
#define _P1_

#include <iostream>
#include "string"
#include "LexicalAnalyzer.hpp"

using namespace std;

string tokenConverter(int t);

int main() {

    cout<<"*********** Lexical Analyzer"<<endl;
    int token = SPACE;

    //Read file store each line into array to be read by Analyzer

    //Parse each line into tokens
    LexicalAnalyzer LA("a3bc+ 223 ++ vd3 ghg  /****/ g; 12.34");

    while(token != STOP){
        token = LA.lex();
        LA.linePrint();
        cout << tokenConverter(token) <<"\t" <<LA.lexenum<< endl;
    }


}

string tokenConverter(int t){
    switch (t){
        case SPACE:
            return "SPACE";
        case LETTER:
            return "LETTER";
        case DIGIT:
            return "DIGIT";
        case ID:
            return "ID";
        case INT:
            return "INT";
        case ERROR:
            return "ERROR";
        case STOP:
            return "STOP";
        case FLOAT:
            return "FLOAT";
        case SYMBOL:
            return "SYMBOL";

        default:
            return "UNKOWN";
    }
    return 0;
}

#endif