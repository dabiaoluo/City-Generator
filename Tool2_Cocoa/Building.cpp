//
//  Building.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 29/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "Building.h"
#include "Renderer.h"
#include "Engine.h"

extern Engine* engine;

struct BuildingComponent {

    float minHeight, maxHeight;
    float minWidth, maxWidth;
    float maxDepth, minDepth;
    
    float minRadius, maxRadius;
    
    int numTriangles;
    
    glm::vec3 color;
    
    bool hasRoof;

};

long roundNum(double x) {
    assert(x >= LONG_MIN-0.5);
    assert(x <= LONG_MAX+0.5);
    if (x >= 0)
        return (long) (x+0.5);
    return (long) (x-0.5);
}

Building::Building()
{
    linkedWidth = false;
    linkedDepth = false;
    isBox = true;
    
//    color = glm::vec3(233.0f/255.0f,162.0f/255.0f,108.0f/255.0f);
    
    numTriangles = 0;
    
    rotation = ((float)rand()/RAND_MAX)*180.0f;
}

void Building::generate(int type)
{
    std::list<BuildingComponent> bcList;
    
    this->texture = engine->textureList[(int) roundNum(((float)rand()/RAND_MAX)*(engine->textureList.size()-1))]->image;
    printf("%d\n", this->texture);
    BuildingComponent aux;
//    printf("%f, %f, %f\n", aux.color.x, aux.color.y, aux.color.z);
    int lastIndex = 0;
    
    float maxRadius = 0.0f;
    
    type = type%16;
    if(type == 0) type = 1;
    if(type == 11) type = 12;
    
    switch (type)
    {
            
        case 1: // ok ok
            //      - b1 t2: (Field and farm) This can be a storage building
            //          - Footprint: 650, max size
            //          - Height: 7m, up to 10m
            aux.minHeight = 0.07f;
            aux.maxHeight = 0.10f;
            aux.minWidth  = 0.15f;
            aux.maxWidth  = 0.25f;
            aux.minDepth  = 0.15f;
            aux.maxDepth  = 0.25f;
            aux.hasRoof = false;
            bcList.push_back(aux);
            break;
        case 2: // ok ok
            //      - b2 t2/6: This is types 2 and 6 building (field and farm / dense area)
            //          - Footprint 280, max size
            //          - Height 6m + 2m (roof), can be up to 11m
            aux.minHeight = 0.06f; // taller part
            aux.maxHeight = 0.06f;
            aux.minWidth  = 0.05f;
            aux.maxWidth  = 0.165f;
            aux.minDepth  = 0.05f;
            aux.maxDepth  = 0.165f;
//            aux.color = glm::vec3(107.0f/255.0f,238.0f/137.0f,112.0f/255.0f);
            aux.hasRoof = true;
            bcList.push_back(aux);
            break;
        case 3: // ok ok
            //      - b3 t2:
            //          - Footprint: around 8mx8m, can be up to 100m
            //          - Height: 3m + 2m (roof), can be up to 6m + 2m
            //          - Low-rise
            aux.minHeight = 0.03f;
            aux.maxHeight = 0.03f;
            aux.minWidth  = 0.05f;
            aux.maxWidth  = 0.10f;
            aux.minDepth  = 0.05f;
            aux.maxDepth  = 0.10f;
//            aux.color = glm::vec3(233.0f/255.0f,162.0f/255.0f,108.0f/255.0f);
            aux.hasRoof = true;
            bcList.push_back(aux);
            break;
        case 4: // ok ok
            //      - b4 t4:(not dense area)
            //          - Low-rise building
            //          - Footprint around 85, can be up to 150
            //          - Height: 3m + 3m + 2m (roof), max size
            aux.minHeight = 0.05f; // taller part
            aux.maxHeight = 0.06f;
            aux.minWidth  = 0.09f;
            aux.maxWidth  = 0.125f;
            aux.minDepth  = 0.04f;
            aux.maxDepth  = 0.06f;
//            aux.color = glm::vec3(154.0f/255.0f,78.0f/137.0f,6.0f/255.0f);
            linkedWidth = true;
            aux.hasRoof = true;
            bcList.push_back(aux);
            
            aux.minHeight = 0.03f; // deep part
            aux.maxHeight = 0.03f;
            aux.minWidth  = 0.09f;
            aux.maxWidth  = 0.125f;
            aux.minDepth  = 0.09f;
            aux.maxDepth  = 0.125f;
//            aux.color = glm::vec3(236.0f/255.0f,175.0f/137.0f,224.0f/255.0f);
            linkedWidth = true;
            aux.hasRoof = false;
            bcList.push_back(aux);
            
            break;
        case 5: // ok ok
            //      - b5 t4:
            //          - Footprint: around 100m, can be up to 200m
            //          - Height: 3m + 3m, can be up to 9m total
            //          - Low-rise building
            aux.minHeight = 0.03f; // taller part
            aux.maxHeight = 0.10f;
            aux.minWidth  = 0.05f;
            aux.maxWidth  = 0.08f;
            aux.minDepth  = 0.05f;
            aux.maxDepth  = 0.08f;
//            aux.color = glm::vec3(152.0f/255.0f,75.0f/137.0f,108.0f/255.0f);
            aux.hasRoof = false;
            bcList.push_back(aux);
            
            aux.minHeight = 0.03f; // wide part
            aux.maxHeight = 0.04f;
            aux.minWidth  = 0.06f;
            aux.maxWidth  = 0.10f;
            aux.minDepth  = 0.04f;
            aux.maxDepth  = 0.05f;
//            aux.color = glm::vec3(152.0f/255.0f,75.0f/137.0f,108.0f/255.0f);
            aux.hasRoof = false;
            bcList.push_back(aux);

            aux.minHeight = 0.03f; // deep part
            aux.maxHeight = 0.04f;
            aux.minWidth  = 0.04f;
            aux.maxWidth  = 0.05f;
            aux.minDepth  = 0.06f;
            aux.maxDepth  = 0.10f;
//            aux.color = glm::vec3(207.0f/255.0f,218.0f/137.0f,168.0f/255.0f);
            aux.hasRoof = false;
            bcList.push_back(aux);
            
            break;
        case 6: // ok ok
                //      - b6 t6:
            aux.minHeight = 0.03f;
            aux.maxHeight = 0.03f;
            aux.minWidth  = 0.03f;
            aux.maxWidth  = 0.05f;
            aux.minDepth  = 0.03f;
            aux.maxDepth  = 0.05f;
            aux.hasRoof = false;
            bcList.push_back(aux);
            break;
        case 7: // ok ok 
            //      - b7 t2 (Field and farm) This can be a storage building
            //          - Footprint 600, max size
            //          - Height 10m, max size
            aux.minHeight = 0.05f;
            aux.maxHeight = 0.10f;
            aux.minWidth  = 0.10f;
            aux.maxWidth  = 0.25f;
            aux.minDepth  = 0.10f;
            aux.maxDepth  = 0.25f;
            aux.hasRoof = false;
            bcList.push_back(aux);
            break;
        case 8: // ok ok 
            //      - b8 t4: (Not dense area)
            //          - Footprint 100m, up to 200m
            //          - Height 15m, max size
            aux.minHeight = 0.10f; // taller part
            aux.maxHeight = 0.15f;
            aux.minWidth  = 0.10f;
            aux.maxWidth  = 0.14f;
            aux.minDepth  = 0.10f;
            aux.maxDepth  = 0.14f;
            aux.hasRoof = false;
            bcList.push_back(aux);
            break;
        case 9: // ok ok
            //      - b9 t5/7: (service area / very dense area) This can be an offices building or a school
            //          - Footprint 800, max size
            //          - Height 15 m, up to 21m (7-storeys)
            aux.minHeight = 0.05f;
            aux.maxHeight = 0.10f;
            aux.minWidth  = 0.15f;
            aux.maxWidth  = 0.285f;
            aux.minDepth  = 0.15f;
            aux.maxDepth  = 0.285f;
            aux.hasRoof = false;
            bcList.push_back(aux);
            break;
        case 10: // ok ok
            //      - b10 t7: This can be offices (banks or whatever)
            //          - Footprint 4000, up to 600
            //          - Height 30m, max size
            aux.minHeight = 0.15f;
            aux.maxHeight = 0.30f;
            aux.minWidth  = 0.15f;
            aux.maxWidth  = 0.25f;
            aux.minDepth  = 0.15f;
            aux.maxDepth  = 0.25f;
            aux.hasRoof = false;
            bcList.push_back(aux);
            break;
        case 11: // ok ok
            //      - b11 t7 (very dense area)
            //          - Footprint 300m, up to 400m
            //          - Height 30m, max size
            aux.minHeight = 0.20f;
            aux.maxHeight = 0.42f;
            aux.minRadius = 0.30f;
            aux.maxRadius = 0.45f;
            aux.hasRoof = false;
            bcList.push_back(aux);
            
            isBox = false;
            break;
        case 12: // ok ok
            //      - b12 t6: It can either be residential or shops
            //          - Footprint 144m, up to 200m
            //          - Height 20m, max size
            aux.minHeight = 0.15f;
            aux.maxHeight = 0.20f;
            aux.minWidth  = 0.12f;
            aux.maxWidth  = 0.141f;
            aux.minDepth  = 0.10f;
            aux.maxDepth  = 0.141f;
            aux.hasRoof = false;
            bcList.push_back(aux);
            break;
        case 13: // ok ok
            //      - b13 t5: (Commercial activities and services)
            //          - This can be an hospital
            //          - Footprint 2025, max size
            //          - Height 33m, max size
            aux.minHeight = 0.20f;
            aux.maxHeight = 0.33f;
            aux.minWidth  = 0.10f;
            aux.maxWidth  = 0.45f;
            aux.minDepth  = 0.10f;
            aux.maxDepth  = 0.45f;
            aux.hasRoof = false;
            bcList.push_back(aux);
            break;
        case 14: // ok ok
            //      - b14 t5: (Commercial activities and services)
            //          - This can be a shopping centre
            //          - Footprint 27500, can be up to 3000
            //          - Height 10m, can be up to 20m (but then smaller footprint)
            aux.minHeight = 0.10f;
            aux.maxHeight = 0.20f;
            aux.minWidth  = 0.30f;
            aux.maxWidth  = 0.55f;
            aux.minDepth  = 0.30f;
            aux.maxDepth  = 0.55f;
            aux.hasRoof = false;
            bcList.push_back(aux);
            break;
        case 15: // ok ok
            //      - b15 t7 (very dense area)
            //          - This is type 7 building (very dense area)
            //          - Footprint 144, max 200
            //          - Height 42m, max size
            aux.minHeight = 0.25f;
            aux.maxHeight = 0.42f;
            aux.minWidth  = 0.10f;
            aux.maxWidth  = 0.12f;
            aux.minDepth  = 0.10f;
            aux.maxDepth  = 0.12f;
            aux.hasRoof = false;
            bcList.push_back(aux);
            break;
            
        default:
            break;
    }
    
    if(bcList.size() > 0)
    {
        float mult = 50;
        // generate building
        std::list<BuildingComponent>::iterator i;
        float scaleFactor = 0.5f;
        
        for(i=bcList.begin(); i != bcList.end(); ++i)
        {
            Color vColor;
            
            width  = ((float)rand()/RAND_MAX)*(aux.maxWidth-aux.minWidth)+aux.minWidth*scaleFactor;
            height = ((float)rand()/RAND_MAX)*(aux.maxHeight-aux.minHeight)+aux.minHeight*scaleFactor;
            depth  = ((float)rand()/RAND_MAX)*(aux.maxDepth-aux.minDepth)+aux.minDepth*scaleFactor;
            
//            printf("%d (%f,%f,%f)\n", type, width, depth, height);
//            printf("(%f,%f,%f)\n", width, depth, height);
            
            float rad = sqrt(width/2*width/2 + depth/2*depth/2);
            
            if(rad > maxRadius)
                maxRadius = rad;
            
            if(isBox == true)
            {
                Vertex v1, v2, v3, v4;
                UV uv;
                
                aux = *i;
                
                v1.position[0] = 0.0f;
                v1.position[1] = 0.0f;
                v1.position[2] = 0.0f;
                
                uv.u = 0;
                uv.v = 0;
                uvList.push_back(uv);
                
                v2.position[0] = width;
                v2.position[1] = 0.0f;
                v2.position[2] = 0.0f;
                
                uv.u = -roundNum(width*mult);
                uv.v = 0;
                uvList.push_back(uv);
                
                v3.position[0] = width;
                v3.position[1] = depth;
                v3.position[2] = 0.0f;
                
                uv.u = 0;
                uv.v = 0;
                uvList.push_back(uv);
                
                v4.position[0] = 0.0f;
                v4.position[1] = depth;
                v4.position[2] = 0.0f;
                
                uv.u = -roundNum(depth*mult);
                uv.v = 0;
                uvList.push_back(uv);
                
                vertexList.push_back(v1);
                vertexList.push_back(v2);
                vertexList.push_back(v3);
                vertexList.push_back(v4);
                
                aux.color = glm::vec3((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX);
                vColor.color[0] = aux.color.x;
                vColor.color[1] = aux.color.y;
                vColor.color[2] = aux.color.z;
                colorList.push_back(vColor);
                
                aux.color = glm::vec3((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX);
                vColor.color[0] = aux.color.x;
                vColor.color[1] = aux.color.y;
                vColor.color[2] = aux.color.z;
                colorList.push_back(vColor);
                aux.color = glm::vec3((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX);
                vColor.color[0] = aux.color.x;
                vColor.color[1] = aux.color.y;
                vColor.color[2] = aux.color.z;
                colorList.push_back(vColor);
                aux.color = glm::vec3((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX);
                vColor.color[0] = aux.color.x;
                vColor.color[1] = aux.color.y;
                vColor.color[2] = aux.color.z;
                colorList.push_back(vColor);
                
                v1.position[2] = height;
                v2.position[2] = height;
                v3.position[2] = height;
                v4.position[2] = height;
                
                vertexList.push_back(v1);
                uv.u = 0;
                uv.v = -roundNum(height*mult);
                uvList.push_back(uv);
                
                vertexList.push_back(v2);
                uv.u = -roundNum(width*mult);
                uv.v = -roundNum(height*mult);
                uvList.push_back(uv);
                
                vertexList.push_back(v3);
                uv.u = 0;
                uv.v = -roundNum(height*mult);
                uvList.push_back(uv);
                
                vertexList.push_back(v4);
                uv.u = -roundNum(depth*mult);
                uv.v = -roundNum(height*mult);
                uvList.push_back(uv);
                
                aux.color = glm::vec3((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX);
                vColor.color[0] = aux.color.x;
                vColor.color[1] = aux.color.y;
                vColor.color[2] = aux.color.z;
                colorList.push_back(vColor);
                aux.color = glm::vec3((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX);
                vColor.color[0] = aux.color.x;
                vColor.color[1] = aux.color.y;
                vColor.color[2] = aux.color.z;
                colorList.push_back(vColor);
                aux.color = glm::vec3((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX);
                vColor.color[0] = aux.color.x;
                vColor.color[1] = aux.color.y;
                vColor.color[2] = aux.color.z;
                colorList.push_back(vColor);
                aux.color = glm::vec3((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX);
                vColor.color[0] = aux.color.x;
                vColor.color[1] = aux.color.y;
                vColor.color[2] = aux.color.z;
                colorList.push_back(vColor);
                
                indexList.push_back(lastIndex+0);
                indexList.push_back(lastIndex+5);
                indexList.push_back(lastIndex+1);
                
                indexList.push_back(lastIndex+0);
                indexList.push_back(lastIndex+4);
                indexList.push_back(lastIndex+5);
                
                indexList.push_back(lastIndex+1);
                indexList.push_back(lastIndex+6);
                indexList.push_back(lastIndex+2);
                
                indexList.push_back(lastIndex+1);
                indexList.push_back(lastIndex+5);
                indexList.push_back(lastIndex+6);
                
                indexList.push_back(lastIndex+2);
                indexList.push_back(lastIndex+7);
                indexList.push_back(lastIndex+3);
                
                indexList.push_back(lastIndex+2);
                indexList.push_back(lastIndex+6);
                indexList.push_back(lastIndex+7);
                
                indexList.push_back(lastIndex+0);
                indexList.push_back(lastIndex+3);
                indexList.push_back(lastIndex+7);
                
                indexList.push_back(lastIndex+0);
                indexList.push_back(lastIndex+7);
                indexList.push_back(lastIndex+4);
                
                if(0)  // aux.hasRoof == true)
                {
                    aux.color = glm::vec3(177.0f/255.0f,129.0f/255.0f,108.0f/255.0f);
                    
                    vColor.color[0] = aux.color.x;
                    vColor.color[1] = aux.color.y;
                    vColor.color[2] = aux.color.z;
                    
                    v1.position[0] = width/2.0f;
                    v1.position[1] = depth/2.0f;
                    v1.position[2] = height+0.02f;
                    
                    vertexList.push_back(v1);
                    aux.color = glm::vec3((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX);
                    vColor.color[0] = aux.color.x;
                    vColor.color[1] = aux.color.y;
                    vColor.color[2] = aux.color.z;
                    colorList.push_back(vColor);
                    
                    indexList.push_back(lastIndex+4);
                    indexList.push_back(lastIndex+8);
                    indexList.push_back(lastIndex+5);
                    
                    indexList.push_back(lastIndex+5);
                    indexList.push_back(lastIndex+8);
                    indexList.push_back(lastIndex+6);
                    
                    indexList.push_back(lastIndex+6);
                    indexList.push_back(lastIndex+8);
                    indexList.push_back(lastIndex+7);
                    
                    indexList.push_back(lastIndex+7);
                    indexList.push_back(lastIndex+8);
                    indexList.push_back(lastIndex+4);
                    
                    lastIndex += 9;
                    numTriangles += 43;
                }
                else
                {
                    indexList.push_back(lastIndex+4);
                    indexList.push_back(lastIndex+6);
                    indexList.push_back(lastIndex+5);
                    
                    indexList.push_back(lastIndex+4);
                    indexList.push_back(lastIndex+7);
                    indexList.push_back(lastIndex+6);
                    
                    lastIndex += 8;
                    
                    numTriangles += 36;
                }
            }
        }
    }
    radius = maxRadius;
//    printf("mr: %f\n", maxRadius);
    buildVAO();
}

void Building::buildVAO()
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
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // buffer for vertex colors
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color) * colorList.size(), &colorList[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(ATTRIB_COLOR);
    glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UV) * uvList.size(), &uvList[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(ATTRIB_TEX);
    glVertexAttribPointer(ATTRIB_TEX, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    // unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}