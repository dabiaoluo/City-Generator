//
//  BuildingFactory.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 28/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "BuildingFactory.h"
#include "Engine.h"

extern Engine* engine;

using namespace SpatialIndex;


class BuildingQueryCallback : public IVisitor
{
public:
    BuildingFactory* bf;
    bool canBuild;
    
    BuildingQueryCallback(BuildingFactory *bf)
    {
        this->bf = bf;
        canBuild = true;
    }

	void visitNode(const INode& n) {}
    
	void visitData(const IData& d)
	{
        if(canBuild == false)
            return;
        Building* b = bf->currBuilding;
        float buildingRadius = b->radius;
        
        if(engine->componentMap[d.getIdentifier()].modelComponent != NULL)
        {
            ModelComponent* mc = engine->componentMap[d.getIdentifier()].modelComponent;
            mc->repaint(glm::vec3(0,255,0));
            glm::vec3 pa;
            glm::vec3 pb;
            
            if(mc->vertexList.size() == 1) // just a point
            {
                pa = glm::vec3(mc->vertexList[0].position[0], mc->vertexList[0].position[1], 0.0f);
                float dist = bf->distancePoints(bf->point, pa);
                if(dist < buildingRadius)
                    canBuild = false;
            }
            else // line list
            {
                pa = glm::vec3(mc->vertexList[0].position[0], mc->vertexList[0].position[1], 0.0f);
                mc->colorList[0].color[0] = 255;
                mc->colorList[0].color[1] = 255;
                mc->colorList[0].color[2] = 255;
                
                mc->updateColors();
                
                for(int i=1;i<mc->vertexList.size();i++)
                {
                    mc->colorList[i].color[0] = 255;
                    mc->colorList[i].color[1] = 255;
                    mc->colorList[i].color[2] = 255;
                    
                    mc->updateColors();
                    
                    pb = glm::vec3(mc->vertexList[i].position[0], mc->vertexList[i].position[1], 0.0f);
                    float dist = Utils::distPointLine(pa, pb, b->position);
//                    printf("Dist: %f\n", dist);
                    dist = Utils::distPointLine2(b->position, pa, pb);
//                    printf("Dist: %f\n", dist);
                    if(dist < buildingRadius)
                    {
                        canBuild = false;
                        break;
                    }
                    
                    pa = pb;
                }
            }
        }
        if(engine->componentMap[d.getIdentifier()].building != NULL)
        {
            Building* otherBuilding = engine->componentMap[d.getIdentifier()].building;
            float dist = glm::distance(b->position, otherBuilding->position);
            if(dist < b->radius + otherBuilding->radius)
            {
                canBuild = false;
            }

        }
//        printf("Can? %x\n", canBuild);
	}
    
	void visitData(std::vector<const IData*>& v) {}
};

BuildingFactory::BuildingFactory()
{
}

void BuildingFactory::createBuildingRandomPlace(int numBuildings)
{
    glm::vec3 lim_min = engine->scene_min;
    glm::vec3 lim_max = engine->scene_max;
    
    float pX, pY;
    
    for(int i=0;i<numBuildings;i++)
    {
        pX = ((float)rand()/RAND_MAX)*(lim_max.x-lim_min.x)+lim_min.x;
        pY = ((float)rand()/RAND_MAX)*(lim_max.y-lim_min.y)+lim_min.y;
//        printf("Random coords: (%f, %f)\n", pX, pY);
    }
}

void BuildingFactory::createBuildingsOfType(float radius, int numBuildings, int type)
{
    this->point = glm::vec3(engine->cursorPos.x, engine->cursorPos.y, 0.0f);
    this->radius = radius;
    this->numBuildings = numBuildings;
    
    glm::vec3 lim_min = engine->scene_min;
    glm::vec3 lim_max = engine->scene_max;
    
    
    if(point.x >= lim_max.x || point.x <= lim_min.x || point.y >= lim_max.y || point.y <= lim_min.y)
        return;
    
    for(int i=0;i<numBuildings;i++)
    {
        float t = 2.0f*M_PI*((float)rand()/RAND_MAX);
        float r = radius*((float)rand()/RAND_MAX);
        
        glm::vec3 p(r*cos(t)+point.x, r*sin(t)+point.y, 0.0f);
        
        if(p.x >= lim_min.x && p.x <= lim_max.x && p.y >= lim_min.y && p.y <= lim_max.y)
        {
            // query
            BuildingQueryCallback qcb(this);
            
            double p1[2], p2[2];
            
            
            currBuilding = new Building();
            currBuilding->position.x = p.x;
            currBuilding->position.y = p.y;
            currBuilding->position.z = 0.0f;
            
            
            // t2: 1 3 7
            // t3: 2
            // t4: 4 5 8
            // t5: 9 13 14
            // t6: 2 6 12
            // t7: 9 10 11 15
            
            int t2[] = {1, 2, 3, 7};
            int t3[] = {};
            int t4[] = {4, 5, 8};
            int t5[] = {9, 13, 14};
            int t6[] = {2, 6, 12};
            int t7[] = {9, 10, 11, 15};
            
            int bType = 0;
            
            switch (type) {
                case 2:
                    bType = t2[(int)rand()%sizeof(t2)];
                    break;
                case 3:
                    bType = t3[0];
                    break;
                case 4:
                    bType = t4[(int)rand()%sizeof(t4)];
                    break;
                case 5:
                    bType = t5[(int)rand()%sizeof(t5)];
                    break;
                case 6:
                    bType = t6[(int)rand()%sizeof(t6)];
                    break;
                case 7:
                    bType = t7[(int)rand()%sizeof(t7)];
                    
                    break;
                    
                default:
                    bType = 1;
            }
            
            printf("Type: %d\n", bType);
            
            currBuilding->generate(bType);
            
            p1[0] = p.x-currBuilding->radius;
            p1[1] = p.y-currBuilding->radius;
            
            p2[0] = p.x+currBuilding->radius;
            p2[1] = p.y+currBuilding->radius;
            
            Region r = Region(p1, p2, 2);
            
            engine->tree->intersectsWithQuery(r, qcb);
//            printf("#####################\n");
            
            if(qcb.canBuild == true)
            {
                id_type id = engine->getNextIdentifier();
                
                engine->componentMap[id].modelComponent = NULL;
                engine->componentMap[id].building       = currBuilding;
                
                engine->tree->insertData(0, 0, r, id);
//                engine->cubeList.push_back(p);
                engine->buildingList.push_back(currBuilding);
            }
            
//            double p1[2], p2[2];
//            id_type id = engine->getNextIdentifier();
//            
//            p1[0] = p.x-radius;
//            p1[1] = p.y-radius;
//            
//            p2[0] = p.x+radius;
//            p2[1] = p.y+radius;
//
//            Building *building = new Building();
//            
//            building->position.x = p.x;
//            building->position.y = p.y;
//            building->position.z = 0.0f;
//
//            engine->componentMap[id].modelComponent = NULL;
//            engine->componentMap[id].building       = building;
//            
//            Region r = Region(p1, p2, 2);
//            
//            engine->tree->insertData(0, 0, r, id);
//            engine->cubeList.push_back(p);
        }
        else
        {
            i--;
        }
    }
}


float BuildingFactory::distancePoints(glm::vec3 a, glm::vec3 b)
{
    return glm::distance(a, b);
}
