//
//  Event.cpp
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 24/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "EventHandler.h"
#include "Engine.h"

extern Engine* engine;

EventHandler::EventHandler()
{
    depth = -7.0f;
    deltaDepth = 10.0f;
    
    rot_x = rot_y = 0;
    rot_ax = rot_ay = 0;
    pan_x = pan_y = 0;
    pan_ax = pan_ay = 0;
    
    mouse_x = mouse_y = 0;
    
    b0 = b1 = b3 = false;
    
    pressed2 = pressed3 = false;
    
    painting = false;
    
    up = false;
    e = new exportOBJ();
}

void EventHandler::processEvents()
{
	SDL_Event event;
	int key;
    
    engine->mainMenu->updateValues();
    
	while (SDL_PollEvent(&event) != 0)
	{
		key = event.key.keysym.sym;
		switch (event.type)
		{
			case SDL_KEYUP:
                if(key == 'q')
				{
                    exit(0);
				}
				if(key == 'p')
				{
					depth+=1/deltaDepth;
				}
				else if(key=='l')
				{
					depth-=1/deltaDepth;
				}
				else if(key == 'a')
				{
					rot_ay-= 10;
				}
				else if(key == 'd')
				{
					rot_ay+= 10;
				}
				else if(key == 's')
				{
					rot_ax+= 10;
				}
				else if(key == 'w')
				{
					rot_ax-= 10;
				}
                else if(key == 't')
				{
//                    engine->r->writeTextureToFile();
				}
                else if(key == 'y')
				{
					
				}
                else if(key == 'm')
				{
//					engine->sf->craftSurfaces();
//                    engine->sf->buildVAO();
//                    engine->sfInitialized = true;
				}
				break;
			case SDL_MOUSEMOTION:
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
                if(b0 == true)
                {
                    if([engine->mainMenu->buildings intValue] < 50)
                        engine->bf->createBuildingsOfType([engine->mainMenu->radius floatValue], [engine->mainMenu->buildings intValue], (int)[[engine->mainMenu->blockType selectedItem] tag]);
                }
				else if(b1 == true)
				{
                    pan_x = event.button.x - px;
					pan_y = py - event.button.y;
				}
				else if(b3 == true)
				{
					rot_x = py - event.button.y;
					rot_y = event.button.x - px;
				}
			case SDL_MOUSEBUTTONDOWN:
//                printf("Button: %d\n", event.button.button);
                if(event.button.button == 1 && b0 == false)
				{
                    b0 = true;
//                    printf("pressed\n");
//                    engine->queryPoint();
                    engine->bf->createBuildingsOfType([engine->mainMenu->radius floatValue], [engine->mainMenu->buildings intValue], (int)[[engine->mainMenu->blockType selectedItem] tag]);
                    painting = true;
				}
				else if(event.button.button == 3 && pressed2 == false)
				{
					pressed2 = true;
					b1 = true;
					px = event.button.x;
					py = event.button.y;
				}
				else if(event.button.button == 2 && b1 == false && pressed3 == false)
				{
					pressed3 = true;
					b3 = true;
					px = event.button.x;
					py = event.button.y;
				}
				else if(event.button.button == 4 && b1 == false)
				{
					depth++;
				}
				else if(event.button.button == 5 && b1 == false)
				{
					depth--;
				}
				break;
			case SDL_MOUSEBUTTONUP:
                if(event.button.button == 1 && b0 == true)
				{
                    painting = false;
                    b0 = false;
				}
				else if(event.button.button == 3 && pressed2 == true)
				{
					b1 = false;
					pressed2 = false;
					pan_ax = pan_ax+pan_x;
					pan_ay = pan_ay+pan_y;
					pan_x = 0;
					pan_y = 0;
				}
				else if(event.button.button == 2 && pressed3 == true)
				{
					b3 = false;
                    pressed3 = false;
					rot_ax = rot_ax+rot_x;
					rot_ay = rot_ay+rot_y;
					rot_x = 0;
					rot_y = 0;
				}
				break;
            case SDL_MOUSEWHEEL:
                depth += event.wheel.y/deltaDepth;
                break;
			case SDL_QUIT:
				exit(0);
				break;
		}
	}
}
