//
//  Layer.h
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 27/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2__Layer__
#define __Tool2__Layer__

#include <iostream>

class Layer
{
public:
    Layer(const char* name, int flags, int color);
    
    char *name;
    int flags;
    int color;
};

#endif /* defined(__Tool2__Layer__) */
