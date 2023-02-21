//
// Created by Ali Kooshesh on 1/22/23.
//

#include <iostream>
#include <iomanip>
#include "Token.hpp"

Token::Token(int line, int pos): _isOpenTag{false},
                                 _isCloseTag{false},
                                 _isCloseAngleBracket{false},
                                 _isOpenAngleBracket{false},
                                 _isCloseStandAloneTag{false},

                                 _tagName{""},
                                 _lineNumber{line},
                                 _charPos{pos} {}

bool &Token::isOpenTag() { return _isOpenTag; }
bool &Token::isCloseTag() { return _isCloseTag; }



bool &Token::isCloseAngleBracket() { return _isCloseAngleBracket; }
bool &Token::isOpenAngleBracket() {return _isOpenAngleBracket;}

bool &Token::endOfFile() { return _eof; }
bool &Token::isCloseStandAloneTag() { return _isCloseStandAloneTag; }

std::string Token::tagName() { return _tagName; }
int Token::getLineNumber() {return _lineNumber; }
int Token::getCharPos() {return _charPos;}


void Token::makeOpenTag(std::string name) {
    _tagName = name;
    isOpenTag() = true;
}

void Token::makeCloseTag(std::string name) {
    _tagName = name;
    isCloseTag() = true;
}

//modified print() function because we don't want location to be printed for all tokens
void Token::print() {

    if (isOpenTag()) {
        std::cout << "[" << std::setw(2) << _lineNumber << ", " << std::setw(3) << _charPos << "] ";
        std::cout << "<" << tagName();
    } else if (isCloseTag()) {
        std::cout << " -- [" << std::setw(2) << _lineNumber << ", " << std::setw(3) << _charPos << "] ";
        std::cout << "</" << tagName()<< "\n";
    } else if (isCloseAngleBracket()) {
        std::cout << "[" << std::setw(2) << _lineNumber << ", " << std::setw(3) << _charPos << "] ";
        std::cout << ">" <<"\n";
    } else if (isCloseStandAloneTag()) {
        std::cout << " -- [" << std::setw(2) << _lineNumber << ", " << std::setw(3) << _charPos << "] ";
        std::cout << "/>" <<"\n";
    } else if (isOpenAngleBracket()){
        std::cout << "[" << std::setw(2) << _lineNumber << ", " << std::setw(3) << _charPos << "] ";
        std::cout << "<" <<"\n";
    }else {
        std::cout << "Token::print -- unknown token.\n" << std::endl;
        exit(3);
    }
}
