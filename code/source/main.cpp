#include<string>
#include "../library/lex.h"
#include<iostream>
#include"../library/parser.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]){
    tokenParser test1(argv[1]);
    test1.Parse();    
    test1.PrintTokenText();

    parse(test1);

    return 0;
}