#ifndef PREPROCESS_H
#define PREPROCESS_H

#include<vector>
#include<string>
#include<memory>
#include<utility>

// Preprocesser preprocesses (include files、macro expand) the source file and 
// saves the results in itself.
// 
// Example:
//  Preprocesser preprocesser(source_file_name);
//  preprocesser.Preprocess();
//  
struct Preprocesser {

public:
    Preprocesser(const char* _source_file_name) : source_file_name(_source_file_name), output_file_after_preprocess(nullptr) {}

    // Interface exposed to the outside
    void Preprocess(); 

private:
    void IncludeFiles(const std::string& include_file, const std::shared_ptr<std::string>& output_file_after_preprocess);
    void MacroExpand();

    const char*                                         source_file_name;
    std::vector<std::pair<std::string, std::string>>    macro_definitions;

public:
    std::shared_ptr<std::string>                        output_file_after_preprocess;
};

#endif