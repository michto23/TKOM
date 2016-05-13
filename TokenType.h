//
// Created by michto on 13.05.16.
//

#ifndef TKOM_TOKENTYPE_H
#define TKOM_TOKENTYPE_H

#include <string>

enum TokenType {
    ScriptStart = 1,
    ScriptKoniec,
    ScriptText,
    StartTag,
    EndTag,
    EndOnStartTag, // '/>'
    StartOnEndTag, // '</{tagName}'
    Attribute,
    AttributeNoValue,
    AttributeValueStartEqualsQuote,
    AttributeValueStartEqualsQuotes,
    AttributeValue,
    AtrributeValueEndQuote,
    AtrributeValueEndQuotes,
    SpecialCharText, // eg. < , parser concats it with text before and after this char
    Text
};

std::string getTokenName(int token) {
    switch(token) {
        case ScriptStart:                       return "ScriptStart";
        case ScriptKoniec:                      return "ScriptKoniec";
        case ScriptText:                        return "ScriptText";
        case StartTag:                          return "StartTag";
        case EndTag:                            return "EndTag";
        case EndOnStartTag:                     return "EndOnStartTag";
        case StartOnEndTag:                     return "StartOnEndTag";
        case Attribute:                         return "Attribute";
        case AttributeNoValue:                  return "AttributeNoValue";
        case AttributeValueStartEqualsQuote:    return "AttributeValueStartEqualsQuote";
        case AttributeValueStartEqualsQuotes:   return "AttributeValueStartEqualsQuotes";
        case AttributeValue:                    return "AttributeValue";
        case AtrributeValueEndQuote:            return "AtrributeValueEndQuote";
        case AtrributeValueEndQuotes:           return "AtrributeValueEndQuotes";
        case SpecialCharText:                   return "SpecialCharText";
        case Text:                              return "Text";
        default:                                return "";
    }
}

#endif //TKOM_TOKENTYPE_H
