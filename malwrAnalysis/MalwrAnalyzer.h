//
// Created by michto on 11.06.16.
//

#ifndef TKOM_MALWRANALYZER_H
#define TKOM_MALWRANALYZER_H
#define TR_TOKEN_VALUE "<tr"
#define OUTPUT_JSON_FILE "outputJson.json"


#include <memory>
#include <vector>
#include <queue>
#include <fstream>
#include "MalwrDTO.h"
#include "../parser/Parser.h"

class MalwrAnalyzer {
private:
    std::vector<std::shared_ptr<MalwrDTO>> malwrDTOs;
    std::shared_ptr<Parser> parser;
    std::shared_ptr<HtmlDocument> htmlDocument;

public:
    MalwrAnalyzer(std::shared_ptr<Parser> &parser) : parser(parser) { }
    void buildHtmlDocumentTree ();
    std::shared_ptr<MalwrDTO> createMalwrDTO (std::shared_ptr<Component> trComponent);
    void findMalwrDTOComponents();
    std::vector<std::shared_ptr<MalwrDTO>> filterMalwrDTOs(char **argv);
    void runMalwrAnalyzer(char **argv);
};


#endif //TKOM_MALWRANALYZER_H
