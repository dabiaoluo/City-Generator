//
//  Renderer.cpp
//  Proto10Client
//
//  Created by Gustavo Buzogany Eboli on 29/06/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "Renderer.h"
#include "utils.h"
#include "Engine.h"


#define PROGRAM_NAME "City Generator"

#define WIDTH 1024
#define HEIGHT 768

extern Engine* engine;

Renderer::Renderer()
{
    fov = 60.0f;
    zNear = 0.1f;
    zFar  = 1000.0f;
    viewport = glm::vec4(0, 0, WIDTH, HEIGHT);
}

void Renderer::setupSDL_GL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        Utils::sdldie("Unable to initialize SDL"); /* Or die on error */
    
    /* Request an opengl 3.2 context.
     * SDL doesn't have the ability to choose which profile at this time of writing,
     * but it should default to the core profile */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    
    
    /* Enable double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    /* Enable multisampling for a nice antialiased effect */
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    
    /* Create our window centered at 512x512 resolution */
    window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) /* Die if creation failed */
        Utils::sdldie("Unable to create window");
    
    /* Create our opengl context and attach it to our window */
    context = SDL_GL_CreateContext(window);
    
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
    
    /* Enable Z depth testing so objects closest to the viewpoint are in front of objects further away */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_PROGRAM_POINT_SIZE);
    //    glFrontFace(GL_CW);
}

void Renderer::destroySDL_GL()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::swap()
{
    SDL_GL_SwapWindow(window);
}

void Renderer::loadVAO()
{
    
    
    static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f
	};
    
	static const GLfloat g_color_buffer_data[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f
	};
    
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    static const GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        3, 6, 7,
        3, 6, 2,
        7, 4, 6,
        4, 5, 6,
        4, 5, 0,
        5, 1, 0,
        2, 6, 5,
        5, 1, 2,
        7, 3, 0,
        7, 0, 4
    };
    
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices , GL_STATIC_DRAW);
    
    loadCircle();
}

void Renderer::loadCircle()
{
    
    std::vector<Vertex> vertex;
    std::vector<Color> color;
    std::vector<GLuint> index;
    
    Vertex v;
    Color c;
    
    c.color[0] = 1.0f;
    c.color[1] = 1.0f;
    c.color[2] = 1.0f;
    
    
    int steps = 30;
    float delta = 2*M_PI/steps;
    
    for(int i=0;i<steps;i++)
    {
        v.position[0] = cosf((float)i * delta);
        v.position[1] = sinf((float)i * delta);
        v.position[2] = 0.0f;
        
        vertex.push_back(v);
        color.push_back(c);
        index.push_back(i);
    }
    
    glGenVertexArrays(1, &circleVao);
    glBindVertexArray(circleVao);
    
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex.size(), &vertex[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color) * color.size(), &color[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * index.size(), &index[0] , GL_STATIC_DRAW);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void Renderer::perspective()
{
    projectionMatrix = glm::perspective(fov, (float)WIDTH/(float)HEIGHT, zNear, zFar);
}

void Renderer::loadTexture()
{
    
    GLuint texture;
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    
}


void Renderer::loadIdentity()
{
    modelMatrix = glm::mat4(1.0f);
}

void Renderer::multProjection()
{
    modelMatrix = projectionMatrix * modelMatrix;
}

void Renderer::rotate(GLfloat angle, glm::vec3 axis)
{
    glm::mat4 rotMatrix = glm::rotate(angle, axis);
    modelMatrix = modelMatrix * rotMatrix;
}

void Renderer::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    glm::vec3 axis(x, y, z);
    glm::mat4 rotMatrix = glm::rotate(angle, axis);
    modelMatrix = modelMatrix * rotMatrix;
}

void Renderer::translate(GLfloat x, GLfloat y, GLfloat z)
{
    glm::mat4 translationMatrix = glm::translate(x, y, z);
    modelMatrix = modelMatrix * translationMatrix;
}

void Renderer::scale(GLfloat sx, GLfloat sy, GLfloat sz)
{
    glm::mat4 myScalingMatrix = glm::scale(sx, sy, sz);
    modelMatrix = modelMatrix * myScalingMatrix;
}


void Renderer::destroywindow()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::pushMatrix()
{
    matrixStack.push(modelMatrix);
}

void Renderer::popMatrix()
{
    modelMatrix = matrixStack.top();
    matrixStack.pop();
}

