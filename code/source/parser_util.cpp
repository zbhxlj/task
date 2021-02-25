#include "../library/parser.h"
#include <iostream>

void unexpectedTokenTypeErrorF(const std::shared_ptr<token>& tokenPtr, 
            std::string syntaxUnitType,
            std::string tokentype){
    std::cerr << "Syntax error in row " << tokenPtr->row 
              << " column " <<tokenPtr->column << std::endl;
    std::cerr << "When parsing " << syntaxUnitType << std::endl
              << "Unexpected tokenType : " << tokentype << std::endl;
    std::cerr << "Parsing terminated " << std::endl;
    exit(-1);
}   

void matchTerminatorErrorF(const std::shared_ptr<token>& tokenPtr,
                           std::string tokentype,
                           std::string terminator){
    std::cerr << "Syntax error in row " << tokenPtr->row 
              << " column " <<tokenPtr->column << std::endl;
    std::cerr << "When matching " << tokentype << std::endl
              << "Unexpected terminator : " << terminator << std::endl;
    std::cerr << "Parsing terminated " << std::endl;
    exit(-1);
}   

std::shared_ptr<SyntaxTreeNode> MatchIdentifier( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Identifier){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "Identifier", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchInt_C( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Int_C){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "Int_C", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLong_C( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Long_C){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "Long_C", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchFloat_C( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Int_C){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "Float_C", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchChar_C( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Char_C){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "Char_C", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchCloseBracket( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::OpenBracket){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "(", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchOpenBracket( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::CloseBracket){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), ")", (*it)->value);
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> MatchEnd( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Sharp){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "#", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchSemi( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Semi){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), ";", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchComma( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Comma){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), ",", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLp( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Lp){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "{", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchRp( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Rp){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "}", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchFor( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "for"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "for", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchContinue( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "continue"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "continue", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchBreak( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "break"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "break", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchIf( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "if"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "if", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchWhile( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "while"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "while", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchReturn( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "return"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "return", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchElse( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "else"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "else", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchAnd( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::And){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "&&", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchOr( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Or){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "||", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchPl( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Pl){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "+", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchMinus( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Minus){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "-", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchMulti( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Multi){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "*", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchDivid( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Divid){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "/", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchEqual( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Eq){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "==", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchNotEqual( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::NtEq){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "!=", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchGreater( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Gt){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), ">", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLess( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Ls){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "<", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchGreaterEq( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::GtEq){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), ">=", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchLessEq( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::LsEq){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "<=", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchAssign( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::Assign){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "=", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchInt( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "int"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "int", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchFloat( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "float"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "float", (*it)->value);
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> MatchChar( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->value == "char"){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "char", (*it)->value);
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> MatchLeftArray( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::LeftArray){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "[", (*it)->value);
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> MatchRightArray( std::vector<std::shared_ptr<token>>::const_iterator& it){
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    if((*it)->type == tokenType::RightArray){
        root->syntaxType = SyntaxUnitType::Terminator;
        root -> curTerminator = (*it) -> value;
    }else {
        matchTerminatorErrorF((*it), "]", (*it)->value);
    }
    return root;
}