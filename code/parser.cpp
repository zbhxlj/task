#include"parser.h"
#include<memory>
#include<vector>

std::shared_ptr<SyntaxTreeNode> parse(const tokenParser& environment){
    auto it = environment.tokenText.begin();
    return parseS(it);
}

std::shared_ptr<SyntaxTreeNode> parseS(std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    switch ((*it)->type)
    {
    case tokenType::Integer:
    case tokenType::Float:
    // case tokenType::Char:
    case 
        break;
    
    default:
        break;
    }
}