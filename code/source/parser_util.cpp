#include "parser.h"
#include <iostream>

void errorF(){

}

std::shared_ptr<SyntaxTreeNode> MatchIdentifier( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Identifier){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchInteger( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Integer){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchCloseBracket( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::OpenBracket){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchOpenBracket( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::CloseBracket){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> MatchEnd( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Sharp){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchSemi( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Semi){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchComma( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Comma){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLp( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Lp){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchRp( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Rp){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchFor( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "for"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchContinue( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "continue"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchBreak( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "break"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchIf( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "if"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchWhile( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "while"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchReturn( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "return"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchElse( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "else"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchAnd( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::And){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchOr( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Or){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchPl( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Pl){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchMinus( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Minus){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchMulti( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Multi){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchDivid( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Divid){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchEqual( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Eq){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchNotEqual( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::NtEq){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchGreater( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Gt){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLess( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Ls){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchGreaterEq( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::GtEq){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLessEq( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::LsEq){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchAssign( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Assign){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchInt( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "int"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchFloat( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "float"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchChar( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "char"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> MatchLeftArray( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::LeftArray){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> MatchRightArray( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::RightArray){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        std::cerr << "syntax error in row " << (*it)->row << " column "  << (*it) -> column << std::endl;
    }
    return root;
}