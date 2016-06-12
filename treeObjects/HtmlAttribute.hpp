//
// Created by michto on 31.05.16.
//

#ifndef TKOM_ATTRIBUTE_H
#define TKOM_ATTRIBUTE_H

#include <iostream>
#include "../token/TokenType.h"

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
};


#endif //TKOM_ATTRIBUTE_H
