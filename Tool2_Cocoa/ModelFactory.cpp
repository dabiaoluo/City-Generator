//
//  ModelFactory.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 27/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "ModelFactory.h"
#include "Engine.h"

extern Engine* engine;

ModelFactory::ModelFactory()
{
    currModel = NULL;
    currComponent = NULL;
    n = 0;
}


void ModelFactory::newModel()
{
    if(currModel == NULL)
    {
        currModel = new Model();
    }
    else
    {
        engine->modelList.push_back(currModel);
        currModel = new Model();
    }
}

void ModelFactory::pushComponent(ModelComponent* mc)
{
    if(currModel == NULL)
    {
        currModel = new Model();
    }
    if(currComponent == NULL)
    {
        currComponent = mc;
    }
    else
    {
        currModel->componentList.push_back(currComponent);
        currComponent = mc;
    }
}

void ModelFactory::pushCurrComponent()
{
    if(currComponent != NULL)
    {
        currModel->componentList.push_back(currComponent);
    }
}


void ModelFactory::newComponent()
{
    if(currModel == NULL)
    {
        currModel = new Model();
    }
    if(currComponent == NULL)
    {
        currComponent = new ModelComponent();
        n++;
    }
    else
    {
        currModel->componentList.push_back(currComponent);
        currComponent = new ModelComponent();
        n++;
    }
}

ModelComponent* ModelFactory::getCurrComponent()
{
    if(currModel == NULL)
    {
        currModel = new Model();
    }
    if(currComponent == NULL)
    {
        currComponent = new ModelComponent();
        n++;
    }
    return currComponent;
}

void ModelFactory::finish()
{
    currModel->componentList.push_back(currComponent);
    currComponent = NULL;
    engine->modelList.push_back(currModel);
    currModel = NULL;
    printf("Finished loading %d components\n", n);
}

