//
//  Layer.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 27/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "Layer.h"


Layer::Layer(const char* name, int flags, int color)
{
    this->name = (char*) malloc(strlen(name)*sizeof(char)+1);
    strncpy(this->name, name, strlen(name));
    this->flags = flags;
    this->color = color;
}