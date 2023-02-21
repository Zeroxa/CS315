//
// Created by 29919 on 2023/2/13.
//

#include "OpenTagStack.hpp"
#include "Token.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include<map>




void OpenTagStack::addTag(const Token &token) {
    stack.push_back(token);
}

bool OpenTagStack::empty(){
    return stack.empty();
}

Token OpenTagStack::top(){
    if (!stack.empty()) {
        return stack.back();
    } else {
        std::cerr << "Error: vector is empty" << std::endl;
        std::exit(1);
    }
}

Token OpenTagStack::pop(){
    if (!stack.empty()) {
        Token temp = stack.back();
        stack.pop_back();
        return temp;
    } else {
        std::cerr << "Error: vector is empty" << std::endl;
        std::exit(1);
    }
}

void OpenTagStack::removeElementWithTagName(std::string tagName){
    for (auto iterate = stack.rbegin(); iterate != stack.rend(); ++iterate) {
        if (iterate->tagName() == tagName) {
            stack.erase(std::next(iterate).base());
            return;
        }
    }
}

void OpenTagStack::printStack() {
    std::cout << "Current stack: ";
    for (auto& token : stack) {
        std::cout << token.tagName() << " ";
    }
    std::cout << std::endl;
}






