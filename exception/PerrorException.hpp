//
// Created by michto on 12.06.16.
//

#include <exception>
#include <string>

#ifndef TKOM_PERROREXCEPTION_H
#define TKOM_PERROREXCEPTION_H

#endif //TKOM_PERROREXCEPTION_H

class PerrorException : public std::exception {
private:
    std::string errorMsg;
public:
    PerrorException(const std::string &errorMsg) : errorMsg(errorMsg) { }

    const std::string &getErrorMsg() const {
        return errorMsg;
    }

    void setErrorMsg(const std::string &errorMsg) {
        PerrorException::errorMsg = errorMsg;
    }
};