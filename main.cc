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
    if(argc != 6) {
        printf("Too few input arguments \n");
        printf("Run as - ./Analizator <malwrInputFile> <outputJsonFile> <dateFrom> <dateTo> <fileType>\n");
        printf("Date is - <day/month/year,hour:minute>\n");
        printf("If no filter is needed - type 'none' in each position\n");
        printf("E.g. './Analizator fileIn fileOut.json none none none' give all records without filtering\n");
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

    std::cout << "\nScanner - success" << std::endl;

    std::shared_ptr<Parser> parserPtr = std::shared_ptr<Parser>(new Parser(&tokens));

    MalwrAnalyzer malwrAnalyzer(parserPtr);

    try {
        malwrAnalyzer.runMalwrAnalyzer(argv);
    }
    catch (PerrorException &e){
        std::cout << e.getErrorMsg() << std::endl;
        return -1;
    }

    std::cout << "Program - success \n" << std::endl;

    return 0;
}