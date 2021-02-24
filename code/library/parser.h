#ifndef PARSER_H
#define PARSER_H

#include<memory>
#include<vector>
#include"lex.h"

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
    ParameterSequence,                          // I    形式参数序列
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
    Identifier,                                 // h    标识符
    Nul,                                        //      占位符
};

struct SyntaxTreeNode {
    SyntaxUnitType                                      syntaxType = SyntaxUnitType::Nul;
    std::vector<std::shared_ptr<SyntaxTreeNode >>       childs;
    string                                              curTerminator;
};

#endif