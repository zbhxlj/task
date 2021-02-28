#include"../library/syntax_analysis.h"
#include<memory>
#include<vector>
#include "syntax_analysis_util.cc"
#include<unordered_map>


SyntaxAnalyzer::SyntaxAnalyzer(const LexicalAnalyzer& tP) : lexical_analyzer(tP) {}

void SyntaxAnalyzer::Parse(){
    auto it = lexical_analyzer.token_text.cbegin();
    printFuncPath("", it);
    root = ParseS(it);
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "Compilation success !" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << std::endl;
    return;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseS(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("S", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::Program;
    switch ((*it)->token_type)
    {
    case TokenType::Int:
    case TokenType::Float:
    case TokenType::Char:
        root->childs.push_back( ParseA(it) );
        break;
    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "S");
        break;
    }
    return root;
}


std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseA(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("A", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::ExternalDefinitionSequence;
    switch ((*it)->token_type)
    {
    case TokenType::Int :
    case TokenType::Float :
    case TokenType::Char :
        root->childs.push_back(parseB(it));
        root->childs.push_back(ParseA__SingleQuota(it));
        break;
    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "A");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseA__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("A_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::ExternalDefinition__SingleQuota;
    switch ((*it)->token_type)
    {
    case TokenType::Int :
    case TokenType::Float :
    case TokenType::Char :
        root->childs.push_back( ParseA(it) );
        break;

    case TokenType::End :
        root ->childs.push_back( MatchEnd(it) );
        it++;
        break;

    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "A_SingleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::parseB(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("B", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::ExternalDefinition;
    switch ((*it) -> token_type)
    {
    case TokenType::Int :
    case TokenType::Float :
    case TokenType::Char :
        root->childs.push_back( ParseR(it) );
        root->childs.push_back( ParseH(it) );
        root->childs.push_back( ParseB_SingleQuota(it) );
        break;
    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "B");    
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseB_SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("B_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::ExternalDefinition__SingleQuota;
    switch ((*it) -> token_type)
    {
    case TokenType::OpenBracket:
        root->childs.push_back( ParseG(it) );
        break;

    case TokenType::Comma :
    case TokenType::Semi :
        root->childs.push_back( parseE__SingleQuota(it) );
        break;
        
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "B_SingleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseC(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("C", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::ExternalVariableDefinition;
    switch ((*it) -> token_type)
    {
    case TokenType::Int :
    case TokenType::Float :
    case TokenType::Char :
        root->childs.push_back( ParseR(it) );
        root->childs.push_back( ParseE(it));
        break;
    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "C");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseE(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("E", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::VariableSequence;
    switch ((*it) -> token_type)
    {
    case TokenType::Identifier:
        root->childs.push_back( MatchIdentifier(it) );
        it++;
        root->childs.push_back( parseE__SingleQuota(it));
        break;
    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "E");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::parseE__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("E_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::VariableSequence__SingleQuota;
    switch ((*it) -> token_type)
    {
    case TokenType::Comma :
        root->childs.push_back( MatchComma(it));
        it++;
        root->childs.push_back( ParseE(it) );
        break;
    
    case TokenType::Semi :
        root->childs.push_back( MatchSemi(it));
        it++;
        break;

    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "E_SingleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseG(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("G", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::FunctionDefinition;
    switch ((*it)->token_type)
    {
    case TokenType::OpenBracket :
        root->childs.push_back( MatchOpenBracket(it) );
        it++;
        root->childs.push_back( ParseI(it) );
        root->childs.push_back( MatchCloseBracket(it) );
        it++;
        root->childs.push_back( ParseG__SingleQuota(it) );
        break;
    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "G");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseG__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("G_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::FunctionDefinition__SingleQuota;
    switch ((*it)->token_type)
    {
    case TokenType::Lp :
        root->childs.push_back( ParseJ(it) );
        break;
    
    case TokenType::Semi :
        root->childs.push_back( MatchSemi(it));
        it++;
        break;

    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "G_SingleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseH(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("H", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::Identifier;
    switch ((*it)->token_type)
    {
    case TokenType::Identifier :
        root->childs.push_back( MatchIdentifier(it) );
        it++;
        root->childs.push_back( ParseH__SingleQuota(it) );
        break;
    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "H");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseH__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("H_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::Identifier_SingleQuota;
    switch ((*it)->token_type)
    {
    case TokenType::OpenBracket :
    case TokenType::Comma :
    case TokenType::Semi :
    case TokenType::CloseBracket :
        break;
    
    case TokenType::LeftArray :
        root->childs.push_back( MatchLeftArray(it) );
        it++;
        root->childs.push_back( MatchInt_C(it) );
        it++;
        root->childs.push_back( MatchRightArray(it));
        it++;
        break;

    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "H_SingleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseI(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("I", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::ParameterSequence;
    switch ((*it)->token_type)
    {
    case TokenType::CloseBracket :
        break;
    
    case TokenType::Int :
    case TokenType::Float :
    case TokenType::Char :
        root->childs.push_back( ParseK(it) );
        root->childs.push_back( ParseI__SingleQuota(it) );
        break;

    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "I");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseI__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("I_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::ParameterSequence__SingleQuota;
    switch ((*it)->token_type)
    {
    case TokenType::Comma :
        root->childs.push_back( MatchComma(it) );
        it++;
        root->childs.push_back( ParseI(it) );
        break;

    case TokenType::CloseBracket :
        break;
    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "I");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseK(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("K", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::Parameter;
    switch ((*it)->token_type)
    {
    case TokenType::Int :
    case TokenType::Float :
    case TokenType::Char :
        root->childs.push_back( ParseR(it) );
        root->childs.push_back( ParseH(it) );
        break;
    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "K");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseJ(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("J", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::ComplexSentence;
    switch ((*it) -> token_type)
    {
    case TokenType::Lp :
        root->childs.push_back( MatchLp(it) );
        it++;
        root->childs.push_back( ParseL(it) );
        root->childs.push_back( ParseM(it) );
        root->childs.push_back( MatchRp(it) );
        it++;
        break;
    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "J");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseL(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("L", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::LocalVariableDefinitionSequence;
    switch ((*it) -> token_type)
    {
    case TokenType::Int :
    case TokenType::Float :
    case TokenType::Char :
        root->childs.push_back( ParseN(it) );
        root->childs.push_back( ParseL(it) );
        break;

    

    default:
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseN(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("N", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::LocalVarialbleDefinition;
    switch ((*it) -> token_type)
    {
    case TokenType::Int :
    case TokenType::Float :
    case TokenType::Char :
        root->childs.push_back( ParseR(it) );
        root->childs.push_back( ParseE(it) );
        break;
    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "N");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseM(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("M", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::SentenceSequence;
    switch ((*it) -> token_type)
    {
    case TokenType::Rp :
        break;
    
    case TokenType::Int_C:
    case TokenType::Char_C:
    case TokenType::Float_C:
    case TokenType::Long_C:
    case TokenType::Identifier:
        root->childs.push_back( ParseO(it));
        root->childs.push_back( ParseM(it) );
        break;

    case TokenType::Return:
    case TokenType::If :
    case TokenType::While:
    case TokenType::Break:
    case TokenType::Continue:
    case TokenType::For:
        root->childs.push_back( ParseO(it));
        root->childs.push_back( ParseM(it) );
        break;
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "M");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseO(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("O", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::Sentence;
    switch ((*it) -> token_type)
    {
    case TokenType::For:
        root->childs.push_back( MatchFor(it) );
        it++;
        root->childs.push_back( MatchOpenBracket(it) );
        it++;
        root->childs.push_back( ParseP(it) );
        root->childs.push_back( MatchSemi(it) );
        it++;
        root->childs.push_back( ParseP(it) );
        root->childs.push_back( MatchSemi(it) );
        it++;
        root->childs.push_back( ParseP(it) );
        root->childs.push_back( MatchCloseBracket(it) );
        it++;
        root->childs.push_back( ParseO(it) );
        break;
    
    case TokenType::Continue:
        root->childs.push_back( MatchContinue(it) );
        it++;
        root->childs.push_back( MatchSemi(it) );
        it++;
        break;

    case TokenType::Break:
        root->childs.push_back( MatchBreak(it) );
        it++;
        root->childs.push_back( MatchSemi(it) );
        it++;
        break;

    case TokenType::While:
        root->childs.push_back( MatchWhile(it) );
        it++;
        root->childs.push_back( MatchOpenBracket(it) );
        it++;
        root->childs.push_back( ParseP(it) );
        root->childs.push_back( MatchCloseBracket(it) );
        it++;
        root->childs.push_back( ParseO(it) );
        break;

    case TokenType::If:
        root->childs.push_back( MatchIf(it) );
        it++;
        root->childs.push_back( MatchOpenBracket(it) );
        it++;
        root->childs.push_back( ParseP(it) );
        root->childs.push_back( MatchCloseBracket(it) );
        it++;
        root->childs.push_back( ParseO(it) );
        root->childs.push_back( ParseO__SingleQuota(it) );
        break;

    case TokenType::Return:
        root->childs.push_back( MatchReturn(it)) ;
        it++;
        root->childs.push_back( ParseP(it) );
        root->childs.push_back( MatchSemi(it) );
        it++;
        break;

    case TokenType::Int_C:
    case TokenType::Float_C:
    case TokenType::Long_C:
    case TokenType::Char_C:
    case TokenType::Identifier:
        root->childs.push_back( ParseP(it) );
        root->childs.push_back( MatchSemi(it) );
        it++;
        break;
    
    case TokenType::End:
        root->childs.push_back( MatchEnd(it) );
        it++;
        break;
    
    case TokenType::Else:
        root->childs.push_back( MatchElse(it) );
        it++;
        root->childs.push_back( ParseO(it) );
        break;

    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "O");
        break;
    }       
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseO__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("O_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::Sentence__SingleQuota;
    switch ((*it)->token_type)
    {
    case TokenType::End :
        root->childs.push_back( MatchEnd(it));
        it++;
        break;
    
    case TokenType::Rp :
        break;

    case TokenType::Else :
        root->childs.push_back( MatchElse(it) );
        it++;
        root->childs.push_back( ParseO(it));
        break;

    default:

        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "O_SingleQuota");

        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseP(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("P", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::Expression;
    switch ((*it)->token_type)
    {
    case TokenType::Identifier:
        root->childs.push_back( MatchIdentifier(it) );
        it++;
        root->childs.push_back( ParseP__DoubleQuota(it) );
        root->childs.push_back( ParseP__TripleQuota(it) );
        break;
    
    case TokenType::Int_C :
        root->childs.push_back( MatchInt_C(it));
        it++;
        root->childs.push_back( ParseP__TripleQuota(it));
        break;

    case TokenType::Float_C :
        root->childs.push_back( MatchFloat_C(it));
        it++;
        root->childs.push_back( ParseP__TripleQuota(it));
        break;

    case TokenType::Long_C :
        root->childs.push_back( MatchLong_C(it));
        it++;
        root->childs.push_back( ParseP__TripleQuota(it));
        break;

    case TokenType::Char_C :
        root->childs.push_back( MatchChar_C(it));
        it++;
        root->childs.push_back( ParseP__TripleQuota(it));
        break;

    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "P");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseP__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("P_SingleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::Expression__SingleQuota;
    switch ((*it)->token_type)
    {
    case TokenType::And :
        root->childs.push_back( MatchAnd(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;
    
    case TokenType::Or :
        root->childs.push_back( MatchOr(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;

    case TokenType::Pl :
        root->childs.push_back( MatchPl(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;
    
    case TokenType::Minus :
        root->childs.push_back( MatchMinus(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;

    case TokenType::Multi :
        root->childs.push_back( MatchMulti(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;

    case TokenType::Divid :
        root->childs.push_back( MatchDivid(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;

    case TokenType::Eq :
        root->childs.push_back( MatchEqual(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;
    
    case TokenType::NtEq :
        root->childs.push_back( MatchNotEqual(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;
    
    case TokenType::Gt :
        root->childs.push_back( MatchGreater(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;

    
    case TokenType::Ls :
        root->childs.push_back( MatchLess(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;
    
    case TokenType::GtEq :
        root->childs.push_back( MatchGreaterEq(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;

    case TokenType::LsEq :
        root->childs.push_back( MatchLessEq(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;

    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "P_SingleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseP__DoubleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("P_DoubleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::Expression__DoubleQuota;
    switch ((*it)->token_type)
    {
    case TokenType::Assign :
        root->childs.push_back( MatchAssign(it));
        it++;
        root->childs.push_back( ParseP(it) );
        break;
        
    case TokenType::OpenBracket :
        root->childs.push_back( MatchOpenBracket(it));
        it++;
        root->childs.push_back( ParseQ(it) );
        root->childs.push_back( MatchCloseBracket(it) );
        it++;
        break;
    
    case TokenType::Semi :
    case TokenType::Comma :
    case TokenType::CloseBracket :
    case TokenType::And :
    case TokenType::Or :
    case TokenType::Pl :
    case TokenType::Minus :
    case TokenType::Multi : 
    case TokenType::Divid :
    case TokenType::Eq :
    case TokenType::NtEq :
    case TokenType:: Gt:
    case TokenType::Ls:
    case TokenType::GtEq :
    case TokenType::LsEq:  
        break;

    
    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "P_DoubleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseP__TripleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("P_TripleQuota", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::Expression__TripleQuota;
    switch ((*it)->token_type)
    {
    case TokenType::Semi :
    case TokenType::CloseBracket:
        break;
    
    case TokenType::And :
    case TokenType::Or :
    case TokenType::Pl :
    case TokenType::Minus :
    case TokenType::Multi : 
    case TokenType::Divid :
    case TokenType::Eq :
    case TokenType::NtEq :
    case TokenType:: Gt:
    case TokenType::Ls:
    case TokenType::GtEq :
    case TokenType::LsEq: 
        root->childs.push_back( ParseP__SingleQuota(it) );
        root->childs.push_back( ParseP__TripleQuota(it) );
        break;

    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "P_TripleQuota");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseQ(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("Q", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::ArgumentSequence;
    switch ((*it)->token_type)
    {
    case TokenType::CloseBracket :
        break;

    case TokenType::Int_C :
    case TokenType::Float_C :
    case TokenType::Long_C :
    case TokenType::Char_C :
    case TokenType::Identifier:
        root->childs.push_back( ParseP(it) );
        root->childs.push_back( ParseQ(it) );
        break;

    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "Q");
        break;
    }
    return root;
}

std::shared_ptr<SyntaxTreeNode> SyntaxAnalyzer::ParseR(std::vector<std::shared_ptr<Token>>::const_iterator& it){
    printFuncPath("R", it);
    std::shared_ptr<SyntaxTreeNode> root = std::make_shared<SyntaxTreeNode>();
    root->syntax_type = SyntaxUnitType::TypeName;

    switch ((*it)->token_type)
    {
    case TokenType::Int:
        root->childs.push_back( MatchInt(it) );
        it++;
        break;
    
    case TokenType::Float:
        root->childs.push_back( MatchFloat(it) );
        it++;
        break;
    
    case TokenType::Char:
        root->childs.push_back( MatchChar(it) );
        it++;
        break;

    default:
        UnexpectedTokenTypeErrorF((*it), MapFromSyntaxUnitTypeToString[root->syntax_type],    
                                MapFromTokenTypeToString[(*it)->token_type], "R");
        break;
    }
    return root;
}
