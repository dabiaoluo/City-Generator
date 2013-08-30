//
//  Texture.cpp
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 29/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "Texture.h"

Texture::Texture(GLuint image, string path)
{
    this->image = image;
    this->path = path;
}