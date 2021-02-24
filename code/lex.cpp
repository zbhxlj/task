#include "lex.h"
#include<iostream>
#include<cstdio>

using std::endl;
using std::cerr;
using std::cout;
using std::string;



tokenParser::tokenParser(const char* filename): fileName(filename) {
    keyWordsList = {"if", "else", "while", "for", "return", "break",
                 "continue", "char", "int", "long","float"};
    
    mapFromEnumClassToString = {
        {tokenType::Nul, "Nul"},
        {tokenType::Error, "Error"},
        {tokenType::Identifier, "Identifier"},
        {tokenType::String, "String"},
        {tokenType::Char, "Char"},
        {tokenType::Integer, "Integer"},
        {tokenType::Long, "Long"},
        {tokenType::Float, "Float"},
        {tokenType::KeyWord, "KeyWord"},
        {tokenType::Pl, "Plus Mark"},
        {tokenType::Minus, "Minus"},
        {tokenType::Multi, "Multiply"},
        {tokenType::Divid, "Division"},
        {tokenType::Ls, "Less"},
        {tokenType::LsEq, "LessOrEqual"},
        {tokenType::Eq, "Equal"},
        {tokenType::GtEq, "GreaterEqual"},
        {tokenType::Gt, "GreaterOrEqual"},
        {tokenType::NtEq, "NotEqual"},
        {tokenType::And, "And"}, 
        {tokenType::Or, "Or"},
        {tokenType::Assign, "Assign"},
        {tokenType::OpenBracket, "OpenBracket"},
        {tokenType::CloseBracket, "CloseBracket"},
        {tokenType::Lp, "LeftParenthes"},
        {tokenType::Rp, "RightParenthes"},
        {tokenType::Semi, "Semicolon"},
        {tokenType::Comma, "Comma"}, 
        {tokenType::Quota, "Quotation"},
        {tokenType::SingleQuota, "SingleQuotation"},
        {tokenType::LeftArray, "LeftArray"},
        {tokenType::RightArray, "RightArray"},
        {tokenType::Sharp, "Sharp"}
    };
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
 * @param const char* fileName
 * @return hasUnknowType indicating whether there is Error Type
 */


void tokenParser::Parse(){

    FILE* fp = fopen(fileName, "r");
    char ch;
    string input;
    while((ch = fgetc(fp)) != EOF) input += ch;

    const char* reading = input.c_str();

    State state = State::Begin;
    shared_ptr<token> curToken(nullptr);

    while(*reading){
        columnNum++;
        switch (state)
        {
        case State::Begin:
        {
            curToken.reset(new token());
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
                curToken->type = tokenType::Identifier;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                state = State::InIdentifier;
                break;

            case '1' ... '9' :
                curToken->type = tokenType::Integer;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                state = State:: InInt;
                break;

            case '=' :
                curToken->type = tokenType::Assign;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                state = State::InAssign;
                break;
            case '<' :
                curToken->type = tokenType::Ls;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                state = State::InLess;
                break;
            case '>' :
                curToken->type = tokenType::Gt;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                state = State::InGtr;
                break;
            case '!' :
                curToken->type = tokenType::NtEq;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                state = State::InNotEq;
                break;
            
            case '0' :
                curToken->type = tokenType::Integer;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                state = State::In0Prefix;
                break;
            
            case '+' :
                curToken->type = tokenType::Pl;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '-' :
                curToken->type = tokenType::Minus;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '*' :
                curToken->type = tokenType::Multi;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '/' :
                curToken->type = tokenType::Divid;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            case '(' :
                curToken->type = tokenType::OpenBracket;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case ')' :
                curToken->type = tokenType::CloseBracket;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '[' :
                curToken->type = tokenType::LeftArray;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case ']' :
                curToken->type = tokenType::RightArray;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '{' :
                curToken->type = tokenType::Lp;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '}' :
                curToken->type = tokenType::Rp;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            case ',' :
                curToken->type = tokenType::Comma;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case ';' :
                curToken->type = tokenType::Semi;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            case '\'' :
                curToken->type = tokenType::Char;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                state = State::InSingleQuota;
                break;
            case '\"' : 
                curToken->type = tokenType::String;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                state = State::InDoubleQuota;
                break;

            case '#' :
                curToken->type = tokenType::Sharp;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;

            case '&' :
                curToken->type = tokenType::And;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                state = State::InAnd;
                break;
            case '|' :
                curToken->type = tokenType::Or;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                state = State::InOr;
                break;

            default:
                cerr << "Error: Unexpected Character in state::Begin!" << endl;
                hasError = true;
                curToken->type = tokenType::Error;
                curToken->value += *reading;
                curToken->row = rowNum;
                curToken->column = columnNum;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            } 
            break;
        }

        case State::InIdentifier :
        {
            switch (*reading)
            {
            case 'a' ... 'z' :
            case 'A' ... 'Z' :
            case '0' ... '9' :
                curToken->value += *reading;
                break;
            
            default:
                reading--;
                if(keyWordsList.count(curToken->value) > 0) 
                    curToken->type = tokenType::KeyWord;
                else curToken->type = tokenType::Identifier;
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
                curToken->value += *reading;
                break;
            
            case '.' :
                curToken->type = tokenType::Float;
                curToken->value += *reading;
                state = State::InFloat;
                break;

            case 'L' :
            case 'l' :
                curToken->value += *reading;
                curToken->type = tokenType::Long;
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
                curToken->value += *reading;
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
                curToken->type = tokenType::Eq;
                curToken->value += *reading;
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
                curToken->type = tokenType::LsEq;
                curToken->value += *reading;
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
                curToken->type = tokenType::GtEq;
                curToken->value += *reading;
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
                curToken->value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                cerr << "Unexpected character int State::InNotEq !" << endl;
                hasError = true;
                curToken->type = tokenType::Error;
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
                curToken->type = tokenType::Integer;
                curToken->value += *reading;
                state = State::In0Int;
                break;
            
            case 'x' :
            case 'X' :
                curToken->type = tokenType::Integer;
                curToken->value += *reading;
                state = State::In0xPrefix;
                break;
            
            case '8' ... '9' :
                curToken->type = tokenType::Error;
                curToken->value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;

            default:
                curToken->type = tokenType::Integer;
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
                curToken->value += *reading;
                break;
            case 'l' :
            case 'L' :
                curToken->value += *reading;
                curToken->type = tokenType::Long;
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
                curToken->value += *reading;
                state = State::In0xInt;
                break;
            
            default:
                cerr << "Unexpected character in State::In0xPrefix!" << endl;
                hasError = true;
                curToken->type = tokenType::Error;
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
                curToken->value += *reading;
                break;
            case 'l' :
            case 'L' : 
                curToken->value += *reading;
                curToken->type = tokenType::Long;
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

        case State::InDoubleQuota :
        {
            switch (*reading)
            {
            case '\"' : 
                curToken ->value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                curToken -> value += *reading;
                state = State::InString;
                break;
            }
            break;
        }

        case State::InString :
        {   
            switch (*reading)
            {
            case '\"' : 
                curToken ->value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;

            
            default:
                curToken -> value += *reading;
                break;
            }
            break;
        }

        case State::InAnd :
        {
            switch (*reading)
            {
            case '&' :
                curToken->value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            default:
                cerr << "Unexpected character in State::InAnd!" << endl;
                hasError = true;
                curToken->type = tokenType::Error;
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
                curToken->value += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            default:
                cerr << "Unexpected character in State::InOr!" << endl;
                hasError = true;
                curToken->type = tokenType::Error;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InSingleQuota :
        {
            switch (*reading)
            {
            case '\'':
                cerr << "There must be a character !" << endl;
                curToken -> type = tokenType::Error;
                hasError = true;
                curToken -> value  += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                curToken -> value += *reading;
                state = State::InChar;
                break;
            }
            break;
        }

        case State::InChar :
        {
            switch (*reading)
            {
            case '\'':
                curToken -> value  += *reading;
                tokenText.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                cerr << "There is more than one character!" << endl;
                curToken -> type = tokenType::Error;
                hasError = true;
                while(*reading != '\''){
                    curToken -> value  += *reading;
                    reading++;
                }
                curToken -> value  += *reading;
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
}

void tokenParser::PrintTokenText(){
     for(const auto& x: tokenText){
        cout << "x.type: " << mapFromEnumClassToString[x->type] << " " << "x.value" << " " << x->value << endl;
    }
}
