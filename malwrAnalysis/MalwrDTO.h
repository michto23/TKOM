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
        date = strDate;

        const char * c = strDate.c_str();

        if (strptime(c, "%b %d, %Y, %I:%M %p", &tm) == NULL){
            printf("Error stringDateToTmStruct conversion \n");
        }

        tm.tm_isdst = -1;
        t = mktime(&tm);
        if (t == -1){
            printf("Error time_t conversion \n");
        }

//        std::cout << t << std::endl;
//        printf("seconds since the Epoch: %ld\n", (long) t);
//        printf("**************\n");

//        printf("Time charowy to %s \n", c);
//
//
//        /* Handle error */;
//        printf("year: %d; month: %d; day: %d;\n",
//               tm.tm_year, tm.tm_mon, tm.tm_mday);
//        tm.tm_sec = 0;
//        printf("hour: %d; minute: %d; second: %d\n",
//               tm.tm_hour, tm.tm_min, tm.tm_sec);
    }

    void fileTypeNoWhitespace(){
//        size_t pos = fileType.find_first_not_of(" \t\r\n");
//        fileType = fileType.substr(pos, fileType.length()); //clear whitespaces on start
        fileType.erase(0, fileType.find_first_not_of(" \t\r\n"));
        fileType.erase(fileType.find_last_not_of(" \t\r\n"), fileType.length());
    }

    void toString() {
        std::cout << "md 5 to " << md5 << std::endl;
        std::cout << "fileName to " << fileName << std::endl;
        std::cout << "fileType to " << fileType << std::endl;
        std::cout << "antivirusScore to " << antivirusScore << std::endl;
        std::cout << "link to " << link << std::endl;
//        std::cout << "strDate to " << strDate << std::endl;
        std::cout << "**********************************" << std::endl;
    }
public:

    std::string toJSON(){
        Json::Value root;
        root["md 5"] = md5;
        root["fileName"] = fileName;
        root["fileType"] = fileType;
        root["antivirusScore"] = antivirusScore;
        root["link"] = link;
        root["date"] = date;

        Json::StyledWriter writer;
        std::string outputConfig = writer.write( root );
        std::cout << outputConfig << std::endl;

        return outputConfig;
    }

    MalwrDTO(const std::string md5, const std::string fileName, const std::string fileType,
             const std::string antivirusScore, const std::string &link, const std::string strDate) : md5(md5), fileName(fileName),
                                                                                         fileType(fileType),
                                                                                         antivirusScore(antivirusScore),
                                                                                         link(link) {
        tm = {0};
        stringDateToTmStruct(strDate);
        fileTypeNoWhitespace();
//        toString();
//        toJSON();

    }

    virtual ~MalwrDTO() { }

    // 12/05/2015,13:02 none exe
    bool dateGreaterThan(std::string dateFrom){
        if (dateFrom == "none")
            return true;

        const char * c = dateFrom.c_str();
        struct tm timeStruct = {0};
        time_t timeToCompare;

//        printf("Time charowy to %s \n", c);

        if (strptime(c, "%d/%m/%Y,%H:%M", &timeStruct) == NULL){
            printf("Error stringDateToTmStruct conversion \n");
        }

        timeStruct.tm_isdst = -1;
        timeToCompare = mktime(&timeStruct);
        if (timeToCompare == -1){
            printf("Error time_t conversion \n");
        }

        /* Handle error */;
//        printf("year: %d; month: %d; day: %d;\n",
//               timeStruct.tm_year, timeStruct.tm_mon, timeStruct.tm_mday);
//        tm.tm_sec = 0;
//        printf("hour: %d; minute: %d; second: %d\n",
//               timeStruct.tm_hour, timeStruct.tm_min, timeStruct.tm_sec);

        if (t >= timeToCompare){
            return true;
        }

        return false;
    }

    bool dateLowerThan(std::string dateTo){
        if (dateTo == "none")
            return true;

        const char * c = dateTo.c_str();
        struct tm timeStruct= {0};
        time_t timeToCompare;

        if (strptime(c, "%d/%m/%Y,%H:%M", &timeStruct) == NULL){
            printf("Error stringDateToTmStruct conversion \n");
        }

        timeStruct.tm_isdst = -1;
        timeToCompare = mktime(&timeStruct);
        if (timeToCompare == -1){
            printf("Error time_t conversion \n");
        }

//        std::cout << t << std::endl;
//        std::cout << timeToCompare << std::endl;

        if (t <= timeToCompare){
            return true;
        }

        return false;
    }

    bool fileTypeLike(std::string fType){
        if (fType == "none")
            return true;

        std::string fileTypeToUpper(fileType);
        std::transform(fileTypeToUpper.begin(), fileTypeToUpper.end(),fileTypeToUpper.begin(), ::toupper);
        std::transform(fType.begin(), fType.end(),fType.begin(), ::toupper);

        if (fileTypeToUpper.find(fType) != std::string::npos){
            return true;
        }

        return false;
    }


};

#endif //TKOM_MALWRDTO_H
