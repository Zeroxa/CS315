//
// Created by 29919 on 2023/2/2.
//

#ifndef PROJECT1_P1_TOKEN_H
#define PROJECT1_P1_TOKEN_H
#include <string>


class Token {
public:
    Token(int, int);
    bool &isOpenTag();
    bool &isCloseTag();

    bool &isCloseAngleBracket();
    bool &isOpenAngleBracket();


    bool &endOfFile();
    bool &isCloseStandAloneTag();


    std::string tagName();
    int getLineNumber();
    int getCharPos();

    void makeOpenTag(std::string);
    void makeCloseTag(std::string);
    void print();

private:
    bool _isOpenTag, _isCloseTag, _isCloseAngleBracket, _isOpenAngleBracket,
            _eof, _isCloseStandAloneTag;

    std::string _tagName;
    int _lineNumber, _charPos;


};


#endif //PROJECT1_P1_TOKEN_H