void Renderer::renderAllModels()
{
    std::list<Model*>::iterator i;
    
    //    int n = 1;
    //    printf("Models: %d\n", engine->modelList.size());
    
    for(i=engine->modelList.begin(); i != engine->modelList.end(); ++i)
    {
        Model* aux = (Model*) *i;
        //        printf("     %d Components: %d\n", n++, aux->componentList.size());
        
        std::list<ModelComponent*>::iterator i;
        
        for(i=aux->componentList.begin(); i != aux->componentList.end(); ++i)
        {
            ModelComponent* component = (ModelComponent*) *i;
            //            component->repaint(glm::vec3(0,255,0));
            //                glBindBufferRange(GL_UNIFORM_BUFFER,
            //                                        materialUniLoc,
            //                                        myMeshes[nd->mMeshes[n]].uniformBlockIndex,
            //                                        0,
            //                                        sizeof(struct MyMaterial));
            //		glBindTexture(GL_TEXTURE_2D, myMeshes[nd->mMeshes[n]].texIndex);
            //                component->printVertices();
            glBindVertexArray(component->vao);
            if(component->type == 0)
            {
                glDrawElements(GL_LINES, (int) component->vertexList.size(), GL_UNSIGNED_INT, 0);
            }
            else if(component->type == 1)
            {
                glDrawElements(GL_LINE_STRIP, (int) component->vertexList.size(), GL_UNSIGNED_INT, 0);
            }
        }
    }
    //    printf("Rendered!");
}

glm::vec3 Renderer::unproject(int wx, int wy)
{
    glm::vec4 viewport(0, 0, WIDTH, HEIGHT);
    
    float nwx, nwy, nwz;
    
    float z = -engine->e->depth/(zFar-zNear);
    
    nwx = 2 * (wx - viewport[0])/viewport[2] - 1;
    nwy = 2 * (viewport[3] - wy)/viewport[3] - 1;
    nwz = 2 * z - 1;
    
    glm::mat4 mvp = projectionMatrix * modelMatrix;
    mvp = glm::inverse(mvp);
    
    glm::vec4 n(nwx,nwy,nwz,1);
    
    n = n * mvp;
    
    return glm::vec3(n[0]/n[3],n[1]/n[3],n[2]/n[3]);
}

void Renderer::createFramebuffer()
{
    glGenFramebuffers(1, &fbName);
    glBindFramebuffer(GL_FRAMEBUFFER, fbName);
    
    glGenTextures(1, &sceneTexture);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, sceneTexture);
    
    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, WIDTH, HEIGHT, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
    
    // Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 4096, 4096);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    
    // Set "renderedTexture" as our colour attachement #0
    //    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, sceneTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sceneTexture, 0);
    
    // Set the list of draw buffers.
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
    
    GLint maxTextureSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    printf("Max texture size: %dx%d\n", maxTextureSize, maxTextureSize);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Error creating framebuffer!\n");
    }
}

void Renderer::renderToScreen()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,WIDTH,HEIGHT);
}

void Renderer::renderToTexture()
{
    glBindFramebuffer(GL_FRAMEBUFFER, sceneTexture);
    glViewport(0,0,WIDTH,HEIGHT);
}

void Renderer::writeTextureToFile()
{
    
    byte *raw_img = (byte*) malloc(sizeof(byte) * WIDTH * HEIGHT * 3);
    
    glBindTexture(GL_TEXTURE_2D,sceneTexture);
    
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, WIDTH, HEIGHT, 0);
    
    glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_UNSIGNED_BYTE,raw_img);
    
    FILE *out = fopen("tex.bmp", "w");
    fwrite(raw_img, 1 ,WIDTH * HEIGHT, out); // Write
    fclose(out);
}


//void Renderer::renderModel (Model *m)
//{
//    const aiScene* sc = m->scene;
//    const aiNode* nd = m->scene->mRootNode;
//
//    recursiveRender(sc, nd, m);
//}
//
//void Renderer::recursiveRender (const aiScene *sc, const aiNode* nd, Model* md)
//{
////	// Get node transformation matrix
////	aiMatrix4x4 m = nd->mTransformation;
////	// OpenGL matrices are column major
////	m.Transpose();
////
////	// save model matrix and apply node transformation
////	pushMatrix();
////
////	float aux[16];
////	memcpy(aux,&m,sizeof(float) * 16);
////	multMatrix(modelMatrix, aux);
////	setModelMatrix();
//
//
//	// draw all meshes assigned to this node
//	for (unsigned int n=0; n < nd->mNumMeshes; ++n){
//		// bind material uniform
////		glBindBufferRange(GL_UNIFORM_BUFFER, materialUniLoc, myMeshes[nd->mMeshes[n]].uniformBlockIndex, 0, sizeof(struct MyMaterial));
//		// bind texture
////		glBindTexture(GL_TEXTURE_2D, myMeshes[nd->mMeshes[n]].texIndex);
//		// bind VAO
//		glBindVertexArray(md->myMeshes[nd->mMeshes[n]].vao);
//		// draw
//		glDrawElements(GL_LINES,md->myMeshes[nd->mMeshes[n]].numFaces*3,GL_UNSIGNED_INT,0);
//	}
//
//	// draw all children
//	for (unsigned int n=0; n < nd->mNumChildren; ++n){
//		recursiveRender(sc, nd->mChildren[n], md);
//	}
////	popMatrix();
//}

