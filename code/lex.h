#include<string>
#include<vector>
#include<iostream>

using std::vector;
using std::string;

void init();
int lex(const char* reading);

enum class tokenType 
{
                Nul,
                Unknown,
                Identifier,

                String,                         // 'a'-'z''A'-'Z'  
                Integer,                        // 0123 0x123 123 
                Long,                        // 0123L 0X123L 123L
                Float,                       // 1.23  1.23E0 1.23e0

                KeyWord,                        // int  long  float  if  else ...

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

struct token{
    using list = vector<token>;

    tokenType               type = tokenType::Nul;
    string                  value;
    int                     row = -1;
    int                     column = -1; 
    bool                    isKeyWord = false;

    void clear();
};


enum class State{
    Begin,                                      // 0
    InString,                                   // 1
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
    InSharpIgnored,                             // 22
    InAnd,                                      // 23
    InAndIgnored,                               // 24
    InOr,                                       // 25
    InOrIgnored,                                // 26
};

