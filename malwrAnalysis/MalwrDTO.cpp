//
// Created by michto on 12.06.16.
//

#include "MalwrDTO.h"
#include "../exception/PerrorException.hpp"

void MalwrDTO::stringDateToTmStruct(std::string strDate){
    if (strDate.size() < 6){
        throw PerrorException( "Invalid start date of <td> from malwr.com \n" );
    }
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
        throw PerrorException( "Invalid start date. Error stringDateToTmStruct conversion \n");
    }

    tm.tm_isdst = -1;
    t = mktime(&tm);
    if (t == -1){
        throw PerrorException( "Invalid start date. Error time_t conversion \n" );
    }
}

void MalwrDTO::fileTypeNoWhitespace(){
    fileType.erase(0, fileType.find_first_not_of(" \t\r\n"));
    fileType.erase(fileType.find_last_not_of(" \t\r\n"), fileType.length());
}

void MalwrDTO::toString() {
    std::cout << "md 5 to " << md5 << std::endl;
    std::cout << "fileName to " << fileName << std::endl;
    std::cout << "fileType to " << fileType << std::endl;
    std::cout << "antivirusScore to " << antivirusScore << std::endl;
    std::cout << "link to " << link << std::endl;
    std::cout << "strDate to " << date << std::endl;
    std::cout << "**********************************" << std::endl;
}

std::string MalwrDTO::toJSON(){
    Json::Value root;
    root["md 5"] = md5;
    root["fileName"] = fileName;
    root["fileType"] = fileType;
    root["antivirusScore"] = antivirusScore;
    root["link"] = link;
    root["date"] = date;

    Json::StyledWriter writer;
    std::string outputConfig = writer.write( root );
//    std::cout << outputConfig << std::endl;

    return outputConfig;
}

bool MalwrDTO::dateGreaterThan(std::string dateFrom){
    if (dateFrom == NONE_FILTER_TXT)
        return true;

    const char * c = dateFrom.c_str();
    struct tm timeStruct = {0};
    time_t timeToCompare;

    if (strptime(c, "%d/%m/%Y,%H:%M", &timeStruct) == NULL){
        throw PerrorException( "Invalid start date. Error stringDateToTmStruct conversion \n" );
    }

    timeStruct.tm_isdst = -1;
    timeToCompare = mktime(&timeStruct);
    if (timeToCompare == -1){
        throw PerrorException( "Invalid start date. Error time_t conversion \n" );
    }

    if (t >= timeToCompare){
        return true;
    }

    return false;
}

bool MalwrDTO::dateLowerThan(std::string dateTo){
    if (dateTo == NONE_FILTER_TXT)
        return true;

    const char * c = dateTo.c_str();
    struct tm timeStruct= {0};
    time_t timeToCompare;

    if (strptime(c, "%d/%m/%Y,%H:%M", &timeStruct) == NULL){
        throw PerrorException( "Invalid end date. Error stringDateToTmStruct conversion \n" );
    }

    timeStruct.tm_isdst = -1;
    timeToCompare = mktime(&timeStruct);
    if (timeToCompare == -1){
        throw PerrorException( "Invalid end date. Error time_t conversion \n" );
    }

    if (t <= timeToCompare){
        return true;
    }

    return false;
}

bool MalwrDTO::fileTypeLike(std::string fType){
    if (fType == NONE_FILTER_TXT)
        return true;

    std::string fileTypeToUpper(fileType);
    std::transform(fileTypeToUpper.begin(), fileTypeToUpper.end(),fileTypeToUpper.begin(), ::toupper);
    std::transform(fType.begin(), fType.end(),fType.begin(), ::toupper);

    if (fileTypeToUpper.find(fType) != std::string::npos){
        return true;
    }

    return false;
}