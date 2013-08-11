//
//  ModelComponent.h
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 27/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2__ModelComponent__
#define __Tool2__ModelComponent__

#include <iostream>
#include <OpenGL/gl3.h>
#include <vector>
#include "glm/glm.hpp"
#include "glStructs.h"
#include "Layer.h"

struct Vertex
{
    GLfloat position[3];
};

struct Color
{
    GLfloat color[3];
};


class ModelComponent
{
public:
    ModelComponent();
    std::vector<Vertex> vertexList;
    std::vector<GLint> indexList;
    std::vector<Color> colorList;
    
    void insertVertex(GLfloat x, GLfloat y, GLfloat z);
    void buildVAO();
    void printVertices();
    void repaint(glm::vec3 newColor);
    void updateColors();
    GLuint vao;
    
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint colorBuffer;
    
    glm::vec3 color;
    glm::vec3 component_min, component_max, component_center;
    
    Layer* layer;
    
    int type;

//	GLuint texIndex;
//	GLuint uniformBlockIndex;
//	int numFaces;
};

#endif /* defined(__Tool2__ModelComponent__) */
