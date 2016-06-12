//
// Created by michto on 12.06.16.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H


#include <memory>
#include <queue>
#include "../token/Token.hpp"

class Scanner {
public:
    std::queue<std::shared_ptr<Token>> scanDocument(char** argv);
};


#endif //TKOM_SCANNER_H
