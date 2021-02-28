#ifndef ENUM_CLASS_H
#define ENUM_CLASS_H

#include<unordered_map>
#include<string>

enum class TokenType 
{
                Nul,                            // Initial Type
                Error,                          
                Identifier,
                End,                            // $

                String,                         // " xxx " 
                Char_C,                         // ' x '
                Int_C,                          // 0123 0x123 123 
                Long_C,                         // 0123L 0X123L 123L
                Float_C,                        // 1.23  1.23E0 1.23e0

                If,                             // if
                Else,                           // else
                While,                          // while
                For,                            // for
                Return,                         // return
                Break,                          // break
                Continue,                       // continue
                Char,                           // char
                Int,                            // int
                Long,                           // long
                Float,                          // float

                Pl,                             // +
                Minus,                          // -
                Multi,                          // *
                Divid,                          // /

                Ls,                             // <
                LsEq,                           // <=
                Eq,                             // ==
                GtEq,                           // >=
                Gt,                             // >
                NtEq,                           // !=
                
                And,                            // &&
                Or,                             // ||
                Assign,                         // =

                OpenBracket,                    // (
                CloseBracket,                   // )

                Lp,                             // {
                Rp,                             // }
                Semi,                           // ;
                Comma,                          // ,
                Quota,                          // "
                SingleQuota,                    // '
                
                LeftArray,                      // [
                RightArray,                     // ]

                Sharp,                          // #
                };

enum class State{
    Begin,                                      // 0
    InIdentifier,                               // 1
    InInt,                                      // 2
    InFloat,                                    // 3
    InLong,                                     // 4
    InAssign,                                   // 5
    InEqualIgnored,                             // 6
    InLess,                                     // 7
    InLessEqIgnored,                            // 8
    InGtr,                                      // 9
    InGtrEqIgnored,                             // 10
    InNotEq,                                    // 11
    InNotEqIgnored,                             // 12
    In0Prefix,                                  // 13
    In0Int,                                     // 14
    In0LongIgored,                              // 15
    In0xPrefix,                                 // 16
    In0xInt,                                    // 17
    In0xLongIgnored,                            // 18       
    InArithmeticIgnored,                        // 19
    InBracketIgnored,                           // 20
    InDelimiterIgnored,                         // 21
    InDoubleQuota,                              // 22
    InString,                                   // 23
    InStringIgnored,                            // 24
    InAnd,                                      // 25
    InAndIgnored,                               // 26
    InOr,                                       // 27
    InOrIgnored,                                // 28
    InSingleQuota,                              // 29
    InChar,                                     // 30
    InCharIgnored,                              // 31
};

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

inline std::unordered_map<TokenType, std::string>  MapFromTokenTypeToString = {
        {TokenType::Nul, "Nul"},
        {TokenType::Error, "Error"},
        {TokenType::End, "End"},
        {TokenType::Identifier, "Identifier"},
        {TokenType::String, "String"},
        {TokenType::Char_C, "Char_C"},
        {TokenType::Int_C, "Int_C"},
        {TokenType::Long_C, "Long_C"},
        {TokenType::Float_C, "Float_C"},
        {TokenType::If, "If"},
        {TokenType::Else, "Else"},
        {TokenType::While, "While"},
        {TokenType::For, "For"},
        {TokenType::Return, "Return"},
        {TokenType::Break, "Break"},
        {TokenType::Continue, "Continue"},
        {TokenType::Char, "Char"},
        {TokenType::Int, "Int"},
        {TokenType::Long, "Long"},
        {TokenType::Float, "Float"},
        {TokenType::Pl, "Plus Mark"},
        {TokenType::Minus, "Minus"},
        {TokenType::Multi, "Multiply"},
        {TokenType::Divid, "Division"},
        {TokenType::Ls, "Less"},
        {TokenType::LsEq, "LessOrEqual"},
        {TokenType::Eq, "Equal"},
        {TokenType::GtEq, "GreaterEqual"},
        {TokenType::Gt, "GreaterOrEqual"},
        {TokenType::NtEq, "NotEqual"},
        {TokenType::And, "And"}, 
        {TokenType::Or, "Or"},
        {TokenType::Assign, "Assign"},
        {TokenType::OpenBracket, "OpenBracket"},
        {TokenType::CloseBracket, "CloseBracket"},
        {TokenType::Lp, "LeftParenthes"},
        {TokenType::Rp, "RightParenthes"},
        {TokenType::Semi, "Semicolon"},
        {TokenType::Comma, "Comma"}, 
        {TokenType::Quota, "Quotation"},
        {TokenType::SingleQuota, "SingleQuotation"},
        {TokenType::LeftArray, "LeftArray"},
        {TokenType::RightArray, "RightArray"},
        {TokenType::Sharp, "Sharp"}
    };


inline std::unordered_map<std::string, TokenType>  MapFromKeyWordToTokenType = {
        {"if", TokenType::If},
        {"else", TokenType::Else},
        {"while", TokenType::While},
        {"for", TokenType::For},
        {"return", TokenType::Return},
        {"break", TokenType::Break},
        {"continue", TokenType::Continue},
        {"char", TokenType::Char},
        {"int", TokenType::Int},
        {"long", TokenType::Long},
        {"float", TokenType::Float}
    };

inline std::unordered_map<SyntaxUnitType, std::string>    MapFromSyntaxUnitTypeToString = {
        {SyntaxUnitType::Program, "Program"},
        {SyntaxUnitType::ExternalDefinitionSequence, "ExternalDefinitionSequence"},
        {SyntaxUnitType::ExternalDefinitionSequence___SingleQuota, "ExternalDefinitionSequence_SingleQuota"},
        {SyntaxUnitType::ExternalDefinition, "ExternalDefinition"},
        {SyntaxUnitType::ExternalDefinition__SingleQuota, "ExternalDefinition_SingleQuota"},
        {SyntaxUnitType::ExternalVariableDefinition, "ExternalVarialbleDefinition"},
        {SyntaxUnitType::VariableSequence, "VariableSequence"},
        {SyntaxUnitType::VariableSequence__SingleQuota, "VariableSequence_SingleQuota"},
        {SyntaxUnitType::FunctionDefinition, "FunctionDefinition"},
        {SyntaxUnitType::FunctionDefinition__SingleQuota, "FunctionDefinition__SingleQuota"},
        {SyntaxUnitType::Identifier, "Identifier"},
        {SyntaxUnitType::Identifier_SingleQuota, "Identifier__SingleQuota"},
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

#endif