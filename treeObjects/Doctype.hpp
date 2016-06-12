//
// Created by michto on 31.05.16.
//

#ifndef TKOM_DOCTYPE_H
#define TKOM_DOCTYPE_H

#include <memory>
#include <vector>
#include "HtmlAttribute.hpp"

class Doctype {
private:
    std::vector<std::shared_ptr<HtmlAttribute>> attributes;
public:

    std::vector<std::shared_ptr<HtmlAttribute>> &getAttributes() {
        return attributes;
    }

    void setAttributes(const std::vector<std::shared_ptr<HtmlAttribute>> &attributes) {
        Doctype::attributes = attributes;
    }
};

#endif //TKOM_DOCTYPE_H
