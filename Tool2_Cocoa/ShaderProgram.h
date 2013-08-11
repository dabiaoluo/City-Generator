//
//  ShaderProgram.h
//  Proto10Client
//
//  Created by Gustavo Buzogany Eboli on 29/06/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Proto10Client__ShaderProgram__
#define __Proto10Client__ShaderProgram__

#include <iostream>
#include <OpenGL/gl3.h>

class ShaderProgram
{
public:
    ShaderProgram();
    bool compileShader(GLenum type, const char *file);
    bool linkProgram();
    bool validateProgram();
    void attach();
    void bindAttribLocation(GLuint attrib, const char *name);
    void useProgram();
    GLuint getUniform(const GLchar *name);
    bool load(const char *vs, const char *fs);
    bool link();
    GLuint getAttribLocation(const GLchar *name);
private:
    GLuint vertexShader, fragmentShader;
    GLuint shaderProgram;
};

#endif /* defined(__Proto10Client__ShaderProgram__) */
