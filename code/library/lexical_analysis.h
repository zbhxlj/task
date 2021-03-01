#ifndef LEXICALANALYSIS_H
#define LEXICALANALYSIS_H

#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<memory>
#include "preprocess.h"
#include "enum_class.h"


struct Token{

    TokenType                                   token_type = TokenType::Nul;
    std::string                                 token_value;
    int                                         number_of_row = -1;
    int                                         number_of_column = -1; 
};

// LexicalAnalyzer extracts tokens from the given source file and saves the result in itself.
// 
// Example :
//   LexicalAnalyzer lexical_analyzer(preprocesser);
//   lexical_analyzer.LexicalAnalyze();
//   lexical_analyzer.PrintTokenText();
struct LexicalAnalyzer {

    Preprocesser                                preprocesser;

    bool                                        has_error_when_parsing = false;                               
    int                                         current_number_of_row  = 1;                                   
    int                                         current_number_of_column = 0;                                  
    std::vector<std::shared_ptr<Token>>         token_text;                              

    LexicalAnalyzer(const Preprocesser& preprocesser);
    void LexicalAnalyze();     
    void PrintTokenText();  
    void UnknownTokenErrorf(const std::shared_ptr<Token>& token, 
                            const std::string& state, const char* current_position);
};

#endif