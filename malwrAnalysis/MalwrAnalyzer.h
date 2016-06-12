//
// Created by michto on 11.06.16.
//

#ifndef TKOM_MALWRANALYZER_H
#define TKOM_MALWRANALYZER_H


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

    void buildHtmlDocumentTree () {
        htmlDocument = parser.get()->buildHtmlDocumentTree();
    }

    std::shared_ptr<MalwrDTO> createMalwrDTO (std::shared_ptr<Component> trComponent) { //<tr component
        std::string strDate;
        std::string md5;
        std::string fileName;
        std::string fileType;
        std::string antivirusScore;
        std::string link;

        for (int i = 0; i < trComponent.get()->getComponents().size(); ++i) {

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

    void findMalwrDTOComponents() {
        Token token("<tr", StartTag);
        std::vector<std::shared_ptr<Component>> result = parser.get()->findComponentsInDocument(htmlDocument, token);
        std::cout << "sprawdz size" <<result.size() << std::endl;
        for (int i = 0; i < result.size(); ++i) {
            if (i != 0){
                malwrDTOs.push_back(createMalwrDTO(result.at(i)));
            }
        }
        std::cout << "sprawdz malwrtDTO size " <<malwrDTOs.size() << std::endl;
    }

    std::vector<std::shared_ptr<MalwrDTO>> filterMalwrDTOs(char **argv){
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

    void runMalwrAnalyzer(char **argv){
        buildHtmlDocumentTree();
        findMalwrDTOComponents();
        std::vector<std::shared_ptr<MalwrDTO>> filteredMalwrDTOs = filterMalwrDTOs(argv);
        std::cout << "size tego filtrowanego to " << filteredMalwrDTOs.size() << std::endl;

        std::ofstream outputJson;
        outputJson.open ("outputJson.json");
        outputJson << "[";

        for (int i = 0; i < filteredMalwrDTOs.size(); ++i) {
            filteredMalwrDTOs.at(i).get()->toJSON();
            outputJson << filteredMalwrDTOs.at(i).get()->toJSON();
            if (i != filteredMalwrDTOs.size() - 1){
                outputJson << ",";
            }
        }

        outputJson << "]";
        outputJson.close();


    }
};


#endif //TKOM_MALWRANALYZER_H
