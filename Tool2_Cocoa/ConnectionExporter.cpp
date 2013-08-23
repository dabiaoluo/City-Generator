//
//  ConnectionExporter.cpp
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 14/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "ConnectionExporter.h"
#include "Connection.h"
#include <list>
#include "Engine.h"
#include "Road.h"


extern Engine* engine;

ConnectionExporter::ConnectionExporter()
{
    
}

void ConnectionExporter::connectRoads()
{
    
    std::list<RoadVertex*>::iterator i;
    std::list<Road*>::iterator j, k;
    for(i=engine->nodeList.begin(); i != engine->nodeList.end(); ++i)
    {
        RoadVertex *aux = *i;
//        printf("in: %zd, out: %zd\n",aux->roadIn.size(), aux->roadOut.size());
        for(j=aux->roadIn.begin();j!=aux->roadIn.end();++j)
        {
            for(k=aux->roadOut.begin();k!=aux->roadOut.end();++k)
            {
//                if(aux->roadIn.size() == 2 && aux->roadOut.size() == 2)
//                {
//                    if((*j)->direction == (*k)->direction)
//                    {
//                        Connection *c = new Connection();
//                        c->from = *j;
//                        c->to   = *k;
//                        engine->connectionList.push_back(c);
//                    }
//                }
//                else
//                {
//                    Connection *c = new Connection();
//                    c->from = *j;
//                    c->to   = *k;
//                    engine->connectionList.push_back(c);
//                }
//                if((*j)->direction == (*k)->direction)
                {
                    Connection *c = new Connection();
                    c->from = *j;
                    c->to   = *k;
                    engine->connectionList.push_back(c);
                }
            }
        }
    }
    
//    for(i=a->roadIn.begin(); i != a->roadIn.end(); ++i)
//    {
//        // loop through roads AB created now
//        // create link at A between road IN and road AB created now
//        Connection *c = new Connection();
//        c->from = *i;
//        c->to   = roadAB;
//        engine->connectionList.push_back(c);
//    }
//    // loop through all roads OUT at vertex A
//    for(i=a->roadOut.begin(); i != a->roadOut.end(); ++i)
//    {
//        // create link at A between road OUT and road BA created now
//        Connection *c = new Connection();
//        c->from = roadBA;
//        c->to   = *i;
//        engine->connectionList.push_back(c);
//    }
//    
//    // loop through all roads IN at vertex B
//    for(i=b->roadIn.begin(); i != b->roadIn.end(); ++i)
//    {
//        // create link at B between road IN and road BA created now
//        Connection *c = new Connection();
//        c->from = *i;
//        c->to   = roadBA;
//        engine->connectionList.push_back(c);
//    }
//    // loop through all roads OUT at vertex B
//    for(i=a->roadOut.begin(); i != a->roadOut.end(); ++i)
//    {
//        // create link at B between road OUT and road AB created now
//        Connection *c = new Connection();
//        c->from = roadAB;
//        c->to   = *i;
//        engine->connectionList.push_back(c);
//    }
}

void ConnectionExporter::exportToFile(const char *file)
{
    this->connectRoads();
    NSString *folderPath = [[NSString stringWithFormat:@"~/Desktop/SUMO"] stringByExpandingTildeInPath];
    printf("Creating folder %s\n", [folderPath UTF8String]);
    
    NSFileManager *fm = [[NSFileManager alloc] init];
    
    NSError *e = NULL;
    [fm createDirectoryAtPath:folderPath withIntermediateDirectories:YES attributes:nil error:&e];
    
    NSString *filepath = [NSString stringWithFormat:@"~/Desktop/SUMO/%s", file];
    
    
    filepath = [filepath stringByExpandingTildeInPath];
    
    FILE *f = fopen([filepath UTF8String], "w");
    
    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(f, "<connections xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://sumo.sf.net/xsd/connections_file.xsd\">\n");
    
    std::list<Connection*>::iterator i;

    for(i=engine->connectionList.begin(); i != engine->connectionList.end(); ++i)
    {
        Connection *aux = *i;
        for(int n=0;n<aux->from->lanes;n++)
        {
            for(int m=0;m<aux->to->lanes;m++)
            {
                fprintf(f, "    <connection from=\"%s\" to=\"%s\" fromLane=\"%d\" toLane=\"%d\"/>\n", aux->from->name.str().c_str(), aux->to->name.str().c_str(), n, m);
            }
        }
    }
    fprintf(f, "</connections>\n");
    
    fclose(f);
}