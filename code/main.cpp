#include<fstream>
#include<sstream>
#include<string>
#include "lex.h"
using std::ifstream;
using std::stringstream;
using std::string;

int main(int argc, char* argv[]){
    ifstream codeFile;
    codeFile.open(argv[1]);

    stringstream codeStream;
    codeStream << codeFile.rdbuf();

    string codeString;
    codeStream >> codeString;

    const char* reading = codeString.c_str(); 
    int err = lex(reading);
    return 0;
}