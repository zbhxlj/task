#include "../library/lexical_analysis.h"
#include<iostream>
#include<cstdio>


LexicalAnalyzer::LexicalAnalyzer(const Preprocesser& preprocesser)
                                                        : preprocesser(preprocesser) {}


/**
 * @brief 
 * while(*current_position){
 *      switch(state){
 *          case 某个状态 :
 *              switch(*current_position){
 *                  case 某个字符 {
 *                      if 目标状态只有虚线出口
 *                          输出Token
 *                          state = State::Begin
 *                      else if 目标状态有实线出口
 *                          state = State::NewState
 *                      else if 无法跳到下一个状态, 但是当前状态有虚线出口
 *                          current_position--;
 *                          输出一个Token;
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
 *  current_position++;
 * }
 * 
 * @input output_file_after_preprocess
 * @return token_text
 */


void LexicalAnalyzer::LexicalAnalyze(){

    const char* current_position = preprocesser.output_file_after_preprocess->c_str();

    State state = State::Begin;
    std::shared_ptr<Token> curToken(nullptr);

    while(*current_position){
        current_number_of_column++;
        switch (state)
        {
        case State::Begin:
        {
            curToken.reset(new Token());
            switch (*current_position)
            {
            case '\t':
                current_number_of_column += 3;
                break;
            case ' ':
                break;
            case '\n':
                current_number_of_row++;
                current_number_of_column = 0;
                break;
            
            case 'a' ... 'z' :
            case 'A' ... 'Z' :
                curToken->token_type = TokenType::Identifier;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                state = State::InIdentifier;
                break;

            case '1' ... '9' :
                curToken->token_type = TokenType::Int_C;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                state = State:: InInt;
                break;

            case '=' :
                curToken->token_type = TokenType::Assign;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                state = State::InAssign;
                break;
            case '<' :
                curToken->token_type = TokenType::Ls;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                state = State::InLess;
                break;
            case '>' :
                curToken->token_type = TokenType::Gt;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                state = State::InGtr;
                break;
            case '!' :
                curToken->token_type = TokenType::NtEq;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                state = State::InNotEq;
                break;
            
            case '0' :
                curToken->token_type = TokenType::Int_C;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                state = State::In0Prefix;
                break;
            
            case '+' :
                curToken->token_type = TokenType::Pl;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            case '-' :
                curToken->token_type = TokenType::Minus;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            case '*' :
                curToken->token_type = TokenType::Multi;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            case '/' :
                curToken->token_type = TokenType::Divid;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            
            case '(' :
                curToken->token_type = TokenType::OpenBracket;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            case ')' :
                curToken->token_type = TokenType::CloseBracket;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            case '[' :
                curToken->token_type = TokenType::LeftArray;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            case ']' :
                curToken->token_type = TokenType::RightArray;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            case '{' :
                curToken->token_type = TokenType::Lp;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            case '}' :
                curToken->token_type = TokenType::Rp;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            
            case ',' :
                curToken->token_type = TokenType::Comma;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            case ';' :
                curToken->token_type = TokenType::Semi;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            case '\'' :
                curToken->token_type = TokenType::Char;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                state = State::InSingleQuota;
                break;
            case '\"' : 
                curToken->token_type = TokenType::String;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                state = State::InDoubleQuota;
                break;

            case '#' :
                curToken->token_type = TokenType::Sharp;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;

            case '&' :
                curToken->token_type = TokenType::And;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                state = State::InAnd;
                break;
            case '|' :
                curToken->token_type = TokenType::Or;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                state = State::InOr;
                break;

            default:
                std::cerr << "character : " << *current_position << std::endl;
                std::cerr << "Error: Unexpected Character in state::Begin!" << std::endl;
                has_error_when_parsing = true;
                curToken->token_type = TokenType::Error;
                curToken->token_value += *current_position;
                curToken->number_of_row = current_number_of_row;
                curToken->number_of_column = current_number_of_column;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            } 
            break;
        }

        case State::InIdentifier :
        {
            switch (*current_position)
            {
            case 'a' ... 'z' :
            case 'A' ... 'Z' :
            case '0' ... '9' :
                curToken->token_value += *current_position;
                break;
            
            default:
                current_position--;
                if(MapFromKeyWordToTokenType.count(curToken->token_value) > 0){
                    curToken->token_type = MapFromKeyWordToTokenType[curToken -> token_value];
                } 
                else curToken->token_type = TokenType::Identifier;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }
        
        case State::InInt :
        {
            switch (*current_position)
            {
            case '0' ... '9':
                curToken->token_value += *current_position;
                break;
            
            case '.' :
                curToken->token_type = TokenType::Float_C;
                curToken->token_value += *current_position;
                state = State::InFloat;
                break;

            case 'L' :
            case 'l' :
                curToken->token_value += *current_position;
                curToken->token_type = TokenType::Long_C;
                token_text.push_back(curToken);
                state = State::Begin;
                break;

            default:
                current_position--;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InFloat :
        {
            switch (*current_position)
            {
            case '0' ... '9':
                curToken->token_value += *current_position;
                break;
            
            default:
                current_position--;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InAssign :
        {
            switch (*current_position)
            {
            case '=':
                curToken->token_type = TokenType::Eq;
                curToken->token_value += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                current_position--;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InLess :
        {
            switch (*current_position)
            {
            case '=' :
                curToken->token_type = TokenType::LsEq;
                curToken->token_value += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                current_position--;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InGtr :
        {
            switch (*current_position)
            {
            case '=' :
                curToken->token_type = TokenType::GtEq;
                curToken->token_value += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                current_position--;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        
        case State::InNotEq :
        {
            switch (*current_position)
            {
            case '=' :
                curToken->token_value += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                std::cerr << "Unexpected character int State::InNotEq !" << std::endl;
                has_error_when_parsing = true;
                curToken->token_type = TokenType::Error;
                current_position--;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::In0Prefix :
        {
            switch (*current_position)
            {
            case '0' ... '7':
                curToken->token_type = TokenType::Int_C;
                curToken->token_value += *current_position;
                state = State::In0Int;
                break;
            
            case 'x' :
            case 'X' :
                curToken->token_type = TokenType::Int_C;
                curToken->token_value += *current_position;
                state = State::In0xPrefix;
                break;
            
            case '8' ... '9' :
                curToken->token_type = TokenType::Error;
                curToken->token_value += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;

            default:
                curToken->token_type = TokenType::Int_C;
                current_position--;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::In0Int :
        {
            switch (*current_position)
            {
            case '0' ... '7':
                curToken->token_value += *current_position;
                break;
            case 'l' :
            case 'L' :
                curToken->token_value += *current_position;
                curToken->token_type = TokenType::Long_C;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            default:
                current_position--;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::In0xPrefix :
        {   
            switch (*current_position)
            {
            case '0' ... '9' :
            case 'a' ... 'f' :
                curToken->token_value += *current_position;
                state = State::In0xInt;
                break;
            
            default:
                std::cerr << "Unexpected character in State::In0xPrefix!" << std::endl;
                has_error_when_parsing = true;
                curToken->token_type = TokenType::Error;
                current_position--;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::In0xInt :
        {
            switch (*current_position)
            {
            case '0' ... '9' :
            case 'a' ... 'f' :
                curToken->token_value += *current_position;
                break;
            case 'l' :
            case 'L' : 
                curToken->token_value += *current_position;
                curToken->token_type = TokenType::Long_C;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            default:
                current_position--;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InDoubleQuota :
        {
            switch (*current_position)
            {
            case '\"' : 
                curToken ->token_value += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                curToken -> token_value += *current_position;
                state = State::InString;
                break;
            }
            break;
        }

        case State::InString :
        {   
            switch (*current_position)
            {
            case '\"' : 
                curToken ->token_value += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;

            
            default:
                curToken -> token_value += *current_position;
                break;
            }
            break;
        }

        case State::InAnd :
        {
            switch (*current_position)
            {
            case '&' :
                curToken->token_value += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            default:
                std::cerr << "Unexpected character in State::InAnd!" << std::endl;
                has_error_when_parsing = true;
                curToken->token_type = TokenType::Error;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InOr :
        {
            switch (*current_position)
            {
            case '|' :
                curToken->token_value += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            default:
                std::cerr << "Unexpected character in State::InOr!" << std::endl;
                has_error_when_parsing = true;
                curToken->token_type = TokenType::Error;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        case State::InSingleQuota :
        {
            switch (*current_position)
            {
            case '\'':
                std::cerr << "There must be a character !" << std::endl;
                curToken -> token_type = TokenType::Error;
                has_error_when_parsing = true;
                curToken -> token_value  += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                curToken -> token_value += *current_position;
                state = State::InChar;
                break;
            }
            break;
        }

        case State::InChar :
        {
            switch (*current_position)
            {
            case '\'':
                curToken -> token_value  += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            
            default:
                std::cerr << "There is more than one character!" << std::endl;
                curToken -> token_type = TokenType::Error;
                has_error_when_parsing = true;
                while(*current_position != '\''){
                    curToken -> token_value  += *current_position;
                    current_position++;
                }
                curToken -> token_value  += *current_position;
                token_text.push_back(curToken);
                state = State::Begin;
                break;
            }
            break;
        }

        default:
            std::cerr << "Unexpected case !" << std::endl;
            break;
        }
        current_position++;
    }
    curToken.reset(new Token());
    curToken->number_of_column = current_number_of_column;
    curToken->number_of_row = current_number_of_row;
    curToken->token_type = TokenType::End;
    curToken->token_value = "$";
    token_text.push_back(curToken);
}

void LexicalAnalyzer::PrintTokenText(){
    int i = 0;
     for(const auto& x: token_text){
        std::cout << i++ << "  Token"  
        << "token_type:           " << MapFromTokenTypeToString[x->token_type] 
        << "          " << "token_value" << "        " << x->token_value << std::endl;
    }
}
