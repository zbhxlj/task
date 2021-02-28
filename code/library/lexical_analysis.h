#ifndef LEXICALANALYSIS_H
#define LEXICALANALYSIS_H

#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<memory>
#include "preprocess.h"
#include "enum_class.h"

struct LexicalAnalyzer;                             

struct Token{

    TokenType                                   token_type = TokenType::Nul;
    std::string                                 token_value;
    int                                         number_of_row = -1;
    int                                         number_of_column = -1; 
};

struct LexicalAnalyzer {

    Preprocesser                                preprocesser;

    bool                                        has_error_when_parsing = false;                               
    int                                         current_number_of_row  = 1;                                   
    int                                         current_number_of_column = 0;                                  
    std::vector<std::shared_ptr<Token>>         token_text;                              

    LexicalAnalyzer(const Preprocesser& preprocesser);
    void LexicalAnalyze();     
    void PrintTokenText();  
};

#endif