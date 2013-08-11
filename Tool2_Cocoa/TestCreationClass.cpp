#include "TestCreationClass.h"

#include <iostream>
#include <stdio.h>

extern Engine* engine;

Test_CreationClass::Test_CreationClass()
{
    
}

using namespace SpatialIndex;


void Test_CreationClass::addLayer(const DL_LayerData& data)
{
//    printf("LAYER: %s flags: %d\n", data.name.c_str(), data.flags);
    
    if ( engine->layerMap.find(data.name) == engine->layerMap.end() )
    {
        Layer* newLayer = new Layer(data.name.c_str(), data.flags, attributes.getColor());
        engine->layerMap[data.name] = newLayer;
    }
    else
    {
        // already exist
    }

//    printAttributes();
}

void Test_CreationClass::addPoint(const DL_PointData& data) {
    printf("POINT    (%6.3f, %6.3f, %6.3f)\n",
           data.x, data.y, data.z);
    printAttributes();
}

/**
 * Sample implementation of the method which handles line entities.
 */
void Test_CreationClass::addLine(const DL_LineData& data)
{
    double p1[2], p2[2];
    id_type id = engine->getNextIdentifier();
    
    p1[0] = data.x1;
    p1[1] = data.y1;
    
    p2[0] = data.x2;
    p2[1] = data.y2;
    
    LineSegment line = LineSegment(p1, p2, 2);
    
    engine->tree->insertData(0, 0, line, id);
    
//    printf("Inserted line [%lld]: (%f, %f), (%f, %f)\n", id, data.x1, data.y1, data.x2, data.y2);
    
    ModelComponent* mc = new ModelComponent();
    
    engine->componentMap[id].modelComponent = mc;
    engine->componentMap[id].building = NULL;
    
    mc->type = 0;
    mc->layer = engine->layerMap[attributes.getLayer()];
//    mc->color = glm::vec3(254,0,0);
    
    mc->insertVertex(data.x1, data.y1, data.z1);
    mc->insertVertex(data.x2, data.y2, data.z2);

    
    engine->mf->pushComponent(mc);
    
    
//    printf("LINE     (%6.3f, %6.3f, %6.3f) (%6.3f, %6.3f, %6.3f)\n",
//           data.x1, data.y1, data.z1, data.x2, data.y2, data.z2);
//    printAttributes();
}

/**
 * Sample implementation of the method which handles arc entities.
 */

//////////////////////////////////////////////////////////////////////////////UNHANDLED
void Test_CreationClass::addArc(const DL_ArcData& data) {
//    printf("ARC      (%6.3f, %6.3f, %6.3f) %6.3f, %6.3f, %6.3f\n",
//           data.cx, data.cy, data.cz,
//           data.radius, data.angle1, data.angle2);
//    printAttributes();
}

/**
 * Sample implementation of the method which handles circle entities.
 */
void Test_CreationClass::addCircle(const DL_CircleData& data) {
//    printf("CIRCLE   (%6.3f, %6.3f, %6.3f) %6.3f\n",
//           data.cx, data.cy, data.cz,
//           data.radius);
//    printAttributes();
}


/**
 * Sample implementation of the method which handles polyline entities.
 */
void Test_CreationClass::addPolyline(const DL_PolylineData& data) {
//    printf("NEW MODEL \n");
//    printf("flags: %d\n", (int)data.flags);
    
    engine->mf->newModel();
    engine->mf->newComponent();
    
//    printAttributes();
}


/**
 * Sample implementation of the method which handles vertices.
 */
void Test_CreationClass::addVertex(const DL_VertexData& data) {
//    printf("VERTEX\n");
    
    ModelComponent* mc = engine->mf->getCurrComponent();
    mc->type = 1;
    mc->layer = engine->layerMap[attributes.getLayer()];
    mc->insertVertex(data.x, data.y, data.z);
    
//    printAttributes();
}


void Test_CreationClass::add3dFace(const DL_3dFaceData& data) {
    printf("3DFACE\n");
    for (int i=0; i<4; i++) {
        printf("   corner %d: %6.3f %6.3f %6.3f\n",
               i, data.x[i], data.y[i], data.z[i]);
    }
    printAttributes();
}


void Test_CreationClass::printAttributes() {
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
