#ifndef PRECOMPILATION_H
#define PRECOMPILATION_H

#include<vector>
#include<string>
#include<memory>
#include<utility>
struct preCompiler {
    preCompiler(const char* filename) : fileName(filename), output(nullptr) {
        preCompile();
        macroExpansion();
    }
    void preCompile(); 
    void macroExpansion();

    const char*                                         fileName;
    std::vector<std::pair<std::string, std::string>>    defines;
    std::shared_ptr<std::string>                        output;
};

#endif