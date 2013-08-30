#include "TestCreationClass.h"

#include <iostream>
#include <stdio.h>
#include "spatialindex/SpatialIndex.h"
#include "ModelLine.h"

extern Engine* engine;
using namespace SpatialIndex;

Test_CreationClass::Test_CreationClass()
{
    
}

void Test_CreationClass::addLayer(const DL_LayerData& data)
{
    if ( engine->layerMap.find(data.name) == engine->layerMap.end() )
    {
        Layer* newLayer = new Layer(data.name.c_str(), data.flags, attributes.getColor());
        engine->layerMap[data.name] = newLayer;
    }
    else
    {
        // already exist
    }
}

void Test_CreationClass::addPoint(const DL_PointData& data)
{
}

void Test_CreationClass::addLine(const DL_LineData& data)
{
//    double p1[2], p2[2];
//    id_type id = engine->getNextIdentifier();
//    
//    p1[0] = data.x1;
//    p1[1] = data.y1;
//    
//    p2[0] = data.x2;
//    p2[1] = data.y2;
//    
//    LineSegment line = LineSegment(p1, p2, 2);
//    
//    engine->tree->insertData(0, 0, line, id);
//    
//    ModelComponent* mc = new ModelComponent();
//    
//    engine->componentMap[id].building = NULL;
    
//    mc->type = 0;
//    mc->layer = engine->layerMap[attributes.getLayer()];
//    
//    mc->insertVertex(data.x1, data.y1, data.z1);
//    mc->insertVertex(data.x2, data.y2, data.z2);
    
    ModelLine *ml = new ModelLine();
    ml->a = glm::vec3(data.x1, data.y1, data.z1);
    ml->b = glm::vec3(data.x2, data.y2, data.z2);
    ml->layer = engine->layerMap[attributes.getLayer()];
    engine->lineList.push_back(ml);
    
//    engine->componentMap[id].line = mc;

//    engine->mf->pushComponent(mc);
}

void Test_CreationClass::addArc(const DL_ArcData& data)
{
}

void Test_CreationClass::addCircle(const DL_CircleData& data)
{
}

void Test_CreationClass::addPolyline(const DL_PolylineData& data)
{
    
    engine->lastVertex = -1;
}

void Test_CreationClass::addVertex(const DL_VertexData& data)
{
    if(attributes.getLayer().c_str()[2] == 'a')
    {
        if(engine->lastVertex != -1)
        {
            ModelLine *ml = new ModelLine();
            ml->a = glm::vec3(engine->lastVertexPos.x, engine->lastVertexPos.y, engine->lastVertexPos.z);
            ml->b = glm::vec3(data.x, data.y, data.z);
            engine->lineList.push_back(ml);

            engine->lastVertexPos = glm::vec3(data.x, data.y, data.z);
        }
        else
        {
            engine->lastVertex = 0;
            engine->lastVertexPos = glm::vec3(data.x, data.y, data.z);
        }
    }

    
    
//    ModelComponent* mc = engine->mf->getCurrComponent();
//    mc->type = 1;
//    mc->layer = engine->layerMap[attributes.getLayer()];
//    mc->insertVertex(data.x, data.y, data.z);
}


void Test_CreationClass::add3dFace(const DL_3dFaceData& data)
{
}


void Test_CreationClass::printAttributes()
{
    printf("  Attributes: Layer: %s, ", attributes.getLayer().c_str());
    printf(" Color: ");
    if (attributes.getColor()==256)	{
        printf("BYLAYER");
    } else if (attributes.getColor()==0) {
        printf("BYBLOCK");
    } else {
        printf("%d", attributes.getColor());
    }
    printf(" Width: ");
    if (attributes.getWidth()==-1) {
        printf("BYLAYER");
    } else if (attributes.getWidth()==-2) {
        printf("BYBLOCK");
    } else if (attributes.getWidth()==-3) {
        printf("DEFAULT");
    } else {
        printf("%d", attributes.getWidth());
    }
    printf(" Type: %s\n", attributes.getLineType().c_str());
}
