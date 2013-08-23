//
//  RoadExporter.cpp
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 15/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "RoadExporter.h"
#include "Engine.h"
#include "Road.h"

extern Engine* engine;

RoadExporter::RoadExporter()
{
    
}

void RoadExporter::exportToFile(const char *file)
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
    fprintf(f, "<edges xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://sumo.sf.net/xsd/edges_file.xsd\">\n");
    
    std::list<Road*>::iterator i;
    printf("RoadList size: %d\n", engine->RoadList.size());
    for(i=engine->RoadList.begin(); i != engine->RoadList.end(); ++i)
    {
        Road *aux = *i;
        char type;
        if(aux->lanes == 1)
            type = 'a';
        else if(aux->lanes == 2)
            type = 'b';
        else
            type = 'c';
        fprintf(f, "    <edge id=\"%s\" from=\"%s\" to=\"%s\" type=\"%c\"/>\n", aux->name.str().c_str(), aux->a->name.str().c_str(), aux->b->name.str().c_str(), type);
    }
    fprintf(f, "</edges>\n");
    
    fclose(f);
}