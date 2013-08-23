#include "TestCreationClass.h"

#include <iostream>
#include <stdio.h>
#include "Road.h"
#include "RoadVertex.h"
#include "spatialindex/SpatialIndex.h"
#include "Connection.h"

extern Engine* engine;
using namespace SpatialIndex;

Test_CreationClass::Test_CreationClass()
{
    
}

class RoadQueryCallback : public IVisitor
{
public:
    std::list<RoadVertex*> nodeList;
    glm::vec2 point;
    
    RoadQueryCallback()
    {
        nodeList.clear();
    }
    void clear()
    {
        nodeList.clear();
    }
    
	void visitNode(const INode& n) {}
    
	void visitData(const IData& d)
	{
        clear();
//        printf("Querying for (%f, %f)\n", point.x, point.y);
        glm::vec2 otherPos = engine->nodeMap[d.getIdentifier()]->position;
//        printf("Found! d:%f query(%f, %f) found(%f, %f)\n", glm::distance(point, otherPos), point.x, point.y, otherPos.x, otherPos.y);
        
//        printf("Got          (%f, %f) %lld\n", otherPos.x, otherPos.y, d.getIdentifier());
        if(nodeList.size() > 0) // there is already a node on the list
        {
            printf("Distance: %f\n", glm::distance(point, otherPos));
            if(nodeList.back()->identifier != d.getIdentifier())
            {
                nodeList.push_back(engine->nodeMap[d.getIdentifier()]);
            }
        }
        else // found first node
        {
            nodeList.push_back(engine->nodeMap[d.getIdentifier()]);
        }
	}
    
	void visitData(std::vector<const IData*>& v) {}
};


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

