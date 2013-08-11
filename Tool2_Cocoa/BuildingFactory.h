//
//  BuildingFactory.h
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 28/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2__BuildingFactory__
#define __Tool2__BuildingFactory__

#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <list>
#include "Building.h"

class BuildingFactory
{
public:
    BuildingFactory();
    void createBuildingRandomPlace(int numBuildings);
    void createBuildingsOfType(float radius, int numBuildings, int type);
    float distancePoints(glm::vec3 a, glm::vec3 b);
    
    glm::vec3 point;
    float radius;
    int numBuildings;
    
    Building* currBuilding;
};


#endif /* defined(__Tool2__BuildingFactory__) */
