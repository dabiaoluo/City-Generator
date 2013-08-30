//
//  AppDelegate.m
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 07/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//


#include "ShaderProgram.h"

#import "AppDelegate.h"
#import "Engine.h"
#import "Renderer.h"
#import "EventHandler.h"

#include "Engine.h"
#include "TestCreationClass.h"

#include <math.h>
#include "utils.h"
#include "dxflib/dl_dxf.h"
#include "dxflib/dl_creationadapter.h"

Engine *engine = new Engine();


@implementation AppDelegate

@synthesize blockType, buildings, buildingsNumberField, error, radius, radiusField, window;

-(IBAction) exportOBJ:(id)sender
{
    engine->e->e->exportBuildingsToFile("test.obj");
}

- (void)dealloc
{
    [super dealloc];
}

- (IBAction)changedRadius:(id)sender
{
    engine->mainMenu->changedRadius();
}

- (IBAction)changedBuildingsNumber:(id)sender
{
    engine->mainMenu->changedBuildingsNumber();
}
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    
    NSRect windowRect = [[self window] frame];
    NSPoint pos;
    pos.y = windowRect.origin.y*2;
    [window setFrameOrigin:pos];
    
    engine->setup();
    Renderer *r = engine->r;
    EventHandler *e = engine->e;
    
    engine->mainMenu->radius = radius;
    engine->mainMenu->radiusField = radiusField;
    engine->mainMenu->buildings = buildings;
    engine->mainMenu->buildingsNumberField = buildingsNumberField;
    engine->mainMenu->blockType = blockType;

    engine->mainMenu->updateLabels();
    
    NSString *path = [[NSBundle mainBundle] resourcePath];
    NSString *roadPath = [[NSString stringWithFormat:@"~/Desktop/roads.dxf"] stringByExpandingTildeInPath];
    
    Test_CreationClass* creationClass = new Test_CreationClass();
    DL_Dxf* dxf = new DL_Dxf();
    std::string resourcePath = [roadPath UTF8String];
//    resourcePath.append("/roads.dxf");
    
    if (!dxf->in(resourcePath.c_str(), creationClass))
    { // if file open failed
        exit(0);
    }
    
//    r->createFramebuffer();
    
    std::string vsPath = [path UTF8String];
    vsPath.append("/shader.vert");
    std::string fsPath = [path UTF8String];
    fsPath.append("/shader.frag");
    
    
    ShaderProgram *sp = new ShaderProgram();
    sp->load(vsPath.c_str(), fsPath.c_str());
    sp->bindAttribLocation(0, "in_Position");
    sp->bindAttribLocation(1, "in_Color");
    sp->bindAttribLocation(2, "uv_texCoord");
    sp->link();
    
    r->perspective();
    
    r->buildVAO();
    
//    r->renderToScreen();
    sp->useProgram();
    
    glm::vec3 cameraPos(0.001f);
    
    cameraPos.z = e->depth;
    
//    engine->loadTexture("01.jpg");
//    engine->loadTexture("02.jpg");
//    engine->loadTexture("03.jpg");
//    engine->loadTexture("04.jpg");
//    engine->loadTexture("05.jpg");
//    engine->loadTexture("06.jpg");
//    engine->loadTexture("07.jpg");
//    engine->loadTexture("08.jpg");
//    engine->loadTexture("09.jpg");
//    engine->loadTexture("10.jpg");
//    engine->loadTexture("11.jpg");
//    engine->loadTexture("12.jpg");
//    engine->loadTexture("13.jpg");
//    engine->loadTexture("14.jpg");
//    engine->loadTexture("15.jpg");
//    engine->loadTexture("16.jpg");
//    engine->loadTexture("17.jpg");
    engine->loadTexture("01.jpg");
    
    GLint mvp_uniform = sp->getUniform("modelViewProjectionMatrix");
    GLint useTexture = sp->getUniform("useTexture");
    GLuint TextureID  = sp->getUniform("s_texture");

    while(1)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        e->processEvents();
        r->loadIdentity();
        r->multProjection();
        
        float nwx, nwy, nwz;
        
        float z = 2.0f/(r->zFar-r->zNear);
        
        nwx = 2 * (e->mouse_x - r->viewport[0])/r->viewport[2] - 1;
        nwy = 2 * (r->viewport[3]-e->mouse_y)/r->viewport[3] - 1;
        nwz = z*(-e->depth-r->zNear) - 1.0f;
        nwz *= -1;
//        printf("nwz: %f\n", nwz);
        
        r->translate(0, 0, e->depth);
        r->rotate((e->rot_ax+e->rot_x)*0.3f, glm::vec3(1,0,0));
        r->rotate((e->rot_ay+e->rot_y)*0.3f, glm::vec3(0,0,1));
        r->translate((e->pan_ax+e->pan_x)*0.01-15, (e->pan_ay+e->pan_y)*0.01-15, 0.0f);
        
        glm::mat4 objMatrix(1.0f);
        
        r->pushMatrix();
        
        r->modelMatrix = r->modelMatrix * objMatrix;

        glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(r->modelMatrix));
        
