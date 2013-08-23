//
//  Road.cpp
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 14/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "Road.h"
#include "Engine.h"

extern Engine* engine;

Road::Road()
{
    this->identifier = engine->lastRoadID++;
    this->direction = false;
}