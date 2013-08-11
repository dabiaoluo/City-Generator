//
//  SurfaceFactory.h
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 04/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2__SurfaceFactory__
#define __Tool2__SurfaceFactory__

#include <iostream>

#include <OpenGL/gl3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include <list>

struct Vertex;
struct Color;

class SurfaceFactory
{
public:
    SurfaceFactory();
    void craftSurfaces();
    bool get_line_intersection(glm::vec2 p0, glm::vec2 p1,
                               glm::vec2 p2, glm::vec2 p3,
                               glm::vec2* i);
    void buildVAO();
    void setNextColor(Color *c);
    
    std::vector<Vertex> vertexList;
    std::vector<GLint> indexList;
    std::vector<Color> colorList;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint colorBuffer;
    
    GLuint vao;
    
    int counter;
    
    glm::vec3 color;
    
};

#endif /* defined(__Tool2__SurfaceFactory__) */
