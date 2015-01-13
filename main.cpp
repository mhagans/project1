#if !defined(P1)
#define _P1_

#include <iostream>
#include <fstream>
#include <conio.h>
#include "string"
#include "LexicalAnalyzer.hpp"

using namespace std;

string tokenConverter(int t);


int main(int argc, char **argv) {
    string filename;

    if(argc < 2){
        cout << "Invalid number of arugments entered"<<endl;
        return 0;
    }else{
        filename = argv[1];
    }

    cout<<"*********** Lexical Analyzer*************"<<endl;

    int token = SPACE;

    //Read file store each line into array to be read by Analyzer   a3bc+ float 223  int++ vd3 ghg   if else  /****/ g; 12.34
   // fstream File()
    //Stop program at end of file


    //Parse each line into tokens
    LexicalAnalyzer LA("a3bc+ float 223  3@22 int ++ vd3 ghg   if else  /****/ g; 12.34");
    LA.linePrint();
    while(token != STOP){
        token = LA.lex();
        cout << tokenConverter(token) <<":\t" <<LA.lexenum<< endl;
    }
    End:
    return 0;


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