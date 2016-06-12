//
// Created by michto on 12.06.16.
//

#include <FlexLexer.h>
#include <fstream>
#include "Scanner.h"

std::queue<std::shared_ptr<Token>> Scanner::scanDocument(char** argv) {

    std::queue<std::shared_ptr<Token>> tokens;

    std::filebuf fb;
    std::istream *is;

    if (fb.open(argv[1], std::ios::in)) {
        is = new std::istream(&fb);
    }

    FlexLexer *lexer = new yyFlexLexer(is);

    while (true) {
        int token = lexer->yylex(); //return some token or 0 - EOF
        if (token == 0)
            break;
        if (token == Text || token == SpecialCharText) {
            std::string text = lexer->YYText();
            token = lexer->yylex();
            while (token == Text || token == SpecialCharText) {
                text.append(lexer->YYText());
                token = lexer->yylex();
            }
            tokens.push(std::shared_ptr<Token>(new Token(text, Text)));
        }
        tokens.push(std::shared_ptr<Token>(new Token(lexer->YYText(), static_cast<TokenType>(token))));
    }

    return tokens;
}
