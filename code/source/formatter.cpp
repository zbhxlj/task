#include "../library/formatter.h"
#include<iostream>


void formatter::print(int depth, const std::shared_ptr<SyntaxTreeNode>& root){
    for(int i = 0; i < depth; i++) std::cout << " ";
    std::cout << "SyntaxUnitType : " << parser.mapFromEnumClassToString[root->syntaxType] << std::endl;
    if(root -> curToken.get() != nullptr){
        for(int i = 0; i < depth; i++) std::cout << " ";
        std::cout << "tokenType : " 
        << parser.tokenparser.mapFromEnumClassToString[root->curToken->type]
        << std::endl;

        for(int i = 0; i < depth; i++) std::cout << " ";
        std::cout << "value : " << root->curToken->value << std::endl; 
    }
    std::cout << std::endl;

    for(const auto& son : root -> childs){
        print(depth + 1, son);
    }
    return;
}