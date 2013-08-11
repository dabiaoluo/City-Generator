//
//  Model.h
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 21/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2__Model__
#define __Tool2__Model__

#define GLM_SWIZZLE

#include <math.h>
#include <fstream>
#include <map>
#include <string>
#include <list>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "utils.h"

#include "ModelComponent.h"

#include <OpenGL/gl3.h>

class Model
{
public:
    Model();
    void buildVAO();
    void addComponent(ModelComponent *mc);
    void calculateBounds();

    
    glm::vec3 model_min, model_max, model_center;
    
    std::list<ModelComponent*> componentList;
};


#endif /* defined(__Tool2__Model__) */
