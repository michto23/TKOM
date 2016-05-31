//
// Created by michto on 31.05.16.
//

#ifndef TKOM_COMPONENT_H
#define TKOM_COMPONENT_H


#include <memory>
#include <vector>
#include "../TokenType.h"
#include "HtmlAttribute.h"

class Component {
private:
    std::vector<std::shared_ptr<Component>> components;
    std::vector<std::shared_ptr<HtmlAttribute>> attributes;
    TokenType text; //komponentem jest tutaj rowniez tekst poemidzy tagami
    TokenType startTag; //moze byc zwykly tag, script, void, etc


};


#endif //TKOM_COMPONENT_H
