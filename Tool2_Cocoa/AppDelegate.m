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
#include "Model.h"
#include "ModelFactory.h"

#include <math.h>
#include "utils.h"
#include "dxflib/dl_dxf.h"
#include "dxflib/dl_creationadapter.h"

Engine *engine = new Engine();
NSSlider *radiusSlider;

@implementation AppDelegate

-(IBAction) exportOBJ:(id)sender
{
    engine->e->e->exportBuildingsToFile("test.obj");
}

-(IBAction) generateSUMO:(id)sender
{
    printf("Generating SUMO files...\n");
    engine->connectionExporter->exportToFile("city.con.xml");
    engine->nodeExporter->exportToFile("city.nod.xml");
    engine->roadExporter->exportToFile("city.edg.xml");
    
    NSString *path = [[NSBundle mainBundle] resourcePath];
    
    std::string toolPath = [path UTF8String];
    std::string commaPath = "\"";
    commaPath.append(toolPath);
    commaPath.append("/netconvert\" -c ~/Desktop/SUMO/city.netccfg --speed-in-kmh");
//    printf("cmd: %s\n", commaPath.c_str());
    
    NSString *folderPath = [[NSString stringWithFormat:@"~/Desktop/SUMO/city.netccfg"] stringByExpandingTildeInPath];
    bool exists = [[NSFileManager defaultManager] fileExistsAtPath:folderPath];
    if(!exists)
        return;
    
    system(commaPath.c_str());
}

-(IBAction) generateRoutes:(id)sender
{
    NSString *path = [[NSBundle mainBundle] resourcePath];
    bool exists;
    
    std::string toolPath = [path UTF8String];
    std::string commaPath = "\"";
    commaPath.append(toolPath);
    commaPath.append("/duarouter\" --trip-files=\"");
    NSString *folderPath = [[NSString stringWithFormat:@"~/Desktop/SUMO/city.trips.xml"] stringByExpandingTildeInPath];
    exists = [[NSFileManager defaultManager] fileExistsAtPath:folderPath];
    if(!exists)
        return;
    
    commaPath.append([folderPath UTF8String]);
    commaPath.append("\" --net-file=\"");
    exists = [[NSFileManager defaultManager] fileExistsAtPath:folderPath];
    if(!exists)
        return;
    
    folderPath = [[NSString stringWithFormat:@"~/Desktop/SUMO/city.net.xml"] stringByExpandingTildeInPath];
    commaPath.append([folderPath UTF8String]);
    commaPath.append("\" --output-file=");
    folderPath = [[NSString stringWithFormat:@"~/Desktop/SUMO/city.rou.xml"] stringByExpandingTildeInPath];
    commaPath.append([folderPath UTF8String]);
    commaPath.append(" --ignore-errors -e 3600 -W");
    printf("cmd: %s\n", commaPath.c_str());
    
    system(commaPath.c_str());
}

-(IBAction) generateTrips:(id)sender
{
    NSString *path = [[NSBundle mainBundle] resourcePath];
    
    std::string toolPath = [path UTF8String];
    std::string commaPath = "python \"";
    commaPath.append(toolPath);
    
    NSString *folderPath = [[NSString stringWithFormat:@"~/Desktop/SUMO/city.net.xml"] stringByExpandingTildeInPath];
    bool exists = [[NSFileManager defaultManager] fileExistsAtPath:folderPath];
    if(!exists)
        return;

    commaPath.append("/randomTrips.py\" -n ~/Desktop/SUMO/city.net.xml -p ");
    commaPath.append([[_numberOfRoutes stringValue] UTF8String]);
    commaPath.append(" -e 3600 -o ~/Desktop/SUMO/city.trips.xml ");
    printf("cmd: %s\n", commaPath.c_str());
    
    system(commaPath.c_str());
}

-(IBAction) generateConnectivity:(id)sender
{
    NSString *path = [[NSBundle mainBundle] resourcePath];
    
    std::string toolPath = [path UTF8String];
    std::string commaPath = "python \"";
    commaPath.append(toolPath);
    
    NSString *folderPath = [[NSString stringWithFormat:@"~/Desktop/SUMO/city.net.xml"] stringByExpandingTildeInPath];
    bool exists = [[NSFileManager defaultManager] fileExistsAtPath:folderPath];
    if(!exists)
        return;
    
    NSString *outPath = [[NSString stringWithFormat:@"~/Desktop/SUMO/out.txt"] stringByExpandingTildeInPath];
    
    commaPath.append("/netcheck.py\" ~/Desktop/SUMO/city.net.xml --source L17.7131-L11.2048L17.7716-L11.2424 --selection-output=");
    commaPath.append([outPath UTF8String]);
    printf("cmd: %s\n", commaPath.c_str());
    
    system(commaPath.c_str());
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
    [_window setFrameOrigin:pos];
    
    engine->setup();
    Renderer *r = engine->r;
    EventHandler *e = engine->e;
    
    engine->mainMenu->radius = _radius;
    engine->mainMenu->radiusField = _radiusField;
    engine->mainMenu->buildings = _buildings;
    engine->mainMenu->buildingsNumberField = _buildingsNumberField;
    engine->mainMenu->blockType = _blockType;

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
    engine->mf->finish();
    
//
//
//    commaPath = "\"";
//    commaPath.append(toolPath);
//    commaPath.append("/randomTrips.py\" -n ~/Desktop/SUMO/city.net.xml -e 1000 -l -o ~/Desktop/SUMO/city.trips.xml ");
//    printf("cmd: %s\n", commaPath.c_str());
//
//    system(commaPath.c_str());
//
//    commaPath = "\"";
//    commaPath.append(toolPath);
//    commaPath.append("/duarouter\" --trip-files=\"/Users/gbuzogany/Desktop/SUMO/city.trips.xml\" --net-file=\"/Users/gbuzogany/Desktop/SUMO/city.net.xml\" --output-file=/Users/gbuzogany/Desktop/SUMO/city.rou.xml --ignore-errors ");
//    printf("cmd: %s\n", commaPath.c_str());
//    
//    system(commaPath.c_str());
//    exit(0);
    
    printf("Building VAOs...\n");
    engine->buildVAO();
    printf("Built!\n");

    
    r->createFramebuffer();
    
    std::string vsPath = [path UTF8String];
    vsPath.append("/shader.vert");
    std::string fsPath = [path UTF8String];
    fsPath.append("/shader.frag");
    
    
    ShaderProgram *sp = new ShaderProgram();
    sp->load(vsPath.c_str(), fsPath.c_str());
    sp->bindAttribLocation(0, "in_Position");
    sp->bindAttribLocation(1, "in_Color");
    sp->link();
    
    r->perspective();
    
    r->loadVAO();
    
    r->renderToScreen();
    sp->useProgram();
    
    glm::vec3 cameraPos(0.001f);
    
    cameraPos.z = e->depth;
    
    bool toScreen = true;
    
    while(1)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLint mvp_uniform = sp->getUniform("modelViewProjectionMatrix");
        
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
        r->renderAllModels();
        
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
        
        r->scale(100.00f*[_radius floatValue], 100.0f*[_radius floatValue], 100.0f);
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
            
            
            glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(r->modelMatrix));
            
            glBindVertexArray(aux->vao);
            glDrawElements(GL_TRIANGLES, aux->numTriangles, GL_UNSIGNED_INT, (GLvoid*)0);
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
        r->swap();
        //            r->renderToTexture();
        //            toScreen = true;
        //        }

    }
}

@end
