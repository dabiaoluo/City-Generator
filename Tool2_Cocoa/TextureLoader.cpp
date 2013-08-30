//
//  TextureLoader.cpp
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 29/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
    ilInit(); /* Initialization of DevIL */
}

Texture *TextureLoader::loadTexture(const char* folder, const char *file)
{
    GLuint img;
    ILuint texid;
    
    string path(folder);
    path.append(file);
    
    ilGenImages(1, &texid); /* Generation of one image name */
    ilBindImage(texid); /* Binding of image name */
    success = ilLoadImage((const ILstring)path.c_str()); /* Loading of image "image.jpg" */
    if (success) /* If no error occured: */
    {
        success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every colour component into
                                                             unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
        if (!success)
        {
            /* Error occured */
            exit(0);
            return 0;
        }
        glGenTextures(1, &img); /* Texture name generation */
        glBindTexture(GL_TEXTURE_2D, img); /* Binding of texture name */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH),
                     ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
                     ilGetData());
//        glGenerateMipmap(GL_TEXTURE_2D);
        printf("Created: %d\n", img);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        /* Error occured */
        exit(0);
        return 0;
    }
    ilDeleteImages(1, &texid); /* Because we have already copied image data into texture data
                                we can release memory used by image. */
    return new Texture(img, path);
}