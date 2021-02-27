#include "../library/preCompilation.h"
#include <string>
#include <memory>
#include<iostream>
void preCompiler::preCompile(){

    FILE* fp = fopen(fileName, "r");

    if(fp == nullptr){
        std::cerr << "Open failed or Path error of the given file!" << std::endl;
        exit(-1);
    }

    char ch;
    std::string input;
    while((ch = fgetc(fp)) != EOF) input += ch;

    const char* reading = input.c_str();

    const char* head = nullptr, *tail = nullptr;
    std::shared_ptr<std::string> ret(new std::string);

    while(*reading){
        if(*reading == '#'){
            tail = head = ++reading;
            while(*tail != '\"' && *tail != ' ') tail++;
            std::string keyWord(head, tail - head);

            if(keyWord == "include"){
                while(*tail == ' ' || *tail == '\"') tail++;
                head = tail;
                while(*tail != '\"') tail++;
                std::string includeFile(head, tail - head);


                FILE* includeFilePtr = fopen(includeFile.c_str(),  "r");

                if(includeFilePtr == nullptr){
                    std::cerr << "Open failed or Path error when including files !" << std::endl;
                    exit(-1);
                }

                char ch;
                while((ch = fgetc(includeFilePtr)) != EOF) *ret += ch;

                reading = tail + 1;

            }else if(keyWord == "define"){
                while(*tail == ' ') tail++;
                head = tail;
                while(*tail != ' ') tail++;
                std::string macroDefination(head, tail - head);

                while(*tail == ' ') tail++;
                head = tail;
                while(*tail != '\n') tail++;
                std::string expression(head, tail - head);

                defines.push_back(std::make_pair(macroDefination, expression));
                std::cout << "first " << macroDefination << "  second "  << expression << std::endl;
                reading = tail;
            }
            }else {
                *ret += *reading;
                reading++;
            }
        }
    output = ret;
    // std::cout << "before replace" << *output << std::endl;
}


void preCompiler::macroExpansion(){
    bool found = false;
    // std::cout << *output << std::endl;
    // for(int i = 0; i < output->size(); i++){
    //     std::cout << i << "  " << (*output)[i] << std::endl;
    // }
    do
    {   
        found = false;
        for(const auto& p : defines){
            auto pos = output->find(p.first);
            if(pos != std::string::npos){
                found = true;
                // std::cout << "pos : "<< pos << std::endl;
                // std::cout << "p.first  " << p.first << std::endl;
                // std::cout << "output->substr(0, pos) "  << output->substr(0, pos)  << std::endl
                //           << "p.second  "  << p.second  << std::endl
                //           << "output->substr(pos + p.first.size())  " 
                //           <<  output->substr(pos + p.first.size()) << std::endl;
                *output = output->substr(0, pos) 
                        + p.second 
                        + output->substr(pos + p.first.size());
                // std::cout << "output   " << *output << std::endl;
            }
        }
    } while (found == true);
    // std::cout << "after replace : " <<  *output << std::endl;
    // std::cout << "size" << output->size() << std::endl;
}