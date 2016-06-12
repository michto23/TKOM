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
#include "malwrAnalysis/MalwrDTO.h"
#include "malwrAnalysis/MalwrAnalyzer.h"
#include "scanner/Scanner.h"

int main( int argc, char** argv)
{



//    std::filebuf fb;
//    std::istream* is;
//
//    if (fb.open (argv[1] ,std::ios::in)) {
//        is = new std::istream(&fb);
//    }
//
//    FlexLexer* lexer = new yyFlexLexer(is);
//
//    while(true){
//        int token = lexer->yylex(); //return some token or 0 - EOF
//        if(token == 0)
//            break;
//        if(token == Text || token == SpecialCharText){
//            std::string text = lexer->YYText();
//            token = lexer->yylex();
//            while (token == Text || token == SpecialCharText){
//                text.append(lexer->YYText());
//                token = lexer->yylex();
//            }
//            tokens.push(std::shared_ptr<Token>(new Token(text, Text)));
//        }
//        tokens.push(std::shared_ptr<Token>(new Token(lexer->YYText(), static_cast<TokenType>(token))));




//        std::cout<< "******" << getTokenName(token) <<"  ---->  " <<lexer->YYText() <<std::endl; //read text from lexer yytext
//    }

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

//    Parser parser(&tokens);
//    std::shared_ptr<HtmlDocument> htmlDocument = parser.buildHtmlDocumentTree();
//    Token token1("<tr", StartTag);
//    parser.findComponentsInDocument(htmlDocument, token1);



//    std::cout<< "aaaaaaaaaaaaaa" << std::endl;
//    std::cout<< htmlDocument.get()->getComponents().at(0).get()->getComponents().size() << std::endl;

//MalwrDTO malwrDTO;


//    struct tm tm;
//    "June 11, 2016, 12:21 p.m.";
//
//
//    if (strptime("June 11, 2016, 01:21 PM", "%b %d, %Y, %I:%M %p", &tm) == NULL){
//        printf("eror na suke");
//    }
//        /* Handle error */;
//
//    printf("year: %d; month: %d; day: %d;\n",
//           tm.tm_year, tm.tm_mon, tm.tm_mday);
//    tm.tm_sec = 0;
//    printf("hour: %d; minute: %d; second: %d\n",
//           tm.tm_hour, tm.tm_min, tm.tm_sec);

//    Parser parser(&tokens);

    std::queue<std::shared_ptr<Token>> tokens;

    if(argc != 5) {
        printf("pizda\n");
        return 1;
    }

    Scanner scanner;
    tokens = scanner.scanDocument(argv);


    std::shared_ptr<Parser> parserPtr = std::shared_ptr<Parser>(new Parser(&tokens));
    MalwrAnalyzer malwrAnalyzer(parserPtr);
//    malwrAnalyzer.buildHtmlDocumentTree();
//    malwrAnalyzer.findMalwrDTOComponents();
    malwrAnalyzer.runMalwrAnalyzer(argv);


    return 0;
}