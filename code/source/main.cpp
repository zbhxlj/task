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

    Parser parser(test1);
    parser.parse();

    return 0;
}