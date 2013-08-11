//
//  SurfaceFactory.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 04/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "SurfaceFactory.h"
#include "Engine.h"

using namespace SpatialIndex;

extern Engine* engine;

class SurfaceQueryCallback : public IVisitor
{
public:
    glm::vec3 point;
    glm::vec2 increment;
    
    bool intersect;
    std::list<glm::vec2> pointIntersection;
    
    SurfaceFactory* sf;
    
    SurfaceQueryCallback(SurfaceFactory* pointer)
    {
        sf = pointer;
    }
    
	void visitNode(const INode& n) {}
    
	void visitData(const IData& d)
	{
        if(engine->componentMap[d.getIdentifier()].modelComponent != NULL)
        {
            ModelComponent* mc = engine->componentMap[d.getIdentifier()].modelComponent;
//            mc->repaint(glm::vec3(0,255,0));
            glm::vec3 pa;
            glm::vec3 pb;
            
            if(mc->vertexList.size() == 1) // just a point
            {
//                pa = glm::vec3(mc->vertexList[0].position[0], mc->vertexList[0].position[1], 0.0f);
//                float dist = bf->distancePoints(bf->point, pa);
            }
            else // line list
            {
                pa = glm::vec3(mc->vertexList[0].position[0], mc->vertexList[0].position[1], 0.0f);
//                mc->colorList[0].color[0] = 255;
//                mc->colorList[0].color[1] = 255;
//                mc->colorList[0].color[2] = 255;
                
//                mc->updateColors();
                
                for(int i=1;i<mc->vertexList.size();i++)
                {
//                    mc->colorList[i].color[0] = 255;
//                    mc->colorList[i].color[1] = 255;
//                    mc->colorList[i].color[2] = 255;
                    
//                    mc->updateColors();
                    
                    pb = glm::vec3(mc->vertexList[i].position[0], mc->vertexList[i].position[1], 0.0f);
                    // pa pb is the line
                    glm::vec2 intersection(-1.0f, -1.0f);
                    
                    intersect = sf->get_line_intersection(glm::vec2(pa), glm::vec2(pb),
                                          glm::vec2(point), glm::vec2(point)+increment,
                                          &intersection);
                    if(intersect)
                    {
                        pointIntersection.push_back(glm::vec2(intersection.x, intersection.y));
                    }
                    pa = pb;
                }
            }
        }
	}
    
	void visitData(std::vector<const IData*>& v) {}
};


SurfaceFactory::SurfaceFactory()
{
    
}

void SurfaceFactory::setNextColor(Color *c)
{
    c->color[0] += 55.0f/255.0f;
    if(c->color[0] >= 255.0f/255.0f)
    {
        c->color[0] = 55.0f/255.0f;
        c->color[1] += 55.0f/255.0f;
    }
    if(c->color[1] >= 255.0f/255.0f)
    {
        c->color[1] = 55.0f/255.0f;
        c->color[2] += 55.0f/255.0f;
    }
    if(c->color[2] >= 255.0f/255.0f)
    {
        c->color[2] = 55.0f/255.0f;
    }
}

