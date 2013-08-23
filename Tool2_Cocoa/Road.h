//
//  Road.h
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 14/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2_Cocoa__Road__
#define __Tool2_Cocoa__Road__

#include <iostream>
#include "Layer.h"
#include <sstream>

class RoadVertex;

class Road {
    
public:
    Road();
    RoadVertex *a, *b;
    Layer* layer;
    int lanes;
    bool direction;
    int64_t identifier;
    std::ostringstream name;
};

#endif /* defined(__Tool2_Cocoa__Road__) */
