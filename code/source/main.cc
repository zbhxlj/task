#include<string>
#include"../library/lexical_analysis.h"
#include<iostream>
#include"../library/syntax_analysis.h"
#include"../library/preprocess.h"
#include"../library/format_and_print.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]){
    Preprocesser test1(argv[1]);
    test1.Preprocess();
    LexicalAnalyzer test2(test1);
    test2.LexicalAnalyze();    
    test2.PrintTokenText();

    SyntaxAnalyzer syntax_analyzer(test2);
    syntax_analyzer.Parse();

    Formatter format(syntax_analyzer);
    format.PrintFormattedText();

    return 0;
}