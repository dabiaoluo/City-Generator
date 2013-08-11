//
//  Engine.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 27/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "Engine.h"

using namespace SpatialIndex;

class MyVisitor : public IVisitor
{
public:
    Engine *engine;
	void visitNode(const INode& n) {}
    
	void visitData(const IData& d)
	{
        if(engine->componentMap[d.getIdentifier()].modelComponent != NULL)
        {
            engine->componentMap[d.getIdentifier()].modelComponent->repaint(glm::vec3(0,255,0));
        }
        if(engine->componentMap[d.getIdentifier()].building != NULL)
        {
            printf("id: %lld\n", d.getIdentifier());
        }
	}
    
	void visitData(std::vector<const IData*>& v) {}
};

Engine::Engine()
{
    lastIdentifier = 0;
    
    e = new EventHandler();
    
    mf = new ModelFactory();
    r  = new Renderer();
    
    mainMenu = new MainMenu();
    
    id_type indexIdentifier;
    
    memfile = StorageManager::createNewMemoryStorageManager();
    
    unsigned int indxCap = 10;
    unsigned int leafCap = 10;
    
    cursorPos = glm::vec2(0.0f);
    
    tree = RTree::createNewRTree(*memfile, 0.7, indxCap, leafCap, 2, SpatialIndex::RTree::RV_RSTAR, indexIdentifier);
    
    bf = new BuildingFactory();
    
    sf = new SurfaceFactory();
    sfInitialized = false;

    double plow[2], phigh[2];
    id_type id = 1;
    
    plow[0] = 0;
    plow[1] = 0;
    
    phigh[0] = 1;
    phigh[1] = 1;
    
    Region region = Region(plow, phigh, 2);
    
    tree->insertData(0, 0, region, id);

    
    plow[0] = 0.5;
    plow[1] = 0.5;
    
    phigh[0] = 1.5f;
    phigh[1] = 1.5f;
    
    id = 2;
    
    region = Region(plow, phigh, 2);
    
    tree->insertData(0, 0, region, id);
}

void Engine::buildVAO()
{
    
    std::list<Model*>::iterator i;

    for(i=modelList.begin(); i != modelList.end(); ++i)
    {
        Model* aux = (Model*) *i;
        aux->buildVAO();
        aux->calculateBounds();
    }
    calculateSceneBounds();

}

void Engine::setup()
{
    r->setupSDL_GL();
    
//    r->loadVAO();
}

int64_t Engine::getNextIdentifier()
{
    return lastIdentifier++;
}

void Engine::queryPoint()
{
    MyVisitor vis;
    vis.engine = this;
    double p0[2], p1[2], p[2];

    p[0] = cursorPos[0];
    p[1] = cursorPos[1];
    
    p0[0] = cursorPos[0]-0.1f;
    p0[1] = cursorPos[1]-0.1f;

    p1[0] = cursorPos[0]+0.1f;
    p1[1] = cursorPos[1]+0.1f;
    
//    printf("%lf, %lf\n", point[0], point[1]);
    
    SpatialIndex::Point point = SpatialIndex::Point(p, 2);
    Region r = Region(p0, p1, 2);
//    tree->nearestNeighborQuery(20, point, vis);
    tree->intersectsWithQuery(r, vis);
}


void Engine::calculateSceneBounds()
{
    std::list<Model*>::iterator i;
    
    
    for(i=modelList.begin(); i != modelList.end(); ++i)
    {
        Model* aux = (Model*) *i;
        if(aux->model_min.x < scene_min.x)
        {
            scene_min.x = aux->model_min.x;
        }
        if(aux->model_min.y < scene_min.y)
        {
            scene_min.y = aux->model_min.y;
        }
        if(aux->model_min.z < scene_min.z)
        {
            scene_min.z = aux->model_min.z;
        }
        
        if(aux->model_max.x > scene_max.x)
        {
            scene_max.x = aux->model_max.x;
        }
        if(aux->model_max.y > scene_max.y)
        {
            scene_max.y = aux->model_max.y;
        }
        if(aux->model_max.z > scene_max.z)
        {
            scene_max.z = aux->model_max.z;
        }
    }
    
    printf("Scene\n");
    printf("    min(%f, %f, %f)\n", scene_min.x, scene_min.y, scene_min.z);
    printf("    max(%f, %f, %f)\n", scene_max.x, scene_max.y, scene_max.z);
}