void SurfaceFactory::craftSurfaces()
{
    printf("Min (%f, %f, %f) Max (%f, %f, %f)\n",
           engine->scene_min.x, engine->scene_min.y, engine->scene_min.z,
           engine->scene_max.x, engine->scene_max.y, engine->scene_max.z);
    
    glm::vec3 p(engine->scene_min);
    SurfaceQueryCallback qcb(this);
    glm::vec2 increment;
    Vertex v;
    
    Color c;
    
    c.color[0] = 55;
    c.color[1] = 55;
    c.color[2] = 55;
    
    counter = 0;
    
    double p1[2], p2[2];
    float delta = 0.0001f;
    
    p.y += engine->scene_max.y/10.0f*3;
    
    while(p.y < engine->scene_max.y/10.0f*3.01f)
    {
        increment.x = delta;
        increment.y = 0.0f;
        
        c.color[0] = 55;
        c.color[1] = 55;
        c.color[2] = 55;
        
        while(p.x < engine->scene_max.x)
        {
            
            qcb.pointIntersection.clear();
            qcb.point.x = p.x; // set point on query
            qcb.point.y = p.y;
            
            qcb.increment = increment;
            
            p1[0] = p.x;
            p1[1] = p.y-0.0001f;
            
            p2[0] = p.x+increment.x; // line segment is an horizontal line
            p2[1] = p.y+increment.y+0.0001f;
            
            
            v.position[0] = p.x; // insert new point
            v.position[1] = p.y;
            
//            vertexList.push_back(v);
//            colorList.push_back(c);
//            indexList.push_back(counter++); // end insert new point
            
            Region r = Region(p1, p2, 2);
            
            engine->tree->intersectsWithQuery(r, qcb);
            
            if(qcb.pointIntersection.size() > 0)
            {
                std::list<glm::vec2>::iterator i;
                
                for(i=qcb.pointIntersection.begin(); i != qcb.pointIntersection.end(); ++i)
                {
                    glm::vec2 aux = (glm::vec2) *i;
                    
                    v.position[0] = aux.x;
                    v.position[1] = aux.y;
                    
                    this->setNextColor(&c);
                    
                    vertexList.push_back(v);
                    colorList.push_back(c);
                    indexList.push_back(counter++);
                }
            }
            
            p.x += delta; // increment point
            
        }
        
        p.y += delta; // increase y
        
        p.x = engine->scene_min.x; // put x back to beginning

        increment.x = 0.0f;
        increment.y = delta;
        
        c.color[0] = 55;
        c.color[1] = 55;
        c.color[2] = 55;
        
        while(p.x < engine->scene_max.x)
        {
            
            qcb.pointIntersection.clear();
            qcb.point.x = p.x; // set point on query
            qcb.point.y = p.y;
            
            qcb.increment = increment;
            
            p1[0] = p.x;
            p1[1] = p.y-0.0001f;
            
            p2[0] = p.x+increment.x; // line segment is an horizontal line
            p2[1] = p.y+increment.y+0.0001f;
            
            
            v.position[0] = p.x; // insert new point
            v.position[1] = p.y;
            
//            vertexList.push_back(v);
//            colorList.push_back(c);
//            indexList.push_back(counter++); // end insert new point
            
            Region r = Region(p1, p2, 2);
     
            engine->tree->intersectsWithQuery(r, qcb);
            
            if(qcb.pointIntersection.size() > 0)
            {
                std::list<glm::vec2>::iterator i;
                
                for(i=qcb.pointIntersection.begin(); i != qcb.pointIntersection.end(); ++i)
                {
                    glm::vec2 aux = (glm::vec2) *i;
                    
                    v.position[0] = aux.x;
                    v.position[1] = aux.y;
                    
                    this->setNextColor(&c);
                    
                    vertexList.push_back(v);
                    colorList.push_back(c);
                    indexList.push_back(counter++);
                }
            }
            
            p.x += delta; // increment point
        }
        printf("\rTotal: %f", p.y/engine->scene_max.y*100.0f);
    }
//    printf("\rDone");
    
}

bool SurfaceFactory::get_line_intersection(glm::vec2 p0, glm::vec2 p1,
                                           glm::vec2 p2, glm::vec2 p3,
                                           glm::vec2* i)
{
    glm::vec2 s1, s2;
    s1.x = p1.x - p0.x;
    s1.y = p1.y - p0.y;
    s2.x = p3.x - p2.x;
    s2.y = p3.y - p2.y;
    
//    printf("s1(%f, %f) s2(%f, %f)\n", s1.x, s1.y, s2.x, s2.y);
    
    float s, t;
    
    float div = (-s2.x * s1.y + s1.x * s2.y);
    if(div != 0)
    {
        s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / div;
        t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / div;
        
        if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
        {
//            float x, y;
            // Collision detected
            if (i->x != 0)
                i->x = p0.x + (t * s1.x);
            if (i->y != 0)
                i->y = p0.y + (t * s1.y);
            return true;
        }
   
    }
    return false; // No collision
}

void SurfaceFactory::buildVAO()
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
}