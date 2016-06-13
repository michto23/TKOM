//
// Created by michto on 11.06.16.
//

#include "MalwrAnalyzer.h"
#include "../exception/PerrorException.hpp"

void MalwrAnalyzer::buildHtmlDocumentTree () {
    htmlDocument = parser.get()->buildHtmlDocumentTree();
}

std::shared_ptr<MalwrDTO> MalwrAnalyzer::createMalwrDTO (std::shared_ptr<Component> trComponent) { //<tr component
    std::string strDate;
    std::string md5;
    std::string fileName;
    std::string fileType;
    std::string antivirusScore;
    std::string link;

    for (int i = 0; i < trComponent.get()->getComponents().size(); ++i) {

        if (trComponent.get()->getComponents().size() != 5){
            throw PerrorException( "ERROR STRUKTURY KODU ANALIZY MALWR.COM \n");
        }

        std::shared_ptr<Component> current = trComponent.get()->getComponents().at(i);

        if (i == 0){
            strDate = current.get()->getComponents().at(0).get()->getText().get()->getValue();
        }
        else if (i == 1){
            link = current.get()->getComponents().at(0).get()->getAttributes().at(0).get()->getAttributeValue().get()->getValue();
            md5 = current.get()->getComponents().at(0).get()->getComponents().at(0).get()->getComponents().at(0).get()->getText().get()->getValue();
        }
        else if (i == 2){
            fileName = current.get()->getComponents().at(0).get()->getText().get()->getValue();
        }
        else if (i == 3){
            fileType = current.get()->getComponents().at(0).get()->getText().get()->getValue();
        }
        else if (i == 4){
            antivirusScore = current.get()->getComponents().at(0).get()->getText().get()->getValue();
        }
    }

    return std::shared_ptr<MalwrDTO>(new MalwrDTO(md5, fileName, fileType, antivirusScore, link, strDate));
}

void MalwrAnalyzer::findMalwrDTOComponents() {
    Token token(TR_TOKEN_VALUE, StartTag);
    std::vector<std::shared_ptr<Component>> result = parser.get()->findComponentsInDocument(htmlDocument, token);
    for (int i = 0; i < result.size(); ++i) {
        if (i != 0){
            malwrDTOs.push_back(createMalwrDTO(result.at(i)));
        }
    }
}

std::vector<std::shared_ptr<MalwrDTO>> MalwrAnalyzer::filterMalwrDTOs(char **argv){
    std::vector<std::shared_ptr<MalwrDTO>> filteredMalwrDTOs;
    std::string dateFromStr = argv[2];
    std::string dateToStr = argv[3];
    std::string fileType = argv[4];

    for (int i = 0; i < malwrDTOs.size(); ++i) {
        if (malwrDTOs.at(i).get()->dateGreaterThan(dateFromStr) && malwrDTOs.at(i).get()->dateLowerThan(dateToStr) && malwrDTOs.at(i).get()->fileTypeLike(fileType)){
            filteredMalwrDTOs.push_back(malwrDTOs.at(i));
        }
    }

    return filteredMalwrDTOs;
}

void MalwrAnalyzer::runMalwrAnalyzer(char **argv){
    try {
        buildHtmlDocumentTree();
    }
    catch (PerrorException &e){
        std::cout << "Error buildHtmlDocumentTree " << std::endl;
        std::cout << e.getErrorMsg() << std::endl;
        exit(-1);
    }
    std::cout << "Parser tree - sukces " << std::endl;

    findMalwrDTOComponents();
    std::vector<std::shared_ptr<MalwrDTO>> filteredMalwrDTOs = filterMalwrDTOs(argv);

    std::ofstream outputJson;
    outputJson.open (OUTPUT_JSON_FILE);
    outputJson << "[";

    for (int i = 0; i < filteredMalwrDTOs.size(); ++i) {
        outputJson << filteredMalwrDTOs.at(i).get()->toJSON();
        if (i != filteredMalwrDTOs.size() - 1){
            outputJson << ",";
        }
    }

    outputJson << "]";
    outputJson.close();
}