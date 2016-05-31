//
// Created by michto on 31.05.16.
//

#ifndef TKOM_DOCTYPE_H
#define TKOM_DOCTYPE_H

#include <memory>
#include <vector>
#include "HtmlAttribute.h"

class Doctype {
private:
    std::vector<std::shared_ptr<HtmlAttribute>> attributes;
};

#endif //TKOM_DOCTYPE_H
