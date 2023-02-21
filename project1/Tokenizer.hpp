//
// Created by Ali Kooshesh on 1/22/23.
//

#ifndef PROJECT1_PHASE1_TOKENIZER_HPP
#define PROJECT1_PHASE1_TOKENIZER_HPP


#include <string>
#include <fstream>
#include "Token.hpp"

class Tokenizer {

public:
    Tokenizer(std::string);
    Token getToken();
    void putBack(Token token);

private:
    int lineNumber, charPosition;
    std::string inputFileName;
    std::ifstream inputStream;

    bool charOfInterest(char c);
    bool outstandingToken;
    Token putbackToken;
};


#endif //PROJECT1_PHASE1_TOKENIZER_HPP
