#include "parser.h"
#include <iostream>

void errorF(){

}

std::shared_ptr<SyntaxTreeNode> MatchIdentifier( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Identifier){
        root->syntaxType = SyntaxUnitType::Identifier;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchOpenBracket( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::OpenBracket){
        root->syntaxType = SyntaxUnitType::;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}