//        r->renderAllModels();
        glBindVertexArray(engine->r->vao);
        glDrawElements(GL_LINES, engine->r->vertexList.size()*1.0f, GL_UNSIGNED_INT, (GLvoid*)0);
        glBindVertexArray(0);
        
        r->popMatrix();
        
        if(engine->sfInitialized == true)
        {
            r->pushMatrix();
            objMatrix = glm::mat4(1.0f);
            
            glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(r->modelMatrix));
            
            glBindVertexArray(engine->sf->vao);
            glDrawElements(GL_POINTS, engine->sf->counter, GL_UNSIGNED_INT, (GLvoid*)0);
            glBindVertexArray(0);
            r->popMatrix();
        }
        
        glm::vec3 zNearPoint = glm::unProject(glm::vec3(r->viewport[2]-e->mouse_x, e->mouse_y, nwz), r->modelMatrix, r->projectionMatrix, glm::vec4(r->viewport));
        
        glm::vec3 camPos;
        camPos = glm::unProject(glm::vec3(r->viewport[2]/2.0f, r->viewport[3]/2.0f, 0),
                                r->modelMatrix, r->projectionMatrix, glm::vec4(r->viewport));
        
        glm::vec3 v(camPos.x-zNearPoint.x, camPos.y-zNearPoint.y, camPos.z-zNearPoint.z);
        v.x *= 1.05f;
        v.y *= 1.6f;
        
        glm::vec3 cubePos;
        cubePos = glm::vec3(engine->cursorPos.x, engine->cursorPos.y, 0);
        r->pushMatrix();
        
        objMatrix = glm::mat4(1.0f);
        objMatrix = glm::translate(objMatrix, glm::vec3(cubePos.x,cubePos.y, cubePos.z));
        r->modelMatrix = r->modelMatrix * objMatrix;
        
        r->scale(0.01f, 0.01f, 0.01f);
        glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(r->modelMatrix));
        
        glBindVertexArray(r->vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);
        
        r->scale(100.00f*[radius floatValue], 100.0f*[radius floatValue], 100.0f);
        glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(r->modelMatrix));
        
        
        glBindVertexArray(r->circleVao);
        glDrawElements(GL_LINE_LOOP, 30, GL_UNSIGNED_INT, (GLvoid*)0);
        
        r->popMatrix();
        
        for(int i=-20000;i<50000;i+=10) // create 25 cubes on the picking ray direction
        {
            cubePos = glm::vec3(camPos.x-(float)i*v.x,camPos.y-(float)i*v.y,camPos.z-(float)i*v.z);
            if(abs((float)cubePos.z) < 0.01)
            {
                engine->cursorPos.x = cubePos.x;
                engine->cursorPos.y = cubePos.y;
                
            }
            //                            printf("Cube(%f, %f, %f)\n", cubePos.x, cubePos.y, cubePos.z);
            //            if(cubePos.z > 0 && cubePos.z < -e->depth-2)
            //            {
            //                //            cubePos = glm::vec3(camPos.x, camPos.y, camPos.z-1);
            //                r->pushMatrix();
            //                objMatrix = glm::mat4(1.0f);
            //                objMatrix = glm::translate(objMatrix, glm::vec3(cubePos.x, cubePos.y, cubePos.z));
            //                objMatrix = glm::scale(objMatrix, glm::vec3(0.01f, 0.01f, 0.01f));
            //                r->modelMatrix = r->modelMatrix * objMatrix;
            //
            //                glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(r->modelMatrix));
            //                glBindVertexArray(r->vao);
            //                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);
            //                glBindVertexArray(0);
            //                r->popMatrix();
            //            }
        }
        
        std::list<glm::vec3>::iterator i;
        
        for(i=engine->cubeList.begin(); i != engine->cubeList.end(); ++i)
        {
            glm::vec3 aux = *i;
            
            r->pushMatrix();
            objMatrix = glm::mat4(1.0f);
            objMatrix = glm::translate(objMatrix, glm::vec3(aux.x, aux.y, aux.z));
            objMatrix = glm::scale(objMatrix, glm::vec3(0.01f, 0.01f, 0.01f));
            r->modelMatrix = r->modelMatrix * objMatrix;
            
            glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(r->modelMatrix));
            

            glBindVertexArray(r->vao);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);
            glBindVertexArray(0);
            r->popMatrix();
        }
        
        std::list<Building*>::iterator j;
        for(j=engine->buildingList.begin(); j != engine->buildingList.end(); ++j)
        {
            Building* aux = *j;
            
            r->pushMatrix();
            objMatrix = glm::mat4(1.0f);
            objMatrix = glm::translate(objMatrix, glm::vec3(aux->position.x, aux->position.y, aux->position.z));
            objMatrix = glm::rotate(objMatrix, aux->rotation, glm::vec3(0,0,1.0f));
            objMatrix = glm::translate(objMatrix, glm::vec3(-aux->width/2, -aux->depth/2, aux->position.z));
            
            r->modelMatrix = r->modelMatrix * objMatrix;
            
            glUniform1i(useTexture, 1);
            
            glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(r->modelMatrix));
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, engine->textureList[0]->image);
            glUniform1i(TextureID, 0);
            
            glBindVertexArray(aux->vao);
            glDrawElements(GL_TRIANGLES, aux->numTriangles, GL_UNSIGNED_INT, (GLvoid*)0);
//            glDrawArrays(GL_TRIANGLES, aux->numTriangles);
            
            glUniform1i(useTexture, 0);
            glBindVertexArray(0);
            r->popMatrix();
        }
        
        //        if(toScreen == true)
        //        {
        //            r->renderToScreen();
        //            toScreen = false;
        //        }
        //        else
        //        {
        SDL_Delay(1000.0f / 60.0f);
        r->swap();
        //            r->renderToTexture();
        //            toScreen = true;
        //        }

    }
}

@end
