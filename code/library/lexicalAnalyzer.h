#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<memory>


enum class tokenType 
{
                Nul,                            // Initial Type
                Error,                          
                Identifier,
                End,                            // #

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

struct tokenParser;                             //forward declaration

struct token{

    tokenType                                   type = tokenType::Nul;
    std::string                                 value;
    int                                         row = -1;
    int                                         column = -1; 
    bool                                        isKeyWord = false;

};

struct tokenParser {

    const char*                                 fileName = nullptr;

    bool                                        hasError = false;                               
    int                                         rowNum  = 1;                                   
    int                                         columnNum = 0;                                  
    std::unordered_set<std::string>             keyWordsList;                     
    std::vector<std::shared_ptr<token>>         tokenText;                              
    std::unordered_map<tokenType, std::string>  mapFromEnumClassToString;  
    std::unordered_map<std::string, tokenType>  mapFromKeyWordToTokenType;

    tokenParser(const char* filename);
    void Parse();     
    void PrintTokenText();  
};

#endif