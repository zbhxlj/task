#include "../library/preprocess.h"
#include <string>
#include <memory>
#include<iostream>

// Preprocess() checks the source file character by character and extracts the 
// to_be_included files and macro_definitions, passing them to IncludeFiles() and 
// MacroExpand() respectively.
void Preprocesser::Preprocess(){

    auto file_closer = [] (std::FILE* file_pointer) {
        std::fclose(file_pointer);
    };

    std::unique_ptr<std::FILE, decltype(file_closer)> 
                        sourcefile_ptr(fopen(source_file_name, "r"), file_closer);

    if(sourcefile_ptr == nullptr){
        std::cerr << "Failed when opening the source file!  "
                  << "Probably Path error! " 
                  << "Please provide relative path." << std::endl;
        exit(-1);
    }

    char ch;
    std::string source_file_string;
    while((ch = fgetc(sourcefile_ptr.get())) != EOF) source_file_string += ch;

    const char* current_position = source_file_string.c_str();

    const char* string_begin = nullptr, *string_end = nullptr;

    output_file_after_preprocess = std::shared_ptr<std::string>(new std::string);

    while(*current_position){
        if(*current_position == '#'){

            string_end = string_begin = ++current_position;
            while(*string_end != '\"' && *string_end != ' ') string_end++;
            std::string keyword(string_begin, string_end - string_begin);

            if(keyword == "include"){
                while(*string_end == ' ' || *string_end == '\"') string_end++;
                string_begin = string_end;
                while(*string_end != '\"') string_end++;
                std::string include_file(string_begin, string_end - string_begin);

                IncludeFiles(include_file, output_file_after_preprocess);

                current_position = string_end + 1;

            }else if(keyword == "define"){
                while(*string_end == ' ') string_end++;
                string_begin = string_end;
                while(*string_end != ' ') string_end++;
                std::string macro_source(string_begin, string_end - string_begin);

                while(*string_end == ' ') string_end++;
                string_begin = string_end;
                while(*string_end != '\n') string_end++;
                std::string macro_target(string_begin, string_end - string_begin);
                macro_definitions.push_back(std::make_pair(macro_source, macro_target));

                current_position = string_end;
            }
            }else if(*current_position == '/' && *(current_position + 1) == '/'){
                while(*current_position != '\n') current_position++;
                *output_file_after_preprocess += *current_position;
                current_position++;
            }
            else {
                *output_file_after_preprocess += *current_position;
                current_position++;
            }
        }
    MacroExpand();
    *output_file_after_preprocess += '$';
}

void Preprocesser::IncludeFiles(const std::string& include_file, const std::shared_ptr<std::string>& output_file_after_preprocess){
    auto file_closer = [] (std::FILE* file_pointer) {
        std::fclose(file_pointer);
    };

    std::unique_ptr<std::FILE, decltype(file_closer)> 
                        include_file_ptr(fopen(include_file.c_str(), "r"), file_closer);


    if(include_file_ptr == nullptr){
        std::cerr << "Failed when opening the include files! "
        << "Probably path error! " 
        << "Please provide relative path! "<< std::endl;
        exit(-1);
    }

    char ch;
    while((ch = fgetc(include_file_ptr.get())) != EOF) *output_file_after_preprocess += ch;
}


void Preprocesser::MacroExpand(){
    bool found = false;
    do
    {   
        found = false;
        for(const auto& p : macro_definitions){
            auto pos = output_file_after_preprocess->find(p.first);
            if(pos != std::string::npos){
                found = true;
                *output_file_after_preprocess = output_file_after_preprocess->substr(0, pos) 
                        + p.second 
                        + output_file_after_preprocess->substr(pos + p.first.size());
            }
        }
    } while (found == true);
}