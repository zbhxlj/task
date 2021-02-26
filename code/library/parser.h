#ifndef PARSER_H
#define PARSER_H

#include<memory>
#include<vector>
#include"lexicalAnalyzer.h"

enum class SyntaxUnitType{  
    Program,                                    // S    程序             
    ExternalDefinitionSequence,                 // A    外部定义序列        
    ExternalDefinitionSequence___SingleQuota,   // A'                 
    ExternalDefinition,                         // B    外部定义     
    ExternalDefinition__SingleQuota,            // B'       
    ExternalVariableDefinition,                 // C    外部变量定义      
    VariableSequence,                           // E    变量序列
    VariableSequence__SingleQuota,              // E'
    FunctionDefinition,                         // G    函数定义
    FunctionDefinition__SingleQuota,            // G'
    Identifier,                                 // H
    Identifier_SingleQuota,                     // H'
    ParameterSequence,                          // I    形式参数序列
    ParameterSequence__SingleQuota,             // I'   
    ComplexSentence,                            // J    复合语句 
    Parameter,                                  // K    形式参数
    LocalVariableDefinitionSequence,            // L    局部变量定义序列
    SentenceSequence,                           // M    语句序列
    LocalVarialbleDefinition,                   // N    局部变量定义
    Sentence,                                   // O    语句
    Sentence__SingleQuota,                      // O'
    Expression,                                 // P    表达式
    Expression__SingleQuota,                    // P'   
    Expression__DoubleQuota,                    // P''
    Expression__TripleQuota,                    // P'''
    ArgumentSequence,                           // Q    实参序列
    TypeName,                                   // R    类型说明符
    Array,                                      // R'   
    Terminator,                                 //      终结符
    Nul,                                        //      占位符
};

struct SyntaxTreeNode {
    SyntaxUnitType                                      syntaxType = SyntaxUnitType::Nul;
    std::vector<std::shared_ptr<SyntaxTreeNode >>       childs;
    std::string                                              curTerminator;
};

struct Parser{
    tokenParser                                         tokenparser;
    std::unordered_map<SyntaxUnitType, std::string>               mapFromEnumClassToString;  

    Parser(const tokenParser& tP);

    std::shared_ptr<SyntaxTreeNode> parse();
    std::shared_ptr<SyntaxTreeNode> parseS(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseA(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseA__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseB(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseB_SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseC(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseE(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseE__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseF(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseG(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseG__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseH(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseH__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseI(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseI__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseJ(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseK(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseL(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseM(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseN(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseO(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseO__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseP(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseP__SingleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseP__DoubleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseP__TripleQuota(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseQ(std::vector<std::shared_ptr<token>>::const_iterator& it);
    std::shared_ptr<SyntaxTreeNode> parseR(std::vector<std::shared_ptr<token>>::const_iterator& it);
};

#endif