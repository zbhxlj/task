#include<string>
#include "lex.h"
#include<iostream>

using std::cout;
using std::endl;

int main(int argc, char* argv[]){
    tokenParser test1(argv[1]);
    test1.Parse();    
    test1.PrintTokenText();


    return 0;
}