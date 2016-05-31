#include <iostream>
#include <fstream>
#include <FlexLexer.h>
#include <vector>
#include <memory>
#include "TokenType.h"
#include "token/Token.hpp"


int main( int argc, char** argv)
{

    std::vector<std::shared_ptr<Token>> tokens;

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
        tokens.push_back(std::shared_ptr<Token>(new Token(lexer->YYText(), static_cast<TokenType>(token))));

//        std::cout<< "******" << getTokenName(token) <<"  ---->  " <<lexer->YYText() <<std::endl; //read text from lexer yytext
    }

    for (int i = 0; i < tokens.size(); ++i){
        std::cout<< "******" << getTokenName(tokens.at(i).get()->getTokenType()) <<"  ---->  " <<tokens.at(i).get()->getValue() <<std::endl;
    }


    return 0;
}