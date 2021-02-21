#include<vector>
#include<string>
#include<fstream>
enum class tokenType 
{
                Nul,
                Identifier,

                Character,                      // 'a'-'z''A'-'Z'  
                Integer,                        // 0123 0x123 123 
                LongNum,                        // 0123L 0X123L 123L
                FloatNum,                       // 1.23  1.23E0 1.23e0


                If,                             //if
                Else,                           //else
                While,                          //while
                For,                            //for
                Return,                         //return
                Break,                          //break
                Continue,                       //continue
                Char,                           //char
                Int,                            //int
                Long,                           //long
                Float,                          //float

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

                LP,                             // {
                RP,                             // }
                SEMI,                           // ;
                COMMA,                          // ,
                Quota,                          // "
                SingleQuota,                    // '
                
                LeftArray,                      // [
                RightArray,                     // ]

                Sharp,                          // #
                LeftG,                          // <
                RightG,                         // >
                };


struct token{
    using list = vector<token>;

    tokenType               type = tokenType::Nul;
    string                  value;
    int                     row = -1;
    int                     column = -1; 
    bool                    isKeyWord = false;
};


enum class State{
    Begin,                                      // 0
    InString,                                   // 1
    InInt,                                      // 2
    InFloat,                                    // 3
    InLong,                                     // 4
    InAssign,                                   // 5
    InEqual,                                    // 6
    InLess,                                     // 7
    InLessEq,                                   // 8
    InGtr,                                      // 9
    InGtrEq,                                    // 10
    InNotEq,                                    // 11
                                                // 12
    In0Int,                                     // 13
    In0xInt,                                    // 14
    In0Long,                                    // 15

};

using std::vector;
using std::string;

token::list tokenText;                              // 分词结果

int rowNum = 0; 
int columnNum = 0;
int lex(const char* reading){
    while(*reading){

    }
}