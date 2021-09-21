//
// Created by roagen on 20.09.2021.
//

#ifndef UNTITLED5_VISIBLE_H
#define UNTITLED5_VISIBLE_H


#include <variant>
#include "structs.h"
#include "mesh.h"

typedef std::variant<sphere,mesh> tShape;

class Visible {
private:
    tShape shape;
public:

    explicit Visible(tShape shape);




};



#endif //UNTITLED5_VISIBLE_H
