//
// Created by michto on 12.06.16.
//

#ifndef TKOM_MALWRDTO_H
#define TKOM_MALWRDTO_H

#include <string>
#include <iostream>

class MalwrDTO {
private:
    std::string md5;
    std::string fileName;
    std::string fileType;
    std::string antivirusScore;
    std::string link;
    struct tm tm;
    void stringDateToTmStruct(std::string strDate){
        if (strDate.find("p.m.") != std::string::npos) {
            strDate = strDate.substr(0, strDate.length() - 5);
            strDate += " PM";
        }
        else if (strDate.find("a.m.") != std::string::npos) {
            strDate = strDate.substr(0, strDate.length() - 5);
            strDate += " AM";
        }
        else if (strDate.find("noon") != std::string::npos) {
            strDate = strDate.substr(0, strDate.length() - 4);
            strDate += "12:00 PM";
        }

        const char * c = strDate.c_str();

//        std::cout << strDate << std::endl;
        if (strptime(c, "%b %d, %Y, %I:%M %p", &tm) == NULL){
            printf("Error stringDateToTmStruct conversion \n");
        }

//        printf("year: %d; month: %d; day: %d;\n",
//               tm.tm_year, tm.tm_mon, tm.tm_mday);
//        tm.tm_sec = 0;
//        printf("hour: %d; minute: %d; second: %d\n",
//               tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
public:


    MalwrDTO(const std::string &md5, const std::string &fileName, const std::string &fileType,
             const std::string &antivirusScore, const std::string &link, const std::string &strDate) : md5(md5), fileName(fileName),
                                                                                         fileType(fileType),
                                                                                         antivirusScore(antivirusScore),
                                                                                         link(link) {
        stringDateToTmStruct(strDate);

        std::cout << "md 5 to " << md5 << std::endl;
        std::cout << "fileName to " << fileName << std::endl;
        std::cout << "fileType to " << fileType << std::endl;
        std::cout << "antivirusScore to " << antivirusScore << std::endl;
        std::cout << "link to " << link << std::endl;
        std::cout << "strDate to " << strDate << std::endl;
        std::cout << "**********************************" << std::endl;
    }


    virtual ~MalwrDTO() { }


};

#endif //TKOM_MALWRDTO_H
