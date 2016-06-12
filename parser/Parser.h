//
// Created by michto on 30.05.16.
//

#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H

#include <memory>
#include "../token/Token.hpp"
#include "../treeObjects/HtmlDocument.h"

class Parser {
private:
    std::queue<std::shared_ptr<Token>>* tokens;
    std::shared_ptr<Token> currentToken;
    long posCurrToken = 0;
    std::shared_ptr<Token> nextToken(bool);
public:
    std::shared_ptr<HtmlDocument> buildHtmlDocumentTree();
    std::shared_ptr<HtmlAttribute> buildHtmlAttribute();
    std::shared_ptr<Component> buildComponent();
    std::vector<std::shared_ptr<Component>> findComponentsInDocument(std::shared_ptr<HtmlDocument> document, Token startTag);

    Parser(std::queue<std::shared_ptr<Token>> *tokens) : tokens(tokens) { }
};



#endif //TKOM_PARSER_H
