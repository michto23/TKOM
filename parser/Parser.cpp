//
// Created by michto on 30.05.16.
//

#include <queue>
#include "Parser.h"
#include "../treeObjects/HtmlDocument.h"
#include "../token/Token.hpp"

/*
 *  _Classes - the way to mark Token Enums - terminate symbols
 *
 * HtmlDocument := Doctype Component*
 * Doctype := _StartTagDoctype {Attribute}* _EndTag
 * Component := _StartTag {Attribute}* _EndTag {Component}* _StartOnEndTag _EndTag
 * Component := _ScriptStart _Text _ScriptEnd
 * Component := _StartTag {Attribute}* _EndOnStartTag
 * Component := _Text
 * Component := _StartTagVoid {Attribute}* _EndTag
 * Attribute := _Attribute _AttributeValueStartEqualsQuote _AttributeValue _AtrributeValueEndQuote
 * Attribute := _Attribute _AttributeValueStartEqualsQuotes _AttributeValue _AtrributeValueEndQuotes
 * Attribute := _AttributeNoValue
 */

std::shared_ptr<HtmlDocument> Parser::buildHtmlDocumentTree(){
    std::shared_ptr<HtmlDocument> htmlDocument(new HtmlDocument);
    currentToken = Parser::nextToken(false);
    if(currentToken == NULL)
        return NULL;
    if(currentToken.get()->getTokenType() == StartTagDoctype){
        std::shared_ptr<Doctype> doctype(new Doctype);
        currentToken = Parser::nextToken(false);
        while (currentToken.get()->getTokenType() == AttributeNoValue || currentToken.get()->getTokenType() == Attribute) {
            doctype.get()->getAttributes().push_back(buildHtmlAttribute());
            currentToken = Parser::nextToken(false);
        }
        if (currentToken.get()->getTokenType() == EndTag){
//            doctype.get()->print();
            htmlDocument.get()->setDoctype(doctype);
            currentToken = Parser::nextToken(true);
            while (currentToken.get() != NULL && (currentToken.get()->getTokenType() == StartTag || currentToken.get()->getTokenType() == StartTagVoid || currentToken.get()->getTokenType() == ScriptStart || currentToken.get()->getTokenType() == Text)){
                htmlDocument.get()->getComponents().push_back(buildComponent());
                currentToken = Parser::nextToken(true);
            }
            return htmlDocument;
        }
    }

    std::cout<< "ERROR PARSOWANIA " << currentToken.get()->getValue() <<" ** " << posCurrToken << std::endl;
    exit(posCurrToken);
}

std::shared_ptr<HtmlAttribute> Parser::buildHtmlAttribute(){
    std::shared_ptr<HtmlAttribute> retAtrribute(new HtmlAttribute);
    retAtrribute.get()->setAttributeName(currentToken);
    if(currentToken.get()->getTokenType() == AttributeNoValue){
        return retAtrribute;
    }
    else if(currentToken.get()->getTokenType() == Attribute){
        currentToken = Parser::nextToken(false);
        if (currentToken.get()->getTokenType() == AttributeValueStartEqualsQuote){
            currentToken = Parser::nextToken(false);
            if(currentToken.get()->getTokenType() == AttributeValue){
                retAtrribute.get()->setAttributeValue(currentToken);
                currentToken = Parser::nextToken(false);
                if(currentToken.get()->getTokenType() == AtrributeValueEndQuote){
                    return retAtrribute;
                }
            }
        }
        else if (currentToken.get()->getTokenType() == AttributeValueStartEqualsQuotes){
            currentToken = Parser::nextToken(false);
            if(currentToken.get()->getTokenType() == AttributeValue){
                retAtrribute.get()->setAttributeValue(currentToken);
                currentToken = Parser::nextToken(false);
                if(currentToken.get()->getTokenType() == AtrributeValueEndQuotes){
                    return retAtrribute;
                }
            }
        }
    }
    std::cout<< "ERROR PARSOWANIA " << currentToken.get()->getValue() <<" ** " << posCurrToken << std::endl;
    exit(posCurrToken);
}

