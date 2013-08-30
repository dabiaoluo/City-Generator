//
//  Engine.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 27/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "Engine.h"

using namespace SpatialIndex;



Engine::Engine()
{
    lastIdentifier = 0;
    lastRoadID = 0;
    lastNodeID = 0;
    lastVertex = -1;
    
    e = new EventHandler();
    r  = new Renderer();
    
    mainMenu = new MainMenu();
    
    id_type indexIdentifier;
    
    memfile = StorageManager::createNewMemoryStorageManager();
    
    unsigned int indxCap = 100;
    unsigned int leafCap = 100;
    
    cursorPos = glm::vec2(0.0f);
    
    tree = RTree::createNewRTree(*memfile, 0.7, indxCap, leafCap, 2, SpatialIndex::RTree::RV_RSTAR, indexIdentifier);
    
    memfile = StorageManager::createNewMemoryStorageManager();
    
    roadTree = RTree::createNewRTree(*memfile, 0.7, indxCap, leafCap, 2, SpatialIndex::RTree::RV_RSTAR, indexIdentifier);
    
    bf = new BuildingFactory();
    
    sf = new SurfaceFactory();
    sfInitialized = false;
    
    tl = new TextureLoader();
}

void Engine::loadTexture(const char *file)
{
    string txPath = [[[NSBundle mainBundle] resourcePath] UTF8String];
    txPath.append("/Textures/");
    
    Texture *tx = tl->loadTexture(txPath.c_str(), file);
    textureList.push_back(tx);
}

void Engine::setup()
{
    r->setupSDL_GL();
    
    r->loadVAO();
}

int64_t Engine::getNextIdentifier()
{
    return lastIdentifier++;
}
