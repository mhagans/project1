#if !defined(P1)
#define _P1_

#include <iostream>
#include "string"
#include "LexicalAnalyzer.hpp"

using namespace std;

string tokenConverter(int t);


int main() {

    cout<<"*********** Lexical Analyzer*************"<<endl;
    int token = SPACE;

    //Read file store each line into array to be read by Analyzer   a3bc+ float 223  int++ vd3 ghg   if else  /****/ g; 12.34


    //Parse each line into tokens
    LexicalAnalyzer LA("int g 4 cd (int u, int v)      {");

    while(token != STOP){
        token = LA.lex();
        LA.linePrint();
        cout << tokenConverter(token) <<":\t" <<LA.lexenum<< endl;
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
        case KEYWORD:
            return "KEYWORD";

        default:
            return "UNKOWN";
    }
    return 0;
}

#endif