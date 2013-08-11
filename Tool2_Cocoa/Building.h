//
//  Building.h
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 29/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2__Building__
#define __Tool2__Building__

#include <iostream>
#include <OpenGL/gl3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <list>
#include <vector>
#include "ModelComponent.h"

class Building {
    
public:
    
    Building();
    
    glm::vec3 position;
    float radius;
    
    void generate(int type);
    void buildVAO();
    
    float rotation;
    
    std::vector<Vertex> vertexList;
    std::vector<GLint> indexList;
    std::vector<Color> colorList;
    
    bool linkedWidth;
    bool linkedDepth;
    
    bool isBox;
    
    float width;
    float height;
    float depth;
    
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint colorBuffer;
    
    GLuint vao;
    
    int numTriangles;
};

#endif /* defined(__Tool2__Building__) */
