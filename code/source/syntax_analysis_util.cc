#include "../library/syntax_analysis.h"
#include <iostream>
#include<iomanip>
// This file contains some useful helper functions when in syntax analysis.
// Including user_friendly error_handle functions and MatchTerminator functions. 

void UnexpectedTokenTypeErrorF(const std::shared_ptr<Token>& token_ptr, 
            std::string syntax_unit_type,
            std::string token_type,
            std::string function_name){
    std::cerr << "Syntax error in number_of_row " << std::setw(7) << token_ptr->number_of_row 
              << " number_of_column " << std::setw(7) << token_ptr->number_of_column << std::endl;
    std::cerr << "When parsing " << std::setw(7) << syntax_unit_type << std::endl
              << "Unexpected TokenType : " << token_type << std::endl
              << "In function Parse" << function_name << std::endl;
    std::cerr << "----------------------------------------------" << std::endl;
    std::cerr << "Parsing terminated " << std::endl;
    exit(-1);
}   

void matchTerminatorErrorF(const std::shared_ptr<Token>& token_ptr,
                           std::string token_type,
                           std::string terminator){
    std::cerr << "Syntax error in number_of_row "<< std::setw(7)  << token_ptr->number_of_row 
              << " number_of_column " << std::setw(7)  << token_ptr->number_of_column << std::endl;
    std::cerr << "When matching " << std::setw(7) << token_type << std::endl
              << "Unexpected terminator : " << terminator << std::endl;
    std::cerr << "----------------------------------------------" << std::endl;
    std::cerr << "Parsing terminated " << std::endl;
    exit(-1);
}   

void printFuncPath(const std::string& function_name, std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::cerr << std::setiosflags(std::ios::left)
    << "Calling Parse " << std::setw(20) << function_name  << " Token:  " << (*it)->token_value << std::endl;
}

std::shared_ptr<SyntaxTreeNode> MatchIdentifier( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Identifier){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "Identifier", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchInt_C( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Int_C){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "Int_C", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLong_C( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Long_C){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "Long_C", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchFloat_C( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Float_C){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "Float_C", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchChar_C( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Char_C){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "Char_C", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchCloseBracket( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::CloseBracket){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), ")", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchOpenBracket( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::OpenBracket){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "(", (*it)->token_value);
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> MatchEnd( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::End){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "$", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchSemi( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Semi){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), ";", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchComma( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Comma){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), ",", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLp( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Lp){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "{", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchRp( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Rp){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "}", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchFor( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_value == "for"){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "for", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchContinue( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_value == "continue"){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "continue", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchBreak( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_value == "break"){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "break", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchIf( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_value == "if"){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "if", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchWhile( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_value == "while"){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "while", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchReturn( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_value == "return"){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "return", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchElse( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_value == "else"){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "else", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchAnd( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::And){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "&&", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchOr( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Or){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "||", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchPl( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Pl){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "+", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchMinus( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Minus){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "-", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchMulti( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Multi){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "*", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchDivid( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Divid){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "/", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchEqual( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Eq){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "==", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchNotEqual( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::NtEq){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "!=", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchGreater( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Gt){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), ">", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLess( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Ls){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "<", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchGreaterEq( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::GtEq){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), ">=", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLessEq( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::LsEq){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "<=", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchAssign( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Assign){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "=", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchInt( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Int){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "int", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchFloat( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Float){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "float", (*it)->token_value);
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> MatchChar( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Char){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "char", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLong( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::Long){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "long", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLeftArray( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::LeftArray){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "[", (*it)->token_value);
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> MatchRightArray( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::RightArray){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "]", (*it)->token_value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchString( std::vector<std::shared_ptr<Token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->token_type == TokenType::String){
        root->syntax_type = SyntaxUnitType::Terminator;
        root -> token = (*it);
    }else {
        matchTerminatorErrorF((*it), "String", (*it)->token_value);
    }
    return root;
}