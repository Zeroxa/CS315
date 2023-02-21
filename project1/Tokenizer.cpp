//
// Created by Ali Kooshesh on 1/22/23.
// Modified by Hanpei Zhang for project 1 phase 1

#include <iostream>
#include <string>
#include "Tokenizer.hpp"
#include "Token.hpp"

Tokenizer::Tokenizer(std::string name): lineNumber{1},
                                        charPosition{1},
                                        inputFileName{name},
                                        putbackToken{0,0},
                                        outstandingToken{false}
                                        {
    inputStream.open(inputFileName, std::ios::in);  // open the input file. We will make sure that it is open in getToken.
}

bool Tokenizer::charOfInterest(char c) {
    // is c the initial (or the sole) character of a token?

    return c == '<' || c == '>' || c == '/' && inputStream.peek() == '>' ;   // compares c with characters like '<', '>', etc.
}

void Tokenizer::putBack(Token token){
    outstandingToken = true;
    putbackToken = token;

}

Token Tokenizer::getToken() {
    char c;

    if( ! inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }

    if(outstandingToken) {
        outstandingToken = false;
        return putbackToken;
    }

    while( inputStream.get(c) && ! charOfInterest(c) ) {
        charPosition++;
        if (c == '\n') {
            lineNumber++;
        }
        // keep track of the line number and the character position
    }

    // The above loop stops because one of its conditions is false. That means
    // either function get failed, which happens at the end of the file, or
    // c, the character that get read, is a character of interest. The other
    // possibility is if the input file was not open or the input somehow got clobbered.


    Token token(lineNumber, charPosition);
    if( inputStream.eof() ) {
        token.endOfFile() = true;
        return token;
    }




    //if we found a character of interest, and it's '<'
    if( c == '<' ) {
        //there are three situations it followed by a name, a / and other characters
        if(std::isalnum(inputStream.peek())){
            charPosition++;
            std::string name;
            while(std::isalnum(inputStream.peek())){

                name += inputStream.get();
                charPosition++;

            }
            token.makeOpenTag(name);
            return token;
        } else if (inputStream.peek() == '/'){
            charPosition+=2;
            inputStream.get();
            std::string name;

            while(std::isalnum(inputStream.peek())){

                name += inputStream.get();
                charPosition++;
            }

            token.makeCloseTag(name);
            return token;
        } else if (!std::isalnum(inputStream.peek())){

            charPosition++;
            token.isOpenAngleBracket() = true;
            return token;

        }

    } else if( c == '>' ) {
        charPosition++;
        token.isCloseAngleBracket() = true;
        return token;

    } else if( c == '/'  && inputStream.peek() == '>'){
        charPosition+=2;
        token.isCloseStandAloneTag() = true;
        c=inputStream.get();
        return token;



    }else {
        // The condition of one of the above "if ... else if" statements should
        // evaluate to true because function charOfInterest return true when it
        // finds a character that is the start of some token and that the
        // "if ... else if" has one case for each character that starts a token.
        // Therefore, the control should never get here. However, it is always
        // a good idea to have an "else" when you have a sequence of "if ... else if"
        // statements so that you do not end up with a case that has not been handled.
        // For example, you forgot to account for one of the cases.
        std::cout << "There is a logic error in unction Tokenizer::getToken.\n";
        std::cout << "The function doesn't know how to process this character: ->" << c << "<-\n";
        exit(1);
    }
    return token; // The control SHOULD NOT reach this statement.
}
