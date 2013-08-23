//
//  Vertex.h
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 14/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2_Cocoa__Vertex__
#define __Tool2_Cocoa__Vertex__

#include <iostream>
#include <list>
#include "glm/glm.hpp"
#include <string>
#include <sstream>

class Road;

class RoadVertex {
public:
    RoadVertex(glm::vec2 position);
    
    std::list<Road*> tempIn;
    std::list<Road*> tempOut;
    
    std::list<Road*> roadIn;
    std::list<Road*> roadOut;
    glm::vec2 position;
    
    int64_t identifier;
    std::ostringstream name;
};

#endif /* defined(__Tool2_Cocoa__Vertex__) */
