#include <iostream>
#include <fstream>
#include "Tokenizer.hpp"
#include "OpenTagStack.hpp"
#include "CompletedTags.hpp"
#include <string.h>


int main(int argc, char *argv[]) {

    if( argc != 2 ) {  // we expect the name of the file as an argument to the program.
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile" << std::endl;
        exit(1);
    }

    // Here, we open the file to make sure that it exists before starting the program.
    // When using CLion, the input file has to be in cmake-build-debug directory.
    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);    // open for reading
    if( ! inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        std::cout << strerror(errno) << std::endl;
        exit(2);
    }

    // We now know that the input file exists and we can read from it. Here, we will close it
    // and give Tokenizer the name of the file so it can open and use it. We also could give
    // Tokenizer 'inputStream' so that it just uses it.
    inputStream.close();

    Tokenizer tokenizer(argv[1]);   // use the first argument, which contains the name of the input file
    // to create an instance of Tokenizer.
    Token token = tokenizer.getToken();  // get the first token.

    CompletedTags completedTags;
    OpenTagStack openTagStack;

  while (!token.endOfFile()) {
        if (token.isOpenTag())
            completedTags.handleOpenTag(tokenizer, token); // this function will have to get a new token. It might not use it though.
        else if (token.isCloseTag())
            completedTags.handleCloseTag(tokenizer, token);
        else if(token.isCloseAngleBracket() || token.isOpenAngleBracket()) {
            std::cout<<"["<< token.getLineNumber()<<", "<<token.getCharPos()<<"]";
            std::cout << (token.isCloseAngleBracket() ? " > ignoring random close angle-bracket."
                                                    : " < ignoring random open angle-bracket.") << std::endl;
        } else {
            token.print();
            std::cout << "unknown token."  << std::endl;
            exit(1);
        }
        token = tokenizer.getToken();
   }

    completedTags.printCompletedTags();

/*
    while(!token.endOfFile()){
        token.print();
        token = tokenizer.getToken();
    }*/
    return 0;
}
