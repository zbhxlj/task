#ifndef FORMAT_AND_PRINT_H
#define FORMAT_AND_PRINT_H

#include "syntax_analysis.h"
#include<sstream>
class Formatter {
private:
    SyntaxAnalyzer                                           syntax_analyzer;

    void PrintNode(int& number_of_tab, const std::shared_ptr<SyntaxTreeNode>& root, std::stringstream& output, int& i);
    void printAST(int depth, const std::shared_ptr<SyntaxTreeNode>& root);   
public:    
    Formatter(const SyntaxAnalyzer& syntax_analyzer): syntax_analyzer(syntax_analyzer) {};   
    void PrintAST();
    void PrintFormattedText();
};

#endif