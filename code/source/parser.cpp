#include"parser.h"
#include<memory>
#include<vector>
#include "parser_util.cpp"

std::shared_ptr<SyntaxTreeNode> parse(const tokenParser& environment){
    auto it = environment.tokenText.begin();
    return parseS(it);
}

std::shared_ptr<SyntaxTreeNode> parseS(std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::Program;
    switch ((*it)->type)
    {
    case tokenType::Integer:
    case tokenType::Float:
    case tokenType::Char:
        root->childs.push_back( parseA(it) );
        break;
    
    default:
        break;
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> parseA(std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ExternalDefinitionSequence;
    switch ((*it)->type)
    {
    case tokenType::Integer :
    case tokenType::Float :
    case tokenType::Char :
        root->childs.push_back(parseB(it));
        root->childs.push_back(parseA__SingleQuota(++it));
        break;
    
    default:
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> parseA__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ExternalDefinition__SingleQuota;
    switch ((*it)->type)
    {
    case tokenType::Integer :
    case tokenType::Float :
    case tokenType::Char :
        root->childs.push_back( parseA(it) );
        break;
    case tokenType::End :
        break;
    default:
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> parseB(std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ExternalDefinition;
    switch ((*it) -> type)
    {
    case tokenType::Integer :
    case tokenType::Float :
    case tokenType::Char :
        root->childs.push_back( parseR(it) );
        root->childs.push_back( MatchIdentifier(++it) );
        root->childs.push_back( parseB_SingleQuota(++it) );
        break;
    
    default:
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> parseB_SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ExternalDefinition__SingleQuota;
    switch ((*it) -> type)
    {
    case tokenType::OpenBracket:
        root->childs.push_back( MatchOpenBracket(it) );
        root->childs.push_back( parseI(++it) );
        root->childs.push_back( MatchCloseBracket(++it) );
        root->childs.push_back( parseJ(++it) );
        break;

    case tokenType::Comma :
    case tokenType::Semi :
        root->childs.push_back( parseE__SingleQuota(it) );
        break;
        
    default:
        break;
    }
}

std::shared_ptr<SyntaxTreeNode> parseC(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseE(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseE__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseG(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseI(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseK(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseJ(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseL(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseN(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseM(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseO(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseO__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseP(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseP__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseP__DoubleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseP__TripleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseQ(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseR(std::vector<std::shared_ptr<token>>::const_iterator& it){

}

std::shared_ptr<SyntaxTreeNode> parseR_SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){

}