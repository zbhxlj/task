#include "../library/lexical_analysis.h"
#include<iostream>
#include<cstdio>
#include<iomanip>

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
 * @output token_text
 */

void LexicalAnalyzer::LexicalAnalyze(){

    const char* current_position = preprocesser.output_file_after_preprocess->c_str();
    State state = State::Begin;
    std::shared_ptr<Token> current_token(nullptr);

    while(*current_position){
        current_number_of_column++;
        switch (state)
        {
        case State::Begin:
        {
            current_token.reset(new Token());
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
                current_token->token_type = TokenType::Identifier;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                state = State::InIdentifier;
                break;

            case '1' ... '9' :
                current_token->token_type = TokenType::Int_C;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                state = State:: InInt;
                break;

            case '=' :
                current_token->token_type = TokenType::Assign;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                state = State::InAssign;
                break;
            case '<' :
                current_token->token_type = TokenType::Ls;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                state = State::InLess;
                break;
            case '>' :
                current_token->token_type = TokenType::Gt;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                state = State::InGtr;
                break;
            case '!' :
                current_token->token_type = TokenType::NtEq;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                state = State::InNotEq;
                break;
            
            case '0' :
                current_token->token_type = TokenType::Int_C;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                state = State::In0Prefix;
                break;
            
            case '+' :
                current_token->token_type = TokenType::Pl;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            case '-' :
                current_token->token_type = TokenType::Minus;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            case '*' :
                current_token->token_type = TokenType::Multi;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            case '/' :
                current_token->token_type = TokenType::Divid;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            
            case '(' :
                current_token->token_type = TokenType::OpenBracket;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            case ')' :
                current_token->token_type = TokenType::CloseBracket;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            case '[' :
                current_token->token_type = TokenType::LeftArray;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            case ']' :
                current_token->token_type = TokenType::RightArray;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            case '{' :
                current_token->token_type = TokenType::Lp;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            case '}' :
                current_token->token_type = TokenType::Rp;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            
            case ',' :
                current_token->token_type = TokenType::Comma;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            case ';' :
                current_token->token_type = TokenType::Semi;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            case '\'' :
                current_token->token_type = TokenType::Char_C;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                state = State::InSingleQuota;
                break;
            case '\"' : 
                current_token->token_type = TokenType::String;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                state = State::InDoubleQuota;
                break;

            case '#' :
                current_token->token_type = TokenType::Sharp;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                token_text.push_back(current_token);
                state = State::Begin;
                break;

            case '&' :
                current_token->token_type = TokenType::And;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                state = State::InAnd;
                break;
            case '|' :
                current_token->token_type = TokenType::Or;
                current_token->token_value += *current_position;
                current_token->number_of_row = current_number_of_row;
                current_token->number_of_column = current_number_of_column;
                state = State::InOr;
                break;
            
            case '$' :
                current_token->token_type = TokenType::End;
                current_token->token_value += *current_position;
                current_token->number_of_column = current_number_of_column;
                current_token->number_of_row = current_number_of_row;
                token_text.push_back(current_token);
                state = State::Begin;
                break;

            default:
                UnknownTokenErrorf(current_token, "Begin", current_position);
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
                current_token->token_value += *current_position;
                break;
            
            default:
                current_position--;
                if(MapFromKeyWordToTokenType.count(current_token->token_value) > 0){
                    current_token->token_type = MapFromKeyWordToTokenType[current_token -> token_value];
                } 
                else current_token->token_type = TokenType::Identifier;
                token_text.push_back(current_token);
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
                current_token->token_value += *current_position;
                break;
            
            case '.' :
                current_token->token_type = TokenType::Float_C;
                current_token->token_value += *current_position;
                state = State::InFloat;
                break;

            case 'L' :
            case 'l' :
                current_token->token_value += *current_position;
                current_token->token_type = TokenType::Long_C;
                token_text.push_back(current_token);
                state = State::Begin;
                break;

            default:
                current_position--;
                token_text.push_back(current_token);
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
                current_token->token_value += *current_position;
                break;
            
            default:
                current_position--;
                token_text.push_back(current_token);
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
                current_token->token_type = TokenType::Eq;
                current_token->token_value += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            
            default:
                current_position--;
                token_text.push_back(current_token);
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
                current_token->token_type = TokenType::LsEq;
                current_token->token_value += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            
            default:
                current_position--;
                token_text.push_back(current_token);
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
                current_token->token_type = TokenType::GtEq;
                current_token->token_value += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            
            default:
                current_position--;
                token_text.push_back(current_token);
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
                current_token->token_value += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            
            default:
                UnknownTokenErrorf(current_token, "InNotEq", current_position);
                // std::cerr << "Unexpected character int State::InNotEq !" << std::endl;
                // has_error_when_parsing = true;
                // curToken->token_type = TokenType::Error;
                // current_position--;
                break;
            }
            break;
        }

        case State::In0Prefix :
        {
            switch (*current_position)
            {
            case '0' ... '7':
                current_token->token_type = TokenType::Int_C;
                current_token->token_value += *current_position;
                state = State::In0Int;
                break;
            
            case 'x' :
            case 'X' :
                current_token->token_type = TokenType::Int_C;
                current_token->token_value += *current_position;
                state = State::In0xPrefix;
                break;
            
            case '8' ... '9' :
                current_token->token_type = TokenType::Error;
                current_token->token_value += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;

            default:
                current_token->token_type = TokenType::Int_C;
                current_position--;
                token_text.push_back(current_token);
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
                current_token->token_value += *current_position;
                break;
            case 'l' :
            case 'L' :
                current_token->token_value += *current_position;
                current_token->token_type = TokenType::Long_C;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            default:
                current_position--;
                token_text.push_back(current_token);
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
                current_token->token_value += *current_position;
                state = State::In0xInt;
                break;
            
            default:
                UnknownTokenErrorf(current_token, "In0Prefix", current_position);
                // std::cerr << "Unexpected character in State::In0xPrefix!" << std::endl;
                // has_error_when_parsing = true;
                // curToken->token_type = TokenType::Error;
                // current_position--;
                // token_text.push_back(curToken);
                // state = State::Begin;
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
                current_token->token_value += *current_position;
                break;
            case 'l' :
            case 'L' : 
                current_token->token_value += *current_position;
                current_token->token_type = TokenType::Long_C;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            default:
                current_position--;
                token_text.push_back(current_token);
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
                current_token ->token_value += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            
            default:
                current_token -> token_value += *current_position;
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
                current_token ->token_value += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;

            
            default:
                current_token -> token_value += *current_position;
                break;
            }
            break;
        }

        case State::InAnd :
        {
            switch (*current_position)
            {
            case '&' :
                current_token->token_value += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            default:
                UnknownTokenErrorf(current_token, "InAnd", current_position);
                // std::cerr << "Unexpected character in State::InAnd!" << std::endl;
                // has_error_when_parsing = true;
                // current_token->token_type = TokenType::Error;
                // token_text.push_back(current_token);
                // state = State::Begin;
                break;
            }
            break;
        }

        case State::InOr :
        {
            switch (*current_position)
            {
            case '|' :
                current_token->token_value += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            default:
                UnknownTokenErrorf(current_token, "InOr", current_position);
                // std::cerr << "Unexpected character in State::InOr!" << std::endl;
                // has_error_when_parsing = true;
                // current_token->token_type = TokenType::Error;
                // token_text.push_back(current_token);
                // state = State::Begin;
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
                current_token -> token_type = TokenType::Error;
                has_error_when_parsing = true;
                current_token -> token_value  += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            
            default:
                current_token -> token_value += *current_position;
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
                current_token -> token_value  += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            
            default:
                // UnknownTokenErrorf(current_token, "InChar", current_position);
                std::cerr << "There is more than one character!" 
                << "In row " << current_number_of_row 
                << " In column  "  << current_number_of_column 
                << std::endl;
                exit(-1);
                current_token -> token_type = TokenType::Error;
                has_error_when_parsing = true;
                while(*current_position != '\''){
                    current_token -> token_value  += *current_position;
                    current_position++;
                }
                current_token -> token_value  += *current_position;
                token_text.push_back(current_token);
                state = State::Begin;
                break;
            }
            break;
        }

        default:
            std::cerr << "Unexpected case !" << std::endl;
            exit(-1);
            break;
        }
        current_position++;
    }
}

void LexicalAnalyzer::PrintTokenText(){
    int i = 0;
     for(const auto& x: token_text){
        std::cout << std::setiosflags(std::ios::left)
        << std::setw(4)
        << i++  << " Token  " 
        << std::setw(20)
        << " token_type: " << std::setw(20) 
        << MapFromTokenTypeToString[x->token_type] 
        << std::setw(20) << "token_value " << std::setw(10) << x->token_value << std::endl;
    }
}

// User_friendly error_handle helper function.
void LexicalAnalyzer::UnknownTokenErrorf(const std::shared_ptr<Token>& current_token,  
                    const std::string& state, const char* current_position){
                std::cerr << "character : " << *current_position << std::endl;
                std::cerr << "Error: Unexpected Character in state::" << state << "!" << std::endl;
                std::cerr << "In row " << current_number_of_row << "  In  column  " << current_number_of_column << std::endl;
                has_error_when_parsing = true;
                // current_token->token_type = TokenType::Error;
                // current_token->token_value += *current_position;
                // current_token->number_of_row = current_number_of_row;
                // current_token->number_of_column = current_number_of_column;
                // token_text.push_back(current_token);
                // state = State::Begin;
                exit(-1);
}