//
// Created by 29919 on 2023/2/13.
//


#include "CompletedTags.hpp"
#include "Token.hpp"
#include "Tokenizer.hpp"
#include <iostream>
#include <string>


void CompletedTags::addCompletedTag(Token &token1, Token &token2) {

    std::string tagName = token1.tagName();

    completedTagsMap[token1.tagName()].push_back(token1);
    completedTagsMap[token1.tagName()].push_back(token2);
}

void CompletedTags::printCompletedTags() {
    if (!completedTagsMap.empty()) {
        std::cout << "The following is a list of well-formed HTML tags." << std::endl << std::endl;


        for (auto& mapIt : completedTagsMap) {
            std::cout << mapIt.first << " appeared in the following " << mapIt.second.size()/2 << " location" << (mapIt.second.size() > 1 ? "s" : "") << std::endl;

            for (auto it = mapIt.second.begin(); it != mapIt.second.end(); ++it) {
                it->print();
            }
            std::cout << std::endl;
        }

        std::cout<<"\n";
    } else {
        std::cout << " doesn't have any matching tags." << std::endl;
    }
}

void CompletedTags::handleOpenTag(Tokenizer& tokenizer, Token& openTag) {

    // Read the next token from the tokenizer
    Token nextToken = tokenizer.getToken();
    // Check if the next token is a close angle-bracket
    if (nextToken.isCloseStandAloneTag()){
        addCompletedTag(openTag, nextToken);
    }else if (nextToken.isCloseAngleBracket()) {
        // If it is, push the open tag onto the stack
        tagStack.addTag(openTag);

    } else {
        // put the token back so it can be read again
        tokenizer.putBack(nextToken);
        openTag.print();
        std::cout<<" is missing a '>' or '/>'. Will discard it." <<std::endl;
    }
}
void CompletedTags::handleCloseTag(Tokenizer& tokenizer, Token& closeTag) {
    // Check if the top tag on the stack matches the close tag
    Token nextToken = tokenizer.getToken();
    if ( tagStack.empty()) {
        if(nextToken.isCloseAngleBracket()) {
            std::cout << "[" << closeTag.getLineNumber() << ", " << closeTag.getCharPos() << "] " << "</"
                      << closeTag.tagName();
            std::cout << "(with close angle bracket [" << nextToken.getLineNumber() << ", " << nextToken.getCharPos()
                      << "] >)";
            std::cout << " doesn't have a matching open tag. Will discard it.\n";
        } else {
            std::cout << "[" << closeTag.getLineNumber() << ", " << closeTag.getCharPos() << "] " << "</"
                      << closeTag.tagName();
            std::cout <<" is missing a '>' or '/>'. Will discard it.\n";
            tokenizer.putBack(nextToken);
        }
    } else if (nextToken.isCloseAngleBracket()){
            Token topTag = tagStack.top();
            if (topTag.tagName() == closeTag.tagName()) {
            // If it does match, add the completed tag to the list of completed tags
                addCompletedTag(topTag, closeTag);
                tagStack.pop();
            }else {
                std::cout << "[" << closeTag.getLineNumber() << ", " << closeTag.getCharPos() << "] " << "</"
                          << closeTag.tagName();
                std::cout << "(with close angle bracket [" << nextToken.getLineNumber() << ", " << nextToken.getCharPos()
                          << "] >)";
                std::cout << " doesn't have a matching open tag. Will discard it.\n";
        }
    } else {
        std::cout << "[" << closeTag.getLineNumber() << ", " << closeTag.getCharPos() << "] " << "</"
                  << closeTag.tagName();
        std::cout<<" is missing a '>' or '/>'. Will discard it.\n";
        tokenizer.putBack(nextToken);
    }
}
