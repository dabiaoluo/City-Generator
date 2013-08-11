//
//  Renderer.h
//  Proto10Client
//
//  Created by Gustavo Buzogany Eboli on 29/06/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Proto10Client__Renderer__
#define __Proto10Client__Renderer__

//#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <list>
#include <stack>
#include "Model.h"
#include "ModelComponent.h"
//#include "SOIL.h"

#define SDL_WindowID SDL_Window*

typedef enum {
    X_AXIS,
    Y_AXIS,
    Z_AXIS
} AXIS;

class Renderer
{
public:
    Renderer();
    void setupSDL_GL();
    void swap();
    void destroySDL_GL();
    void loadVAO();
    void perspective();
    void loadIdentity();
    void multProjection();
    void loadTexture();
    void scale(GLfloat sx, GLfloat sy, GLfloat sz);
    void translate(GLfloat x, GLfloat y, GLfloat z);
    void rotate(GLfloat angle, glm::vec3 axis);
    void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    void destroywindow();
    void renderAllModels();
    void pushMatrix();
    void popMatrix();
    glm::vec3 unproject(int wx, int wy);
    void createFramebuffer();
    void renderToScreen();
    void renderToTexture();
    void writeTextureToFile();
    void loadCircle();

    glm::mat4 projectionMatrix;
    glm::mat4 modelMatrix;
    
    GLuint colorBuffer;
    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint elementBuffer;
    GLuint vao;
    GLuint circleVao;
    GLfloat fov, zNear, zFar;
    std::stack<glm::mat4> matrixStack;
    glm::vec4 viewport;
    
    GLuint fbName;
    GLuint sceneTexture;
    GLuint depthBuffer;
private:
    SDL_Window *window;
    SDL_GLContext context;

};

#endif /* defined(__Proto10Client__Renderer__) */
