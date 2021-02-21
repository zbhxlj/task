#include<vector>
#include<string>
#include<fstream>
#include<unordered_set>
#include<iostream>
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

    void clear(){
        type = tokenType::Nul;
        value.clear();
        row = rowNum;
        column = columnNum;
        isKeyWord = false;
    }
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


using std::vector;
using std::string;
using std::unordered_set;
using std::cerr;
using std::endl;

unordered_set<string> keyWords;                     // 关键字
token::list tokenText;                              // 分词结果

int rowNum = 1; 
int columnNum = 0;

void init(){
    keyWords = {"if", "else", "while", "for", "return", "break",
                 "continue", "char", "int", "long","float"};
}


/**
 * @brief 
 * while(*reading){
 *      switch(state){
 *          case 某个状态 :
 *              switch(*reading){
 *                  case 某个字符 {
 *                      if 目标状态只有虚线出口
 *                          输出token
 *                          state = State::Begin
 *                      else if 目标状态有实线出口
 *                          state = State::NewState
 *                      else if 无法跳到下一个状态, 但是当前状态有虚线出口
 *                          reading--;
 *                          输出一个token;
 *                          state = State::Begin
 *                      else 无法跳到任何状态
 *                          报告错误
 *                          state = State::Begin;
 * 
 *                      break;
 *             }
 *         }  
 *         break;                  
 *     }
 *  reading++;
 * }
 * 
 * @param const char* reading
 * @return 0 indicating ok   -1 indicating something wrong happened
 */


int lex(const char* reading){
    int Err = 0;
    State state = State::Begin;
    token curToken;
    while(*reading){
        columnNum++;
        switch (state)
        {
        case State::Begin:
        {
            curToken.clear();
            switch (*reading)
            {
            case ' ':
                break;
            case '\n':
                rowNum++;
                columnNum = 0;
                break;
            
            case 'a' ... 'z' :
            case 'A' ... 'Z' :
                curToken.type = tokenType::String;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                state = State::InString;
                break;

            case '1' ... '9' :
                curToken.type = tokenType::Integer;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                state = State:: InInt;
                break;

            case '=' :
                curToken.type = tokenType::Assign;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                state = State::InAssign;
                break;
            case '<' :
                curToken.type = tokenType::Ls;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                state = State::InLess;
                break;
            case '>' :
                curToken.type = tokenType::Gt;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                state = State::InGtr;
                break;
            case '!' :
                curToken.type = tokenType::NtEq;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                state = State::InNotEq;
                break;
            
            case '0' :
                curToken.type = tokenType::Integer;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                state = State::In0Prefix;
                break;
            
            case '+' :
                curToken.type = tokenType::Pl;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '-' :
                curToken.type = tokenType::Minus;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '*' :
                curToken.type = tokenType::Multi;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '/' :
                curToken.type = tokenType::Divid;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            case '(' :
                curToken.type = tokenType::OpenBracket;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case ')' :
                curToken.type = tokenType::CloseBracket;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '[' :
                curToken.type = tokenType::LeftArray;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case ']' :
                curToken.type = tokenType::RightArray;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '{' :
                curToken.type = tokenType::Lp;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '}' :
                curToken.type = tokenType::Rp;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            case ',' :
                curToken.type = tokenType::Comma;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case ';' :
                curToken.type = tokenType::Semi;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '\'' :
                curToken.type = tokenType::SingleQuota;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '\"' : 
                curToken.type = tokenType::Quota;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;

            case '#' :
                curToken.type = tokenType::Sharp;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;

            case '&' :
                curToken.type = tokenType::And;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                state = State::InAnd;
                break;
            case '|' :
                curToken.type = tokenType::Or;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                state = State::InOr;
                break;

            default:
                cerr << "Error: Unexpected Character in state::Begin!" << endl;
                Err = -1;
                curToken.type = tokenType::Unknown;
                curToken.value += *reading;
                curToken.row = rowNum;
                curToken.column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            } 
            break;
        }

        case State::InString :
        {
            switch (*reading)
            {
            case 'a' ... 'z' :
            case 'A' ... 'Z' :
            case '0' ... '9' :
                curToken.value += *reading;
                break;
            
            default:
                reading--;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }
        
        case State::InInt :
        {
            switch (*reading)
            {
            case '0' ... '9':
                curToken.value += *reading;
                break;
            
            case '.' :
                curToken.type = tokenType::Float;
                curToken.value += *reading;
                state = State::InFloat;
                break;

            case 'L' :
            case 'l' :
                curToken.type = tokenType::Long;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;

            default:
                reading--;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InFloat :
        {
            switch (*reading)
            {
            case '0' ... '9':
                curToken.value += *reading;
                break;
            
            default:
                reading--;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InAssign :
        {
            switch (*reading)
            {
            case '=':
                curToken.type = tokenType::Eq;
                curToken.value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                reading--;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InLess :
        {
            switch (*reading)
            {
            case '=' :
                curToken.type = tokenType::LsEq;
                curToken.value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                reading--;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InGtr :
        {
            switch (*reading)
            {
            case '=' :
                curToken.type = tokenType::GtEq;
                curToken.value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                reading--;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        
        case State::InNotEq :
        {
            switch (*reading)
            {
            case '=' :
                curToken.value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                cerr << "Unexpected character int State::InNotEq !" << endl;
                Err = -1;
                curToken.type = tokenType::Unknown;
                reading--;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::In0Prefix :
        {
            switch (*reading)
            {
            case '0' ... '7':
                curToken.type = tokenType::Integer;
                curToken.value += *reading;
                state = State::In0Int;
                break;
            
            case 'x' :
            case 'X' :
                curToken.type = tokenType::Integer;
                curToken.value += *reading;
                state = State::In0xPrefix;
                break;

            default:
                curToken.type = tokenType::String;
                reading--;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::In0Int :
        {
            switch (*reading)
            {
            case '0' ... '7':
                curToken.value += *reading;
                break;
            case 'l' :
            case 'L' :
                curToken.type = tokenType::Long;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            default:
                reading--;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::In0xPrefix :
        {   
            switch (*reading)
            {
            case '0' ... '9' :
            case 'a' ... 'f' :
                curToken.value += *reading;
                state = State::In0xInt;
                break;
            
            default:
                curToken.type = tokenType::String;
                reading--;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::In0xInt :
        {
            switch (*reading)
            {
            case '0' ... '9' :
            case 'a' ... 'f' :
                curToken.value += *reading;
                break;
            case 'l' :
            case 'L' : 
                curToken.type = tokenType::Long;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            default:
                reading--;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InAnd :
        {
            switch (*reading)
            {
            case '&' :
                curToken.value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            default:
                cerr << "Unexpected character in State::InAnd!" << endl;
                Err = -1;
                curToken.type = tokenType::Unknown;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InOr :
        {
            switch (*reading)
            {
            case '|' :
                curToken.value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            default:
                cerr << "Unexpected character in State::InOr!" << endl;
                Err = -1;
                curToken.type = tokenType::Unknown;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        default:
            cerr << "Unexpected case !" << endl;
            break;
        }
        reading++;
    }
    return Err;
}