//
// Created by 29919 on 2023/2/13.
//

#ifndef PROJECT1_PHASE2_STUDENT_FILES_COMPLETEDTAGS_HPP
#define PROJECT1_PHASE2_STUDENT_FILES_COMPLETEDTAGS_HPP

#include<iostream>
#include<map>
#include<vector>

#include "Token.hpp"
#include "Tokenizer.hpp"
#include "OpenTagStack.hpp"

class CompletedTags {
public:

    // addCompletedTag takes two arguments
    //     -- an open tag and its corresponding close tag
    //  or
    //     -- an open tag and a stand-alon close tag

    // In either case, if the map doesn't have an entry for the tag-name,
    // you add a vector to the map using the tag name and add the two tokens
    // to the vector.
    // On the other hand, if the tag-name already exists in the map, you just add the two
    // token to its vector.
    void addCompletedTag(Token &token1, Token &token2);

    void handleOpenTag(Tokenizer& tokenizer, Token& openTag);
    void handleCloseTag(Tokenizer& tokenizer, Token& closeTag);

    // The error messages get printed in the main function.
    // This function prints each completed tag and the locations
    // where the tag has been found in the input.
    void printCompletedTags();

private:
    std::map<std::string, std::vector<Token> > completedTagsMap;
    OpenTagStack tagStack;
};


#endif //PROJECT1_PHASE2_STUDENT_FILES_COMPLETEDTAGS_HPP
