#include "../library/formatter.h"
#include<iostream>
#include<sstream>

void formatter::print(){
    std::stringstream output;
    int i = 0;
    int tabNum = 0;
    printNode(tabNum, parser.root, output, i);
    std::cout << output.str() ;
}

void printTab(int tabNum, std::stringstream& output){
    while(tabNum > 0){
        output << '\t';
        tabNum --;
    }
}

void formatter::printAST(int depth, const std::shared_ptr<SyntaxTreeNode>& root){
    for(int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << "SyntaxUnitType : " << parser.mapFromEnumClassToString[root->syntaxType]  << std::endl;
    if(root -> curToken.get() != nullptr){
        for(int i = 0; i < depth; i++) std::cout << "  ";
        std::cout << "tokenType : " 
        << parser.tokenparser.mapFromEnumClassToString[root->curToken->type]
        << std::endl;

        for(int i = 0; i < depth; i++) std::cout << "  ";
        std::cout << "value : " << root->curToken->value << std::endl; 
    }
    std::cout << std::endl;

    for(const auto& son : root -> childs){
        printAST(depth + 1, son);
    }
    return;
}

void formatter::printNode(int& tabNum, const std::shared_ptr<SyntaxTreeNode>& root,
                          std::stringstream& output,int &i){
    if(root -> syntaxType == SyntaxUnitType::Terminator){
        switch (root -> curToken -> type) {
            case tokenType::Lp :
                tabNum++;
                output << root->curToken->value << std::endl;
                printTab(tabNum, output);
                break;
            
            case tokenType::Rp :
                {
                    tabNum--;
                    std::string tmp = output.str();
                    // std::cout << "tmp " << std::endl << tmp;
                    tmp.pop_back();
                    std::stringstream toswap;
                    toswap << tmp;
                    output.swap(toswap);
                    // std::cout << "output " << std::endl << output.str() << std::endl;
                    output << root->curToken->value << std::endl;
                    printTab(tabNum, output);
                    break;
                }

            case tokenType::Semi :
                output << root->curToken->value <<  std::endl;
                printTab(tabNum, output);
                break;

            case tokenType::Quota :
            case tokenType::SingleQuota :
                output << root->curToken->value;
                break;
            
            default :
                output << root->curToken->value << " ";
                break;
        }
    }else {
        for(const auto& son : root -> childs){
            printNode(tabNum, son, output, i);
        }
    }
}
