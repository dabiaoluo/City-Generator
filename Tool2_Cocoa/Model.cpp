//
//  Model.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 21/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "Model.h"

enum {vertexLoc, normalLoc, texCoordLoc};

Model::Model()
{
    model_min.x = 999999999;
    model_min.x = 999999999;
    model_min.x = 999999999;
    
    model_max.x = -999999999;
    model_max.x = -999999999;
    model_max.x = -999999999;
}

void Model::buildVAO()
{
    std::list<ModelComponent*>::iterator i;
    
    for(i=componentList.begin(); i != componentList.end(); ++i)
    {
        ModelComponent* aux = (ModelComponent*) *i;
        aux->buildVAO();
    }

}

void Model::addComponent(ModelComponent *mc)
{
//    componentList.
    componentList.push_back(mc);
//    printf("Added component!\n");
}

void Model::calculateBounds()
{
    std::list<ModelComponent*>::iterator i;
    
    
    for(i=componentList.begin(); i != componentList.end(); ++i)
    {
        ModelComponent* aux = (ModelComponent*) *i;
        if(aux->component_min.x < model_min.x)
        {
            model_min.x = aux->component_min.x;
        }
        if(aux->component_min.y < model_min.y)
        {
            model_min.y = aux->component_min.y;
        }
        if(aux->component_min.z < model_min.z)
        {
            model_min.z = aux->component_min.z;
        }
        
        if(aux->component_max.x > model_max.x)
        {
            model_max.x = aux->component_max.x;
        }
        if(aux->component_max.y > model_max.y)
        {
            model_max.y = aux->component_max.y;
        }
        if(aux->component_max.z > model_max.z)
        {
            model_max.z = aux->component_max.z;
        }
    }
}