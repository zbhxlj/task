#include "parser.h"
struct formatter {
    Parser                                 parser;
    static std::unordered_map<SyntaxUnitType, std::string>     mapFromEnumClassToString; 

    formatter(const Parser& parser): parser(parser) {};   
    void print(int depth, const std::shared_ptr<SyntaxTreeNode>& root);   
};