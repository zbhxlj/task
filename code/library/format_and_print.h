#ifndef FORMAT_AND_PRINT_H
#define FORMAT_AND_PRINT_H

#include "syntax_analysis.h"
#include<sstream>

// Formatter prints abstract syntax tree and shows formatted text;
//
// Example: 
//  Formatter formatter(syntax_analyzer);
//  formatter.PrintAST();
//  formatter.PrintFormattedText(); 
class Formatter {
private:
    SyntaxAnalyzer                                           syntax_analyzer;

    void PrintNode(int& number_of_tab, const std::shared_ptr<SyntaxTreeNode>& root, std::stringstream& output, int& i, bool& in_for_range);
    void printAST(int depth, const std::shared_ptr<SyntaxTreeNode>& root);   
public:    
    Formatter(const SyntaxAnalyzer& syntax_analyzer): syntax_analyzer(syntax_analyzer) {};   
    void PrintAST();
    void PrintFormattedText();
};

#endif