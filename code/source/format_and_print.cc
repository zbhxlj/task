#include "../library/format_and_print.h"
#include<iostream>
#include<sstream>

//API exposed to the user.
void Formatter::PrintFormattedText(){
    std::stringstream output;
    int i = 0;
    int tabNum = 0;
    bool need_new_line = false;
    int depth = 0;
    bool in_for_range = false;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "-----------------FormattedText--------------------"  << std::endl;
    PrintNode(tabNum, syntax_analyzer.root, output, i, in_for_range);
    std::cout << output.str() ;
    std::cout << "-----------------End--------------------"  << std::endl;
    std::cout << std::endl;

}

// print spaces
void printTab(int tabNum, std::stringstream& output){
    while(tabNum > 0){
        output << "  ";
        tabNum --;
    }
}

// API exposed to the user.
void Formatter::PrintAST(){
    std::cout << std::endl;
    std::cout << "-----------------AST--------------------"  << std::endl;
    printAST(0, syntax_analyzer.root);
    std::cout << "-----------------End--------------------"  << std::endl;
}

// Preorder traverse printing abstract syntax tree.
void Formatter::printAST(int depth, const std::shared_ptr<SyntaxTreeNode>& root){
    for(int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << "SyntaxUnitType : " << MapFromSyntaxUnitTypeToString[root->syntax_type]  << std::endl;
    if(root -> token.get() != nullptr){
        for(int i = 0; i < depth; i++) std::cout << "  ";
        std::cout << "TokenType : " 
        << MapFromTokenTypeToString[root->token->token_type]
        << std::endl;

        for(int i = 0; i < depth; i++) std::cout << "  ";
        std::cout << "token_value : " << root->token->token_value << std::endl; 
    }
    std::cout << std::endl;

    for(const auto& son : root -> childs){
        printAST(depth + 1, son);
    }
    return;
}

// Preorder traverse printing formatted text.
void Formatter::PrintNode(int& tabNum, const std::shared_ptr<SyntaxTreeNode>& root,
                          std::stringstream& output, int &i, 
                          bool& in_for_range){
    if(root -> syntax_type == SyntaxUnitType::Terminator){
        switch (root -> token -> token_type) { 

            case TokenType::For :
                in_for_range = true;
                output << root->token->token_value << " ";
                break;

            case TokenType::Lp :
                if(in_for_range) in_for_range = false;
                tabNum++;
                output << root->token->token_value << std::endl;
                printTab(tabNum, output);
                break;
            
            // I cannot  figure out why the following solution is wrong.
            // Wrong solution :
            // 
            // tabNum--;
            // std::string tmp = output.str();
            // tmp.pop_back();
            // output.str(tmp);
            // output << root -> token ->token_value << std::endl;
            // printTab(tabNum, output);
            // break;
            // 

            case TokenType::Rp :
                {
                    tabNum--;
                    std::string tmp = output.str();
                    tmp.pop_back();
                    std::stringstream to_swap;
                    to_swap << tmp;
                    output.swap(to_swap);
                    output << root->token->token_value << std::endl;
                    printTab(tabNum, output);
                    break;
                }

            case TokenType::Semi :
                if(in_for_range){
                    output << root->token->token_value;
                }else {
                    output << root->token->token_value << std::endl;
                    printTab(tabNum, output);
                }
                break;

            case TokenType::Quota :
            case TokenType::SingleQuota :
                output << root->token->token_value;
                break;
            
            default :
                output << root->token->token_value << " ";
                break;
        }
    }else {
        for(const auto& son : root -> childs){
            PrintNode(tabNum, son, output, i, in_for_range);
        }
    }
}
