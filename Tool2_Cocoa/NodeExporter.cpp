//
//  NodeExporter.cpp
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 15/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "NodeExporter.h"
#include <list>
#include "RoadVertex.h"
#include "Engine.h"

extern Engine* engine;

NodeExporter::NodeExporter()
{
    
}

void NodeExporter::exportToFile(const char *file)
{
    NSString *folderPath = [[NSString stringWithFormat:@"~/Desktop/SUMO"] stringByExpandingTildeInPath];
    printf("Creating folder %s\n", [folderPath UTF8String]);
    
    NSFileManager *fm = [[NSFileManager alloc] init];
    
    NSError *e = NULL;
    [fm createDirectoryAtPath:folderPath withIntermediateDirectories:YES attributes:nil error:&e];
    
    NSString *filepath = [NSString stringWithFormat:@"~/Desktop/SUMO/%s", file];
    filepath = [filepath stringByExpandingTildeInPath];
    
    FILE *f = fopen([filepath UTF8String], "w");
    
    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(f, "<nodes xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://sumo.sf.net/xsd/nodes_file.xsd\">\n");
    
    std::list<RoadVertex*>::iterator i;
    printf("NodeList size: %d\n", engine->nodeList.size());
    for(i=engine->nodeList.begin(); i != engine->nodeList.end(); ++i)
    {
        RoadVertex *aux = *i;
        fprintf(f, "    <node id=\"%s\" x=\"%f\" y=\"%f\" />\n", aux->name.str().c_str(), aux->position.x*1000, aux->position.y*1000);
    }
    fprintf(f, "</nodes>\n");
    
    fclose(f);
}