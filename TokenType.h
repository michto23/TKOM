//
// Created by michto on 13.05.16.
//

#ifndef TKOM_TOKENTYPE_H
#define TKOM_TOKENTYPE_H

#include <string>

enum TokenType {
    ScriptStart = 1,                // <script> , where script is non letter sensitive
    ScriptEnd,                      // </script> , where script is non letter sensitive
    StartTag,                       // <{tagName}
    EndTag,                         // >
    EndOnStartTag,                  // />
    StartOnEndTag,                  // </{tagName}
    Attribute,                      // name of attribute, eg. class
    AttributeNoValue,               // name of atrribute with no value, such as html in !doctype
    AttributeValueStartEqualsQuote, // '=
    AttributeValueStartEqualsQuotes,// "=
    AttributeValue,                 // everything between quotes after attribute
    AtrributeValueEndQuote,         // '
    AtrributeValueEndQuotes,        // "
    SpecialCharText,                // eg. < , parser concats it with text, which is before and after this char
    Text,                           // plain text with no '<' character
};

inline std::string getTokenName(int token) {
    switch(token) {
        case ScriptStart:                       return "ScriptStart";
        case ScriptEnd:                         return "ScriptEnd";
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
