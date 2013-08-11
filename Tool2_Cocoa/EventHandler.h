//
//  Event.h
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 24/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2__Event__
#define __Tool2__Event__

#include <iostream>
#include <SDL2/SDL.h>

#include "exportOBJ.h"

class EventHandler
{
public:
    EventHandler();
    void processEvents();
    
    float depth;
    float deltaDepth;
    
    int mouse_x, mouse_y;
    
    float rot_x, rot_y;
    float rot_ax, rot_ay;
    float pan_x, pan_y;
    float pan_ax, pan_ay;
    float px, py;
    
    bool b0, b1, b3;
    bool pressed2, pressed3;
    
    bool painting;
    
    bool up;
    
    exportOBJ* e;
};

#endif /* defined(__Tool2__Event__) */
