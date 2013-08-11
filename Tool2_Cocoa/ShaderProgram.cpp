//
//  ShaderProgram.cpp
//  Proto10Client
//
//  Created by Gustavo Buzogany Eboli on 29/06/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "ShaderProgram.h"
#include "utils.h"

#define DEBUG 1

ShaderProgram::ShaderProgram()
{
    this->shaderProgram = glCreateProgram();
}

bool ShaderProgram::compileShader(GLenum type, const char *file)
{
    GLint status;
    const GLchar *source;
    GLuint *shader;
    
    if(type == GL_VERTEX_SHADER)
    {
        shader = &(this->vertexShader);
    }
    else
    {
        shader = &(this->fragmentShader);
    }
    
    source = Utils::filetobuf(file);
    if (!source)
    {
        printf("Failed to load vertex shader");
        return 0;
    }
    
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        printf("Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return 0;
    }
    
    return 1;
}

bool ShaderProgram::linkProgram()
{
    GLint status;
    GLuint prog = this->shaderProgram;
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        printf("Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0) {
        return 0;
    }
    
    return 1;
}


bool ShaderProgram::validateProgram()
{
    GLint logLength, status;
    GLuint prog = this->shaderProgram;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        printf("Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0) {
        return 0;
    }
    
    return 1;
}

void ShaderProgram::attach()
{
    glAttachShader(this->shaderProgram, this->vertexShader);
    glAttachShader(this->shaderProgram, this->fragmentShader);
}

void ShaderProgram::bindAttribLocation(GLuint attrib, const char *name)
{
    return glBindAttribLocation(shaderProgram, attrib, name);
}



void ShaderProgram::useProgram()
{
    glUseProgram(shaderProgram);
}

GLuint ShaderProgram::getUniform(const GLchar *name)
{
    return glGetUniformLocation(shaderProgram, name);
}

GLuint ShaderProgram::getAttribLocation(const GLchar *name)
{
    return glGetAttribLocation(shaderProgram, name);
}

bool ShaderProgram::load(const char *vs, const char *fs)
{
    if (!this->compileShader(GL_VERTEX_SHADER, vs)) {
        printf("Failed to compile vertex shader");
        return false;
    }
    if (!this->compileShader(GL_FRAGMENT_SHADER, fs)) {
        printf("Failed to compile vertex shader");
        return false;
    }
    
    attach();
    
    return true;
}

bool ShaderProgram::link()
{
    if(!this->linkProgram())
    {
        return false;
    }
    
    return true;
}
