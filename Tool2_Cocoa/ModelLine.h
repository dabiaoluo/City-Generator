//
//  ModelLine.h
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 28/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2_Cocoa__Road__
#define __Tool2_Cocoa__Road__

#include <iostream>
#include "glm/glm.hpp"
#include "Layer.h"

class ModelLine
{
public:
    glm::vec3 a,b;
    int colorIndex;
    Layer *layer;
};

#endif /* defined(__Tool2_Cocoa__Road__) */
