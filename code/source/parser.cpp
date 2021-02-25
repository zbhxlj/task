#include"../library/parser.h"
#include<memory>
#include<vector>
#include "parser_util.cpp"

Parser::Parser(const tokenParser& tP) : tokenparser(tP) {
    mapFromEnumClassToString = {
        {SyntaxUnitType::Program, "Program"},
        {SyntaxUnitType::ExternalDefinitionSequence, "ExternalDefinitionSequence"},
        {SyntaxUnitType::ExternalDefinitionSequence___SingleQuota, "ExternalDefinitionSequence_SingleQuota"},
        {SyntaxUnitType::ExternalDefinition, "ExternalDefinition"},
        {SyntaxUnitType::ExternalDefinition__SingleQuota, "ExternalDefinition_SingleQuota"},
        {SyntaxUnitType::ExternalVariableDefinition, "ExternalVarialbleDefinition"},
        {SyntaxUnitType::VariableSequence, "VariableSequence"},
        {SyntaxUnitType::VariableSequence__SingleQuota, "VariableSequence_SingleQuota"},
        {SyntaxUnitType::FunctionDefinition, "FunctionDefinition"},
        {SyntaxUnitType::ParameterSequence, "ParameterSequence"},
        {SyntaxUnitType::ComplexSentence, "ComplexSentence"},
        {SyntaxUnitType::Parameter, "Parameter"},
        {SyntaxUnitType::LocalVariableDefinitionSequence, "LocalVariableDefinitionSequence"},
        {SyntaxUnitType::SentenceSequence, "SentenceSequence"},
        {SyntaxUnitType::LocalVarialbleDefinition, "LocalVariableDefinition"},
        {SyntaxUnitType::Sentence, "Sentence"},
        {SyntaxUnitType::Sentence__SingleQuota, "Sentence_SingleQuota"},
        {SyntaxUnitType::Expression, "Expression"},
        {SyntaxUnitType::Expression__SingleQuota, "Expression_SingleQuota"},
        {SyntaxUnitType::Expression__DoubleQuota, "Expression_DoubleQuota"},
        {SyntaxUnitType::Expression__TripleQuota, "Expression_TripleQuota"},
        {SyntaxUnitType::ArgumentSequence, "ArgumentSequence"},
        {SyntaxUnitType::TypeName, "TypeName"},
        {SyntaxUnitType::Array, "Array"},
        {SyntaxUnitType::Terminator, "Terminator"},
        {SyntaxUnitType::Nul, "Nul"}
    };
}

std::shared_ptr<SyntaxTreeNode> Parser::parse(){
    auto it = tokenparser.tokenText.cbegin();
    printFuncPath("", it);
    return parseS(it);
}

