//
//  ModelComponent.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 27/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "ModelComponent.h"
#include "Engine.h"

extern Engine* engine;

using namespace SpatialIndex;

ModelComponent::ModelComponent()
{
//    vertexList = new std::list<Vertex*>;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    
    component_min.x = 999999999;
    component_min.x = 999999999;
    component_min.x = 999999999;
    
    component_max.x = -999999999;
    component_max.x = -999999999;
    component_max.x = -999999999;
}

void ModelComponent::insertVertex(GLfloat x, GLfloat y, GLfloat z)
{
    Vertex newVertex;
    newVertex.position[0] = x;
    newVertex.position[1] = y;
    newVertex.position[2] = z;
    
    if (component_min.x > newVertex.position[0]) {
        component_min.x = newVertex.position[0];
    }
    if (component_min.y > newVertex.position[1]) {
        component_min.y = newVertex.position[1];
    }
    if (component_min.z > newVertex.position[2]) {
        component_min.z = newVertex.position[2];
    }

    if (component_max.x < newVertex.position[0]) {
        component_max.x = newVertex.position[0];
    }
    if (component_max.y < newVertex.position[1]) {
        component_max.y = newVertex.position[1];
    }
    if (component_max.z < newVertex.position[2]) {
        component_max.z = newVertex.position[2];
    }
    
    double p[2], op[2];
    
    if(vertexList.size() > 0)
    {
        id_type id = engine->getNextIdentifier();
        
        p[0] = x;
        p[1] = y;
        
        op[0] = vertexList.back().position[0];
        op[1] = vertexList.back().position[1];
        
        LineSegment line = LineSegment(p, op, 2);
        
        engine->tree->insertData(0, 0, line, id);
        
//        printf("Inserted line [%lld]: (%f, %f), (%f, %f)\n", id, p[0], p[1], op[0], op[1]);
        engine->componentMap[id].modelComponent = this;
        engine->componentMap[id].building = NULL;
    }
    
    vertexList.push_back(newVertex); // add vertex to list
    

    
    Color newColor;
    if(color[0] == 255)
    {
        newColor.color[0] = 88.0f/255.0f;
        newColor.color[1] = 88.0f/255.0f;
        newColor.color[2] = (float)layer->color/255;
    }
    else
    {
        newColor.color[0] = color[0];
        newColor.color[1] = color[1];
        newColor.color[2] = color[2];
    }

//    printf("color: (%f, %f, %f)\n", newColor.color[0], newColor.color[1], newColor.color[2]);
    
    colorList.push_back(newColor);
    
    GLint lastIndex = 0;
    if(indexList.size() > 0)
    {
        lastIndex = indexList[indexList.size()-1]+1;
    }
//    printf("lastIndex: %d\n", lastIndex);
    indexList.push_back(lastIndex);
}

void ModelComponent::printVertices()
{
    for(int i=0;i<vertexList.size() && i < 1;i++)
    {
        printf("index[%d] (%f, %f %f)\n", indexList[i], vertexList[i].position[0], vertexList[i].position[1], vertexList[i].position[2]);
    }
}

void ModelComponent::repaint(glm::vec3 newColor)
{
    Color c;
    
    c.color[0] = newColor.x;
    c.color[1] = newColor.y;
    c.color[2] = newColor.z;
    
    //colorList.size();
//    printf("Size: (%ld, %ld)\n", colorList.size(), vertexList.size());

    for(int i=0;i < colorList.size();i++)
    {
        colorList[i] = c;
    }
    updateColors();
}

void ModelComponent::updateColors()
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color) * colorList.size(), &colorList[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(ATTRIB_COLOR);
    glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, 0, 0, 0);
    glBindVertexArray(0);
}

void ModelComponent::buildVAO()
{
    // generate Vertex Array for mesh
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    // buffer for faces
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indexList.size(), &indexList[0], GL_STATIC_DRAW);
    
    // buffer for vertex positions
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexList.size(), &vertexList[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, 0);
    
    // buffer for vertex colors
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color) * colorList.size(), &colorList[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(ATTRIB_COLOR);
    glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, 0, 0, 0);
    
    // unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
//    this->repaint(glm::vec3(255,0,0));
}
