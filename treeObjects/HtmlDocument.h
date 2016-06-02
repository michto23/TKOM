//
// Created by michto on 31.05.16.
//

#ifndef TKOM_HTMLDOCUMENT_H
#define TKOM_HTMLDOCUMENT_H


#include <memory>
#include <vector>
#include "Component.h"
#include "Doctype.h"

class HtmlDocument {
private:
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<Doctype> doctype;
public:

    std::vector<std::shared_ptr<Component>> &getComponents() {
        return components;
    }

    void setComponents(std::vector<std::shared_ptr<Component>> &components) {
        HtmlDocument::components = components;
    }

    std::shared_ptr<Doctype> &getDoctype() {
        return doctype;
    }

    void setDoctype(std::shared_ptr<Doctype> &doctype) {
        HtmlDocument::doctype = doctype;
    }
};


#endif //TKOM_HTMLDOCUMENT_H
