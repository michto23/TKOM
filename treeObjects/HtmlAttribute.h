//
// Created by michto on 31.05.16.
//

#ifndef TKOM_ATTRIBUTE_H
#define TKOM_ATTRIBUTE_H

#include <iostream>
#include "../TokenType.h"

class HtmlAttribute {
private:
    std::shared_ptr<Token> attributeName;
    std::shared_ptr<Token> attributeValue;
public:

    std::shared_ptr<Token> getAttributeValue() {
        return attributeValue;
    }

    void setAttributeValue(std::shared_ptr<Token> attributeValue) {
        HtmlAttribute::attributeValue = attributeValue;
    }

    std::shared_ptr<Token> getAttributeName() {
        return attributeName;
    }

    void setAttributeName(std::shared_ptr<Token> attributeName) {
        HtmlAttribute::attributeName = attributeName;
    }

    void print() {
        std::cout << "****"<< std::endl;
        if(attributeName.get() != NULL){
            std::cout << "AttrNameEnum - " << getTokenName(attributeName.get()->getTokenType()) << std::endl;
            std::cout << "AttrNameValue - " << attributeName.get()->getValue() << std::endl << std::endl;
        }
        if(attributeValue.get() != NULL){
            std::cout << "AttrValueEnum - " << getTokenName(attributeValue.get()->getTokenType()) << std::endl;
            std::cout << "AttrValueValue - " << attributeValue.get()->getValue() << std::endl << std::endl;
        }
        std::cout << "****"<< std::endl;
    };
};


#endif //TKOM_ATTRIBUTE_H
