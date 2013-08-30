//
//  TextureLoader.h
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 29/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2_Cocoa__TextureLoader__
#define __Tool2_Cocoa__TextureLoader__

#include <iostream>
#include "IL/il.h"
#include <string>
#include "Texture.h"

using namespace std;

class TextureLoader
{
    
public:
    TextureLoader();
    Texture *loadTexture(const char* folder, const char *file);
    
    string url;
    ILuint texid;
    ILboolean success;
    GLuint image;
    int finished;
};

#endif /* defined(__Tool2_Cocoa__TextureLoader__) */
