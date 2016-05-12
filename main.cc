#include <iostream>
#include <fstream>
#include <FlexLexer.h>


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
    while(lexer->yylex() != 0)
        ;
    return 0;
}