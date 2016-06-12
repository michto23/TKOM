//
// Created by michto on 31.05.16.
//

#ifndef TKOM_COMPONENT_H
#define TKOM_COMPONENT_H


#include <memory>
#include <vector>
#include "../token/TokenType.h"
#include "HtmlAttribute.hpp"

class Component {
private:
    std::vector<std::shared_ptr<Component>> components;
    std::vector<std::shared_ptr<HtmlAttribute>> attributes;
    std::shared_ptr<Token> text; //komponentem jest tutaj rowniez tekst poemidzy tagami
    std::shared_ptr<Token> startTag; //moze byc zwykly tag, script, void, etc
    bool isText;
public:
    std::vector<std::shared_ptr<Component>> &getComponents() {
        return components;
    }

    void setComponents(std::vector<std::shared_ptr<Component>> &components) {
        Component::components = components;
    }

    std::vector<std::shared_ptr<HtmlAttribute>> &getAttributes() {
        return attributes;
    }

    void setAttributes(std::vector<std::shared_ptr<HtmlAttribute>> &attributes) {
        Component::attributes = attributes;
    }

    std::shared_ptr<Token> getText() {
        return text;
    }

    void setText(std::shared_ptr<Token> text) {
        Component::text = text;
    }

    std::shared_ptr<Token> getStartTag() {
        return startTag;
    }

    void setStartTag(std::shared_ptr<Token> startTag) {
        Component::startTag = startTag;
    }


    bool isIsText()  {
        return isText;
    }

    void setIsText(bool isText) {
        Component::isText = isText;
    }

    bool compareStartAndEndTag(std::shared_ptr<Token> endTag){
        std::string start = startTag.get()->getValue().substr(1);
        std::string end = endTag.get()->getValue().substr(2);
        return start == end;
    }
};


#endif //TKOM_COMPONENT_H
