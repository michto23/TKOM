#include <iostream>
#include <fstream>
#include <FlexLexer.h>
#include <vector>
#include <memory>
#include <queue>
#include "token/TokenType.h"
#include "token/Token.hpp"
#include "treeObjects/HtmlAttribute.hpp"
#include "parser/Parser.h"
#include "malwrAnalysis/MalwrDTO.h"
#include "malwrAnalysis/MalwrAnalyzer.h"
#include "scanner/Scanner.h"
#include "exception/PerrorException.hpp"

int main( int argc, char** argv)
{
    if(argc != 5) {
        printf("Za malo argumentow wejsciowych \n");
        return -1;
    }

    std::queue<std::shared_ptr<Token>> tokens;
    Scanner scanner;

    try {
        tokens = scanner.scanDocument(argv);
    }
    catch (PerrorException &e){
        std::cout << e.getErrorMsg() << std::endl;
        return -1;
    }

    std::cout << "\nScanner - sukces" << std::endl;

    std::shared_ptr<Parser> parserPtr = std::shared_ptr<Parser>(new Parser(&tokens));

    MalwrAnalyzer malwrAnalyzer(parserPtr);

    try {
        malwrAnalyzer.runMalwrAnalyzer(argv);
    }
    catch (PerrorException &e){
        std::cout << e.getErrorMsg() << std::endl;
        return -1;
    }

    std::cout << "Program - sukces \n" << std::endl;

    return 0;
}