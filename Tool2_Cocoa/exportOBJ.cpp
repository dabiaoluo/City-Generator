//
//  exportOBJ.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 05/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "exportOBJ.h"
#include "Engine.h"
#include "Building.h"
#include "Renderer.h"
#include "ModelComponent.h"

extern Engine* engine;

exportOBJ::exportOBJ()
{
    
}

void exportOBJ::exportBuildingsToFile(const char *file)
{
    std::list<Building*>::iterator i;
    
    int vCount = 1; // count all the vertices inserted until now
    int bCount = 1;
    
    NSString *filepath = @"~/Desktop/Buildings.obj";
    filepath = [filepath stringByExpandingTildeInPath];
    
    FILE *f = fopen([filepath UTF8String], "w");
    
    for(i=engine->buildingList.begin(); i != engine->buildingList.end(); ++i)
    {
        int bvCount = 0; // count number of builing vertices
        Building* building = *i;
        
        fprintf(f, "o Building%d\n", bCount++);
        
        glm::mat4 objMatrix(1.0f);
        objMatrix = glm::translate(objMatrix, glm::vec3(building->position.x, building->position.y, building->position.z));
        objMatrix = glm::rotate(objMatrix, building->rotation, glm::vec3(0,0,1.0f));
        objMatrix = glm::translate(objMatrix, glm::vec3(-building->width/2, -building->depth/2, building->position.z));
        
        for(int j=0;j<building->vertexList.size();j++)
        {
            bvCount++;
            glm::vec4 pos(building->vertexList[j].position[0], building->vertexList[j].position[1], building->vertexList[j].position[2], 1.0f);
            pos = objMatrix * pos;
            fprintf(f, "v %f %f %f\n", pos[0], -pos[2], -pos[1]);
        }
        
        for(int j=0;j<building->indexList.size();j++)
        {
            if(j%3 == 0)
                fprintf(f, "f ");
            fprintf(f, "%d ", building->indexList[j]+vCount);
            if((j+1)%3 == 0)
                fprintf(f, "\n");
        }
        vCount+= bvCount;
    }
    fclose(f);
}