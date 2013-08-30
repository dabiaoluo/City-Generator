//
//  BuildingFactory.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 28/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "BuildingFactory.h"
#include "Engine.h"
#include "utils.h"

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
        

        
        if(engine->componentMap[d.getIdentifier()].line != NULL)
        {
            ModelLine* ml = engine->componentMap[d.getIdentifier()].line;
            glm::vec3 pa;
            glm::vec3 pb;
            
            pa = glm::vec3(ml->a.x, ml->a.y, ml->a.z);
            pb = glm::vec3(ml->b.x, ml->b.y, ml->b.z);
            
            Color c;
            
            c.color[0] = 0;
            c.color[1] = 1;
            c.color[2] = 0;
            
            engine->r->colorList[ml->colorIndex] = c;
            engine->r->colorList[ml->colorIndex+1] = c;
            
            engine->r->updateColors();
            
//            float dist = Utils::distPointLine(pa, pb, b->position);
            float dist = Utils::distPointLine2(b->position, pa, pb);
//            printf("D: %f\n", dist);

            if(dist < buildingRadius)
            {
                canBuild = false;
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
//    glm::vec3 lim_min = engine->scene_min;
//    glm::vec3 lim_max = engine->scene_max;
//    
//    float pX, pY;
    
//    for(int i=0;i<numBuildings;i++)
//    {
//        pX = ((float)rand()/RAND_MAX)*(lim_max.x-lim_min.x)+lim_min.x;
//        pY = ((float)rand()/RAND_MAX)*(lim_max.y-lim_min.y)+lim_min.y;
////        printf("Random coords: (%f, %f)\n", pX, pY);
//    }
}

void BuildingFactory::createBuildingsOfType(float radius, int numBuildings, int type)
{
    this->point = glm::vec3(engine->cursorPos.x, engine->cursorPos.y, 0.0f);
    this->radius = radius;
    this->numBuildings = numBuildings;
    
    glm::vec3 lim_min = engine->scene_min;
    glm::vec3 lim_max = engine->scene_max;
    
    
    //    if(point.x >= lim_max.x || point.x <= lim_min.x || point.y >= lim_max.y || point.y <= lim_min.y)
    //        return;
    
    for(int i=0;i<numBuildings;i++)
    {
        float t = 2.0f*M_PI*((float)rand()/RAND_MAX);
        float rad = radius*((float)rand()/RAND_MAX);
        
        glm::vec3 p(rad*cos(t)+point.x, rad*sin(t)+point.y, 0.0f);
        
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
                bType = t2[((int)rand())%sizeof(t2)/sizeof(int)];
                break;
            case 3:
                bType = t3[0];
                break;
            case 4:
                bType = t4[((int)rand())%sizeof(t4)/sizeof(int)];
                break;
            case 5:
                bType = t5[((int)rand())%sizeof(t5)/sizeof(int)];
                break;
            case 6:
                bType = t6[((int)rand())%sizeof(t6)/sizeof(int)];
                break;
            case 7:
                bType = t7[((int)rand())%sizeof(t7)/sizeof(int)];
                break;
                
            default:
                bType = 1;
        }
        
        //            printf("Type: %d\n", bType);
        //            printf("Rand: %ld\n", ((int)rand())%sizeof(t7)/sizeof(int));
        
        currBuilding->generate(bType);
//        printf("R: %f\n", currBuilding->radius);
        
        p1[0] = p.x-currBuilding->radius;
        p1[1] = p.y-currBuilding->radius;
        
        p2[0] = p.x+currBuilding->radius;
        p2[1] = p.y+currBuilding->radius;
        
        Region r = Region(p1, p2, 2);
        
        engine->tree->intersectsWithQuery(r, qcb);
        
        if(qcb.canBuild == true)
        {
            id_type id = engine->getNextIdentifier();
            
            engine->componentMap[id].line = NULL;
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
}


float BuildingFactory::distancePoints(glm::vec3 a, glm::vec3 b)
{
    return glm::distance(a, b);
}
