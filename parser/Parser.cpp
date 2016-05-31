//
// Created by michto on 30.05.16.
//

#include "Parser.h"

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

/*
 *     <area >
    <base>
    <br>
    <col>
    <command>
    <embed>
    <hr>
    <img>
    <input>
    <link>
    <meta>
    <param>
    <source>
    To exclude
 */