std::shared_ptr<SyntaxTreeNode> Parser::parseS(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("S", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::Program;
    switch ((*it)->type)
    {
    case tokenType::Int:
    case tokenType::Float:
    case tokenType::Char:
        root->childs.push_back( parseA(it) );
        break;
    
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "S");
        break;
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> Parser::parseA(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("A", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ExternalDefinitionSequence;
    switch ((*it)->type)
    {
    case tokenType::Int :
    case tokenType::Float :
    case tokenType::Char :
        root->childs.push_back(parseB(it));
        root->childs.push_back(parseA__SingleQuota(++it));
        break;
    
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "A");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseA__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("A_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ExternalDefinition__SingleQuota;
    switch ((*it)->type)
    {
    case tokenType::Int :
    case tokenType::Float :
    case tokenType::Char :
        root->childs.push_back( parseA(it) );
        break;
    case tokenType::End :
        root ->childs.push_back( MatchEnd(it) );
        it++;
        break;
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "A_SingleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseB(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("B", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ExternalDefinition;
    switch ((*it) -> type)
    {
    case tokenType::Int :
    case tokenType::Float :
    case tokenType::Char :
        root->childs.push_back( parseR(it) );
        root->childs.push_back( MatchIdentifier(++it) );
        root->childs.push_back( parseB_SingleQuota(++it) );
        break;
    
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "B");    
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseB_SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("B_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ExternalDefinition__SingleQuota;
    switch ((*it) -> type)
    {
    case tokenType::OpenBracket:
        std::cerr << "It should be here" << std::endl;
        root->childs.push_back( parseG(it) );
        break;

    case tokenType::Comma :
    case tokenType::Semi :
        root->childs.push_back( parseE__SingleQuota(it) );
        it++;
        break;
        
    default:
    std::cerr << "ridiculous" << std::endl;
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "B_SingleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseC(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("C", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ExternalVariableDefinition;
    switch ((*it) -> type)
    {
    case tokenType::Int :
    case tokenType::Float :
    case tokenType::Char :
        root->childs.push_back( parseR(it) );
        root->childs.push_back( parseE(++it));
        it++;
        break;
    
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "C");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseE(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("E", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::VariableSequence;
    switch ((*it) -> type)
    {
    case tokenType::Identifier:
        root->childs.push_back( MatchIdentifier(it) );
        root->childs.push_back( parseE__SingleQuota(++it));
        it++;
        break;
    
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "E");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseE__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("E_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::VariableSequence__SingleQuota;
    switch ((*it) -> type)
    {
    case tokenType::Comma :
        root->childs.push_back( MatchComma(it) );
        root->childs.push_back( parseE(++it) );
        it++;
        break;
    
    case tokenType::Semi :
        break;

    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "E_SingleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseG(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("G", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::FunctionDefinition;
    switch ((*it)->type)
    {
    case tokenType::OpenBracket :
        root->childs.push_back( MatchOpenBracket(it) );
        root->childs.push_back( parseI(++it) );
        root->childs.push_back( MatchCloseBracket(++it) );
        root->childs.push_back( parseJ(++it) );
        it++;
        break;
    
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "G");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseI(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("I", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ParameterSequence;
    switch ((*it)->type)
    {
    case tokenType::CloseBracket :
        root->childs.push_back( MatchCloseBracket(it) );
        it++;
        break;
    
    case tokenType::Int :
    case tokenType::Float :
    case tokenType::Char :
        root->childs.push_back( parseK(it) );
        root->childs.push_back( MatchComma(++it) );
        root->childs.push_back( parseI(++it) );
        it++;
        break;

    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "I");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseK(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("K", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::Parameter;
    switch ((*it)->type)
    {
    case tokenType::Int :
    case tokenType::Float :
    case tokenType::Char :
        root->childs.push_back( parseR(it) );
        root->childs.push_back( MatchIdentifier(++it) );
        it++;
        break;
    
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "K");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseJ(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("J", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ComplexSentence;
    switch ((*it) -> type)
    {
    case tokenType::Lp :
        root->childs.push_back( MatchLp(it) );
        root->childs.push_back( parseL(++it) );
        root->childs.push_back( parseM(++it) );
        root->childs.push_back( MatchRp(++it) );
        it++;
        break;
    
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "J");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseL(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("L", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::LocalVariableDefinitionSequence;
    switch ((*it) -> type)
    {
    case tokenType::Int :
    case tokenType::Float :
    case tokenType::Char :
        root->childs.push_back( parseN(it) );
        root->childs.push_back( parseL(++it) );
        it++;
        break;
    case tokenType::End :
        root->childs.push_back( MatchEnd(it) );
        it++;
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "L");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseN(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("N", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::LocalVarialbleDefinition;
    switch ((*it) -> type)
    {
    case tokenType::Int :
    case tokenType::Float :
    case tokenType::Char :
        root->childs.push_back( parseR(it) );
        root->childs.push_back( parseE(++it) );
        it++;
        break;
    
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "N");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseM(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("M", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::SentenceSequence;
    switch ((*it) -> type)
    {
    case tokenType::Rp :
        break;
    
    case tokenType::Int_C:
    case tokenType::Char_C:
    case tokenType::Float_C:
    case tokenType::Long_C:
    case tokenType::Identifier:
        root->childs.push_back( parseO(it));
        root->childs.push_back( parseM(++it) );
        it++;
        break;

    case tokenType::Return:
    case tokenType::If :
    case tokenType::While:
    case tokenType::Break:
    case tokenType::Continue:
    case tokenType::For:
        root->childs.push_back( parseO(it));
        root->childs.push_back( parseM(++it) );
        it++;
        break;
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "M");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseO(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("O", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::Sentence;
    switch ((*it) -> type)
    {
    case tokenType::For:
        root->childs.push_back( MatchFor(it) );
        root->childs.push_back( MatchOpenBracket(++it) );
        root->childs.push_back( parseP(++it) );
        root->childs.push_back( MatchSemi(++it) );
        root->childs.push_back( parseP(++it) );
        root->childs.push_back( MatchSemi(++it) );
        root->childs.push_back( parseP(++it) );
        root->childs.push_back( MatchCloseBracket(++it) );
        root->childs.push_back( parseO(++it) );
        it++;
        break;
    
    case tokenType::Continue:
        root->childs.push_back( MatchContinue(it) );
        root->childs.push_back( MatchSemi(++it) );
        it++;
        break;

    case tokenType::Break:
        root->childs.push_back( MatchBreak(it) );
        root->childs.push_back( MatchSemi(++it) );
        it++;
        break;

    case tokenType::While:
        root->childs.push_back( MatchWhile(it) );
        root->childs.push_back( MatchOpenBracket(++it) );
        root->childs.push_back( parseP(++it) );
        root->childs.push_back( MatchCloseBracket(++it) );
        root->childs.push_back( parseO(++it) );
        it++;
        break;

    case tokenType::If:
        root->childs.push_back( MatchIf(it) );
        root->childs.push_back( MatchOpenBracket(++it) );
        root->childs.push_back( parseP(++it) );
        root->childs.push_back( MatchCloseBracket(++it) );
        root->childs.push_back( parseO(++it) );
        root->childs.push_back( parseO__SingleQuota(++it) );
        it++;
        break;

    case tokenType::Return:
        root->childs.push_back( MatchReturn(it)) ;
        root->childs.push_back( parseP(++it) );
        root->childs.push_back( MatchSemi(++it) );
        it++;
        break;

    case tokenType::Int_C:
    case tokenType::Float_C:
    case tokenType::Long_C:
    case tokenType::Char_C:
    case tokenType::Identifier:
        root->childs.push_back( parseP(it) );
        root->childs.push_back( MatchSemi(++it) );
        it++;
        break;
    
    case tokenType::End:
        root->childs.push_back( MatchEnd(it) );
        it++;
        break;
    
    case tokenType::Else:
        root->childs.push_back( MatchElse(it) );
        root->childs.push_back( parseO(++it) );
        it++;
        break;

    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "O");
        break;
    }       
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseO__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("O_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::Sentence__SingleQuota;
    switch ((*it)->type)
    {
    case tokenType::End :
        root->childs.push_back( MatchEnd(it));
        it++;
        break;
    default:
        if((*it)->value == "else"){
            root->childs.push_back( MatchElse(it) );
            root->childs.push_back( parseO(++it));
            it++;
        }
        break;

        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "O_SingleQuota");
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseP(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("P", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::Expression;
    switch ((*it)->type)
    {
    case tokenType::Identifier:
        root->childs.push_back( MatchIdentifier(it) );
        root->childs.push_back( parseP__DoubleQuota(++it) );
        root->childs.push_back( parseP__TripleQuota(++it) );
        it++;
        break;
    
    case tokenType::Int_C :
        root->childs.push_back( MatchInt_C(it));
        root->childs.push_back( parseP__TripleQuota(++it));
        it++;
        break;

    case tokenType::Float_C :
        root->childs.push_back( MatchFloat_C(it));
        root->childs.push_back( parseP__TripleQuota(++it));
        it++;
        break;

    case tokenType::Long_C :
        root->childs.push_back( MatchLong_C(it));
        root->childs.push_back( parseP__TripleQuota(++it));
        it++;
        break;

    case tokenType::Char_C :
        root->childs.push_back( MatchChar_C(it));
        root->childs.push_back( parseP__TripleQuota(++it));
        it++;
        break;

    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "P");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseP__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("P_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::Expression__SingleQuota;
    switch ((*it)->type)
    {
    case tokenType::And :
        root->childs.push_back( MatchAnd(it));
        root->childs.push_back( parseP(++it) );
        it++;    
        break;
    
    case tokenType::Or :
        root->childs.push_back( MatchOr(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;

    case tokenType::Pl :
        root->childs.push_back( MatchPl(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;
    
    case tokenType::Minus :
        root->childs.push_back( MatchMinus(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;

    case tokenType::Multi :
        root->childs.push_back( MatchMulti(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;

    case tokenType::Divid :
        root->childs.push_back( MatchDivid(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;

    case tokenType::Eq :
        root->childs.push_back( MatchEqual(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;
    
    case tokenType::NtEq :
        root->childs.push_back( MatchNotEqual(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;
    
    case tokenType::Gt :
        root->childs.push_back( MatchGreater(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;

    
    case tokenType::Ls :
        root->childs.push_back( MatchLess(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;
    
    case tokenType::GtEq :
        root->childs.push_back( MatchGreaterEq(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;

    case tokenType::LsEq :
        root->childs.push_back( MatchLessEq(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;

    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "P_SingleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseP__DoubleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("P_DoubleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::Expression__DoubleQuota;
    switch ((*it)->type)
    {
    case tokenType::Assign :
        root->childs.push_back( MatchAssign(it));
        root->childs.push_back( parseP(++it) );
        it++;
        break;
        
    case tokenType::OpenBracket :
        root->childs.push_back( MatchOpenBracket(it));
        root->childs.push_back( parseQ(++it) );
        root->childs.push_back( MatchCloseBracket(++it) );
        it++;
        break;
    
    case tokenType::Semi :
    case tokenType::Comma :
    case tokenType::CloseBracket :
    case tokenType::And :
    case tokenType::Or :
    case tokenType::Pl :
    case tokenType::Minus :
    case tokenType::Multi : 
    case tokenType::Divid :
    case tokenType::Eq :
    case tokenType::NtEq :
    case tokenType:: Gt:
    case tokenType::Ls:
    case tokenType::GtEq :
    case tokenType::LsEq:  
        break;

    
    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "P_DoubleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseP__TripleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("P_TripleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::Expression__TripleQuota;
    switch ((*it)->type)
    {
    case tokenType::Semi :
    case tokenType::CloseBracket:
        break;
    
    case tokenType::And :
    case tokenType::Or :
    case tokenType::Pl :
    case tokenType::Minus :
    case tokenType::Multi : 
    case tokenType::Divid :
    case tokenType::Eq :
    case tokenType::NtEq :
    case tokenType:: Gt:
    case tokenType::Ls:
    case tokenType::GtEq :
    case tokenType::LsEq: 
        root->childs.push_back( parseP__SingleQuota(it) );
        root->childs.push_back( parseP__TripleQuota(++it) );
        it++;
        break;

    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "P_TripleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseQ(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("Q", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ArgumentSequence;
    switch ((*it)->type)
    {
    case tokenType::CloseBracket :
        break;

    case tokenType::Int_C :
    case tokenType::Float_C :
    case tokenType::Long_C :
    case tokenType::Char_C :
    case tokenType::Identifier:
        root->childs.push_back( parseP(it) );
        root->childs.push_back( parseQ(++it) );
        it++;
        break;

    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "Q");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseR(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("R", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::ArgumentSequence;

    switch ((*it)->type)
    {
    case tokenType::Int:
        root->childs.push_back( MatchInt(it) );
        root->childs.push_back( parseR_SingleQuota(++it));
        it++;
        break;
    
    case tokenType::Float:
        root->childs.push_back( MatchFloat(it) );
        root->childs.push_back( parseR_SingleQuota(++it));
        it++;
        break;
    
    case tokenType::Char:
        root->childs.push_back( MatchChar(it) );
        root->childs.push_back( parseR_SingleQuota(++it));
        it++;
        break;

    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "R");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> Parser::parseR_SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it){
    printFuncPath("R_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntaxType = SyntaxUnitType::Array;
    switch ((*it)->type)
    {
    case tokenType::Identifier :
        break;
    
    case tokenType::LeftArray :
        root->childs.push_back( MatchLeftArray(it));
        root->childs.push_back( MatchInt(++it));
        root->childs.push_back( MatchRightArray(++it));

    default:
        unexpectedTokenTypeErrorF((*it), mapFromEnumClassToString[root->syntaxType],    
                                tokenparser.mapFromEnumClassToString[(*it)->type], "R_SingleQuota");
        break;
    }
    return root;
}