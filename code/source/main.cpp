#include<string>
#include"../library/lexicalAnalyzer.h"
#include<iostream>
#include"../library/parser.h"
#include"../library/preCompilation.h"
#include"../library/formatter.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]){
    Preprocesser test1(argv[1]);
    tokenParser test2(test1);
    test2.Parse();    
    test2.PrintTokenText();

    Parser parser(test2);
    parser.parse();

    formatter format(parser);
    format.print();

    return 0;
}