std::shared_ptr<Component> Parser::buildComponent(){
    std::shared_ptr<Component> retComponent(new Component);
    if(currentToken.get()->getTokenType() == Text){
        retComponent.get()->setText(currentToken);
        retComponent.get()->setIsText(true);
        return retComponent;
    }
    else if(currentToken.get()->getTokenType() == ScriptStart){
        retComponent.get()->setStartTag(currentToken);
        currentToken = Parser::nextToken(false);
        if (currentToken.get()->getTokenType() == Text) { // dla startaga dojdzie jeszcze reszta
            retComponent.get()->getComponents().push_back(buildComponent()); //zbuduj komponent tekstu - tego co pomiedzy <s.. </s..
            currentToken = Parser::nextToken(false);
        }
        if (currentToken.get()->getTokenType() == ScriptEnd){
            return retComponent;
        }
    }
    else if(currentToken.get()->getTokenType() == StartTag){
        retComponent.get()->setStartTag(currentToken);
        currentToken = Parser::nextToken(false);
        while (currentToken.get()->getTokenType() == AttributeNoValue || currentToken.get()->getTokenType() == Attribute) {
            retComponent.get()->getAttributes().push_back(buildHtmlAttribute());
            currentToken = Parser::nextToken(false);
        }
        if (currentToken.get()->getTokenType() == EndTag){
            currentToken = Parser::nextToken(false);
            while (currentToken.get()->getTokenType() == StartTag || currentToken.get()->getTokenType() == StartTagVoid || currentToken.get()->getTokenType() == ScriptStart || currentToken.get()->getTokenType() == Text) { // dla startaga dojdzie jeszcze reszta
                retComponent.get()->getComponents().push_back(buildComponent()); //zbuduj komponent tekstu - tego co pomiedzy <s.. </s..
                currentToken = Parser::nextToken(false);
            }
            if (currentToken.get()->getTokenType() == StartOnEndTag && retComponent.get()->compareStartAndEndTag(currentToken)){
                currentToken = Parser::nextToken(false);
                if (currentToken.get()->getTokenType() == EndTag){
                    return retComponent;
                }
            }
        }
        else if (currentToken.get()->getTokenType() == EndOnStartTag){
            return retComponent; //tag samozamykajacy sie
        }
    }
    else if(currentToken.get()->getTokenType() == StartTagVoid){
        retComponent.get()->setStartTag(currentToken);
        currentToken = Parser::nextToken(false);
        while (currentToken.get()->getTokenType() == AttributeNoValue || currentToken.get()->getTokenType() == Attribute) {
            retComponent.get()->getAttributes().push_back(buildHtmlAttribute());
            currentToken = Parser::nextToken(false);
        }
        if (currentToken.get()->getTokenType() == EndTag){
            return retComponent;
        }
        else if (currentToken.get()->getTokenType() == EndOnStartTag){
            return retComponent; //tag samozamykajacy sie
        }
    }
    std::cout<< "ERROR PARSOWANIA " << currentToken.get()->getValue() <<" ** " << posCurrToken << std::endl;
    exit(posCurrToken);
}

std::shared_ptr<Token> Parser::nextToken(bool isPossibleEnd){
    if (!tokens->empty()){
        std::shared_ptr<Token> retToken = tokens->front();
        posCurrToken++;
        tokens->pop();
        return retToken;
    }
    if (isPossibleEnd){
        return NULL;
    }
    else{
        std::cout<< "ERROR PARSOWANIA. KONIEC TOKENOW W NIEODPOWIEDNIM MOMENCIE" << std::endl;
        exit(posCurrToken);
    }
}


/*
 * Search component with given tag token
 * @return list of found components
 */
std::vector<std::shared_ptr<Component>> findComponents(std::shared_ptr<Component> component, Token startTag){

    std::vector<std::shared_ptr<Component>> found;
    if (component.get()->getStartTag() == NULL){
        std::cout << " tekst to " << component.get()->getText().get()->getValue() << std::endl;
        return found;
    }
    else {
        std::cout << component.get()->getStartTag().get()->getValue() << " ";
        std::cout << component.get()->getComponents().size() << std::endl;
    }
    if (component.get()->getStartTag().get()->getValue() == startTag.getValue() && component.get()->getStartTag().get()->getTokenType() == startTag.getTokenType()){
        found.push_back(component);
    }
    for (int i = 0; i < component.get()->getComponents().size(); ++i) {
        std::vector<std::shared_ptr<Component>> recursiveFound = findComponents(component.get()->getComponents().at(i), startTag);
        found.insert(found.end(), recursiveFound.begin(), recursiveFound.end());
    }
    return found;
}

std::vector<std::shared_ptr<Component>> Parser::findComponentsInDocument(std::shared_ptr<HtmlDocument> document, Token startTag){
    std::vector<std::shared_ptr<Component>> found;
    for (int i = 0; i < document.get()->getComponents().size(); ++i) {
        found = findComponents(document.get()->getComponents().at(i), startTag);
        std::cout<< "to ";
        std::cout<< found.size() << std::endl;
    }
    return found;
}