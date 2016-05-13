#include <iostream>
#include <fstream>
#include <FlexLexer.h>
#include "TokenType.h"


int main( int argc, char** argv)
{
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
        int token = lexer->yylex();
        if(token == 0)
            break;
        std::cout<< "******" << getTokenName(token) <<"  ---->  " <<lexer->YYText() <<std::endl;
    }


    return 0;
}