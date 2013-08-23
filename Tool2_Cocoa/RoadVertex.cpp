//
//  Vertex.cpp
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 14/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "RoadVertex.h"


RoadVertex::RoadVertex(glm::vec2 pos)
{
    this->position = glm::vec2(pos);
    this->name << "L" << pos.x << "-L" << pos.y;
//    printf("Node: %s\n", this->name.str().c_str());
}