#include "parser.h"
#include<sstream>
struct formatter {
    Parser                                 parser;
    static std::unordered_map<SyntaxUnitType, std::string>     mapFromEnumClassToString; 

    formatter(const Parser& parser): parser(parser) {};   
    void printAST(int depth, const std::shared_ptr<SyntaxTreeNode>& root);   
    void printNode(int& tabNum, const std::shared_ptr<SyntaxTreeNode>& root, std::stringstream& output, int& i);
    void print();
};