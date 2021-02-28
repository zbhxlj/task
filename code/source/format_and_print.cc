#include "../library/format_and_print.h"
#include<iostream>
#include<sstream>

void Formatter::PrintFormattedText(){
    std::stringstream output;
    int i = 0;
    int tabNum = 0;
    PrintNode(tabNum, syntax_analyzer.root, output, i);
    std::cout << output.str() ;
}

void printTab(int tabNum, std::stringstream& output){
    while(tabNum > 0){
        output << '\t';
        tabNum --;
    }
}

void Formatter::PrintAST(){
    printAST(0, syntax_analyzer.root);
}

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

void Formatter::PrintNode(int& tabNum, const std::shared_ptr<SyntaxTreeNode>& root,
                          std::stringstream& output,int &i){
    if(root -> syntax_type == SyntaxUnitType::Terminator){
        switch (root -> token -> token_type) {
            case TokenType::Lp :
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
                output << root->token->token_value <<  std::endl;
                printTab(tabNum, output);
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
            PrintNode(tabNum, son, output, i);
        }
    }
}
