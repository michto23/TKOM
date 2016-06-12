//
// Created by michto on 12.06.16.
//

#ifndef TKOM_MALWRDTO_H
#define TKOM_MALWRDTO_H

#include <string>
#include <iostream>
#include <algorithm>
#include "../json/json.h"
#include "../json/json-forwards.h"
#define NONE_FILTER_TXT "none"

class MalwrDTO {
private:
    std::string md5;
    std::string fileName;
    std::string fileType;
    std::string antivirusScore;
    std::string link;
    std::string date;
    struct tm tm;
    time_t t;

    void stringDateToTmStruct(std::string strDate);
    void fileTypeNoWhitespace();
    void toString();

public:

    MalwrDTO(const std::string md5, const std::string fileName, const std::string fileType,
             const std::string antivirusScore, const std::string &link, const std::string strDate) : md5(md5), fileName(fileName),
                                                                                                     fileType(fileType),
                                                                                                     antivirusScore(antivirusScore),
                                                                                                     link(link) {
        tm = {0};
        stringDateToTmStruct(strDate);
        fileTypeNoWhitespace();
    }

    virtual ~MalwrDTO() { }
    std::string toJSON();
    bool dateGreaterThan(std::string dateFrom);
    bool dateLowerThan(std::string dateTo);
    bool fileTypeLike(std::string fType);
};

#endif //TKOM_MALWRDTO_H
