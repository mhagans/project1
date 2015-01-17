#if !defined(P1)
#define _P1_

#include <iostream>
#include <fstream>
#include <conio.h>
#include <ctype.h>
#include <regex>
#include "string"
#include "LexicalAnalyzer.hpp"

using namespace std;

string tokenConverter(int t);


int main(int argc, char **argv) {
    string filename;
    string fileLine;


    if(argc < 2){
        cout << "Invalid number of arugments entered"<<endl;
        return 0;
    }else{
        filename = argv[1];
    }


    cout<<"*********** Lexical Analyzer*************"<<endl;

    int token = SPACE;

    //Read file store each line into array to be read by Analyzer   a3bc+ float 223  int++ vd3 ghg   if else  /****/ g; 12.34
   ifstream FILE(filename);
    getline(FILE, fileLine);



    LexicalAnalyzer LA(fileLine);
    if(FILE.is_open()){
        do{

                LA.linePrint();
                while(token != STOP){
                    token = LA.lex();
                    if(token == STOP){
                    }else{
                        cout << tokenConverter(token) <<":\t" <<LA.lexenum<< endl;
                    }

                }
            getline(FILE, fileLine);

            LA.setNewInput(fileLine);
            token = SPACE;

        }while(!FILE.eof());


    }else{
        cout << "Unable to open " << filename <<endl;
    }

    //Stop program at end of file


    //Parse each line into tokens

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