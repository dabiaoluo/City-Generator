//
//  Engine.h
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 27/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2__Engine__
#define __Tool2__Engine__

#include <iostream>
#include "Model.h"
#include "ModelFactory.h"
#include "Renderer.h"
#include <list>
#include <map>
#include <string>
#include "spatialindex/SpatialIndex.h"
#include "EventHandler.h"
#include "BuildingFactory.h"
#include "Building.h"
#include "SurfaceFactory.h"
#include "MainMenu.h"

struct PointerContainer
{
    ModelComponent* modelComponent;
    Building* building;
};

class Engine
{
public:
    Engine();
    void buildVAO();
    void setup();
    int64_t getNextIdentifier();
    void queryPoint();
    void calculateSceneBounds();
    
    ModelFactory *mf;
    Renderer *r;
    EventHandler *e;
    
    std::list<Model*> modelList;
    std::map<std::string, Layer*> layerMap;
    std::map<int64_t, PointerContainer> componentMap;
    
    SpatialIndex::IStorageManager* memfile;
    SpatialIndex::ISpatialIndex* tree;
    
    SurfaceFactory *sf;
    bool sfInitialized;
    
    BuildingFactory* bf;
    
    glm::vec3 scene_min, scene_max, scene_center;
    
    std::list<glm::vec3> cubeList;
    std::list<Building*> buildingList;

    
    int64_t lastIdentifier;
    
    glm::vec2 cursorPos;
    
    MainMenu *mainMenu;
};

#endif /* defined(__Tool2__Engine__) */