void Test_CreationClass::insertRoad(glm::vec2 va, glm::vec2 vb)
{
//    RoadVertex *a = new RoadVertex(va);
//    RoadVertex *b = new RoadVertex(vb);
    RoadVertex *a;
    RoadVertex *b;
    
    double pv[2] = {va.x, va.y};
    
    double r1[2] = {va.x-0.001, va.y-0.001};
    double r2[2] = {va.x+0.001, va.y+0.001};
    
    SpatialIndex::Point p;
    Region r;
    
    RoadQueryCallback qcb;
    
    //////////////////////////////////// point A
    qcb.clear();
    p = SpatialIndex::Point(pv, 2);
    r = Region(r1, r2, 2);
    
    qcb.point = va;
//    printf("Querying for a(%f, %f)\n", pv[0], pv[1]);
    engine->roadTree->intersectsWithQuery(p, qcb);
    
    if(qcb.nodeList.size() == 0)
    {
//        printf("No results... inserting (%f, %f)\n", va.x, va.y);
        int64_t nodeID = engine->lastNodeID++;
        
        a = new RoadVertex(va);
        a->identifier = nodeID;
        
        engine->roadTree->insertData(0, 0, p, nodeID);
        engine->nodeMap[nodeID] = a;
        engine->nodeList.push_back(a);
//        printf("Inserted (%f, %f) %lld\n", va.x, va.y, nodeID);
    }
    else
    {
        if(qcb.nodeList.size() > 1)
        {
            std::list<RoadVertex*>::iterator i;
            for(i=qcb.nodeList.begin(); i != qcb.nodeList.end(); ++i)
            {
                RoadVertex *aux = *i;
                printf("V(%f, %f)\n", aux->position.x, aux->position.y);
            }
        }
        a = qcb.nodeList.back();
    }
    
    //////////////////////////////////// point B
    qcb.clear();
    
    pv[0] = vb.x; pv[1] = vb.y;
    
    r1[0] = vb.x-0.001;  r1[1] = vb.y-0.001;
    r2[0] = vb.x+0.001;  r2[1] = vb.y+0.001;
    
    p = SpatialIndex::Point(pv, 2);
    r = Region(r1, r2, 2);

    qcb.point = vb;
//    printf("Querying for b(%f, %f)\n", pv[0], pv[1]);
    engine->roadTree->intersectsWithQuery(p, qcb);
    
    if(qcb.nodeList.size() == 0)
    {
//        printf("No results... inserting (%f, %f)\n", vb.x, vb.y);
        int64_t nodeID = engine->lastNodeID++;
        
        b = new RoadVertex(vb);
        b->identifier = nodeID;
        
        engine->roadTree->insertData(0, 0, p, nodeID);
        engine->nodeMap[nodeID] = b;
        engine->nodeList.push_back(b);
//        printf("Inserted (%f, %f) %lld\n", vb.x, vb.y, nodeID);
    }
    else
    {
        if(qcb.nodeList.size() > 1)
        {
            std::list<RoadVertex*>::iterator i;
            for(i=qcb.nodeList.begin(); i != qcb.nodeList.end(); ++i)
            {
                RoadVertex *aux = *i;
                printf("V(%f, %f)\n", aux->position.x, aux->position.y);
            }
        }
        b = qcb.nodeList.back();
    }
    
    if(a == b)
    {
        printf("a(%f, %f) b(%f, %f)\n", va.x, va.y, vb.x, vb.y);
        return;
    }
    
    int roadsAB = 0;
    int roadsBA = 0;
    
    const char *r2x1 = "Road 2x1";
    const char *r2x2 = "Road 2x2";
    const char *r2x3 = "Road 2x3";
    

    
    Layer *l = engine->layerMap[attributes.getLayer()];
    
    l->name[9] = 0;
    
    if(strncmp(l->name, r2x1, 8) == 0)
    {
        roadsAB = 1;
        roadsBA = 1;
    }
    else if(strncmp(l->name, r2x2, 8) == 0)
    {
        roadsAB = 2;
        roadsBA = 2;
    }
    else if(strncmp(l->name, r2x3, 8) == 0)
    {
        roadsAB = 3;
        roadsBA = 3;
    }
    else
    {
        printf("Error! %s\n", l->name);
    }
    // create links (roads) between vertex A and B (add to temp IN and OUT lists at vertexes)
    
    Road* roadAB;
    roadAB = new Road();
    roadAB->a = a;
    roadAB->b = b;
    roadAB->lanes = roadsAB;
    roadAB->direction = false;
    
    roadAB->name << roadAB->a->name.str() << roadAB->b->name.str();
//    printf("Road: %s\n", roadAB->name.str().c_str());
    
//    a->tempOut.push_back(road);
//    b->tempIn.push_back(road);
    engine->RoadList.push_back(roadAB);
    
    Road* roadBA = new Road();
    roadBA->a = b;
    roadBA->b = a;
    roadBA->lanes = roadsBA;
    roadAB->direction = true;
    
    roadBA->name << roadBA->a->name.str() << roadBA->b->name.str();
//    printf("Road: %s\n", roadBA->name.str().c_str());
    
//    b->tempOut.push_back(road);
//    a->tempIn.push_back(road);
    engine->RoadList.push_back(roadBA);
    
    // loop through all roads IN at vertex A

    // add vertex temp lists to vertex IN and OUT lists
    a->roadIn.push_back(roadBA);
    a->roadOut.push_back(roadAB);
    
    b->roadIn.push_back(roadAB);
    b->roadOut.push_back(roadBA);
}

void Test_CreationClass::addLine(const DL_LineData& data)
{
    double p1[2], p2[2];
    id_type id = engine->getNextIdentifier();
    
    p1[0] = data.x1;
    p1[1] = data.y1;
    
    p2[0] = data.x2;
    p2[1] = data.y2;
    
    if(attributes.getLayer().c_str()[2] == 'a')
    {
        insertRoad(glm::vec2(p1[0],p1[1]), glm::vec2(p2[0],p2[1]));
    }
    
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
    
//    printf("%s\n", attributes.getLayer().c_str());
    engine->lastVertex = -1;
    
    engine->mf->newModel();
    engine->mf->newComponent();
    
//    printAttributes();
}


/**
 * Sample implementation of the method which handles vertices.
 */
void Test_CreationClass::addVertex(const DL_VertexData& data) {
//    printf("VERTEX\n");
    
    if(attributes.getLayer().c_str()[2] == 'a')
    {
        if(engine->lastVertex != -1)
        {
            insertRoad(engine->lastVertexPos, glm::vec2(data.x,data.y));
            engine->lastVertexPos = glm::vec2(data.x, data.y);
        }
        else
        {
            engine->lastVertex = 0;
            engine->lastVertexPos = glm::vec2(data.x, data.y);
        }
    }
    
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
