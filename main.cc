#include <iostream>
#include <fstream>
#include <FlexLexer.h>
#include <vector>
#include <memory>
#include <queue>
#include "/home/michto/Studia/TKOM/TokenType.h"
#include "token/Token.hpp"
#include "treeObjects/HtmlAttribute.h"
#include "parser/Parser.h"

int main( int argc, char** argv)
{

    std::queue<std::shared_ptr<Token>> tokens;

    if(argc != 2) {
        return 1;
    }

    std::filebuf fb;
    std::istream* is;

    if (fb.open (argv[1] ,std::ios::in)) {
        is = new std::istream(&fb);
    }

    FlexLexer* lexer = new yyFlexLexer(is);

    while(true){
        int token = lexer->yylex(); //return some token or 0 - EOF
        if(token == 0)
            break;
        if(token == Text || token == SpecialCharText){
            std::string text = lexer->YYText();
            token = lexer->yylex();
            while (token == Text || token == SpecialCharText){
                text.append(lexer->YYText());
                token = lexer->yylex();
            }
            tokens.push(std::shared_ptr<Token>(new Token(text, Text)));
        }
        tokens.push(std::shared_ptr<Token>(new Token(lexer->YYText(), static_cast<TokenType>(token))));
//        std::cout<< "******" << getTokenName(token) <<"  ---->  " <<lexer->YYText() <<std::endl; //read text from lexer yytext
    }

//    long id = 0;
//    while (!tokens.empty())
//    {
//        std::cout<<  id << " ****** " << getTokenName(tokens.front()->getTokenType()) <<"  ---->  " <<tokens.front().get()->getValue() <<std::endl;
//        tokens.pop();
//        if (id == 2503){
//            break;
//        }
//        ++id;
//    }

    Parser parser(&tokens);
    parser.buildHtmlDocumentTree();

    return 0;
}