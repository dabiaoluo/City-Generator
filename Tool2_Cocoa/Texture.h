//
//  Texture.h
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 29/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2_Cocoa__Texture__
#define __Tool2_Cocoa__Texture__

#include <iostream>
#include <string>
#include "IL/il.h"

using namespace std;

class Texture
{

public:
    Texture(GLuint image, string path);
    
    string path;
    GLuint image;
};

#endif /* defined(__Tool2_Cocoa__Texture__) */
