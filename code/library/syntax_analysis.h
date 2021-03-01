#ifndef SYNTAXANALYSIS_H
#define SYNTAXANALYSIS_H

#include<memory>
#include<vector>
#include"lexical_analysis.h"

// SyntaxTreeNode makes up the abstract syntax tree. 
struct SyntaxTreeNode {
    SyntaxUnitType                                      syntax_type = SyntaxUnitType::Nul;
    std::vector<std::shared_ptr<SyntaxTreeNode >>       childs;
    std::shared_ptr<Token>                              token = nullptr;              
};

// SyntaxAnalyzer parses to check whether it is grammatical.
// 
// Example :
//    SyntaxAnalyzer   syntax_analyzer(lexical_analyzer);
//    syntax_analyzer.Parse();
struct SyntaxAnalyzer{
    LexicalAnalyzer                                     lexical_analyzer;
    std::shared_ptr<SyntaxTreeNode>                     root;


    SyntaxAnalyzer(const LexicalAnalyzer& tP);

    void Parse();
    std::shared_ptr<SyntaxTreeNode> ParseS(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseA(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseA__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseB(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseB_SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseC(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseE(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseE__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseF(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseG(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseG__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseH(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseH__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseI(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseI__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseJ(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseK(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseL(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseM(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseN(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseO(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseO__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseP(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseP__SingleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseP__DoubleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseP__TripleQuota(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseQ(std::vector<std::shared_ptr<Token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> ParseR(std::vector<std::shared_ptr<Token>>::const_iterator& it);
};

#endif