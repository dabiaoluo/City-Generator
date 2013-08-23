//
//  ConnectionExporter.h
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 14/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2_Cocoa__ConnectionExporter__
#define __Tool2_Cocoa__ConnectionExporter__

#include <iostream>


class ConnectionExporter
{
public:
    ConnectionExporter();
    void connectRoads();
    void exportToFile(const char *file);
};
#endif /* defined(__Tool2_Cocoa__ConnectionExporter__) */
