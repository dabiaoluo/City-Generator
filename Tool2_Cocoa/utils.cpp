#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "utils.h"

/* Generate a perspective view matrix using a field of view angle fov,
 * window aspect ratio, near and far clipping planes */
void Utils::perspective(GLfloat *matrix, GLfloat fov, GLfloat aspect, GLfloat nearz, GLfloat farz)
{
    GLfloat range;
    
    range = tan(fov * 0.00872664625) * nearz; /* 0.00872664625 = PI/360 */
    memset(matrix, 0, sizeof(GLfloat) * 16);
    matrix[0] = (2 * nearz) / ((range * aspect) - (-range * aspect));
    matrix[5] = (2 * nearz) / (2 * range);
    matrix[10] = -(farz + nearz) / (farz - nearz);
    matrix[11] = -1;
    matrix[14] = -(2 * farz * nearz) / (farz - nearz);
}



/* A simple function that will read a file into an allocated char pointer buffer */
char* Utils::filetobuf(const char *file)
{
    FILE *fptr;
    long length;
    char *buf;
    
    fptr = fopen(file, "r"); /* Open file for reading */
    if (!fptr) /* Return NULL on failure */
        return NULL;
    fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
    length = ftell(fptr); /* Find out how many bytes into the file we are */
    buf = (char*)malloc(length + 1); /* Allocate a buffer for the entire length of the file plus a null terminator */
    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
    fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
    fclose(fptr); /* Close the file */
    buf[length] = 0; /* Null terminator */
    
    return buf; /* Return the buffer */
}

/* A simple function that prints a message, the error code returned by SDL, and quits the application */
void Utils::sdldie(const char *msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}

float Utils::distPointLine(glm::vec3 v, glm::vec3 w, glm::vec3 p)
{
//    printf("v(%f, %f), w(%f, %f), p(%f, %f)\n", v.x, v.y, w.x, w.y, p.x, p.y);
    // Return minimum distance between line segment vw and point p
    const float l2 = pow(glm::length(w-v),2);//(v, w);  // i.e. |w-v|^2 -  avoid a sqrt
    if (l2 == 0.0) return glm::distance(p, v);   // v == w case
    // Consider the line extending the segment, parameterized as v + t (w - v).
    // We find projection of point p onto the line.
    // It falls where t = [(p-v) . (w-v)] / |w-v|^2
    const float t = glm::dot(p - v, w - v) / l2;
    if (t < 0.0) return glm::distance(p, v);       // Beyond the 'v' end of the segment
    else if (t > 1.0) return glm::distance(p, w);  // Beyond the 'w' end of the segment
    const glm::vec3 projection = v + t * (w - v);  // Projection falls on the segment
    return glm::distance(p, projection);
}

float Utils::distPointLine2(glm::vec3 point, glm::vec3 anchor, glm::vec3 end)
{
    glm::vec3 d = end - anchor;
    float length = glm::length(d);
    if (d.x == 0 && d.y == 0 && d.z == 0) return glm::length(point - anchor);
    d = glm::normalize(d);
    float intersect = glm::dot((point - anchor), d);
    if (intersect < 0) return glm::length(point - anchor);
    if (intersect > length) return glm::length(point - end);
    return glm::length(point - (anchor + d * intersect));
}//{
//    glm::vec3 s1(0.0f);
//    glm::vec3 s2(0.0f);
//    glm::vec3 s3(0.0f);
//
//    s1 = p0-x1;
//    s2 = p0-x2;
//    s3 = x2-x1;
//    
//    glm::vec3 c1 = glm::cross(s1, s2);
//    
//    float d = glm::length(c1)/glm::length(s3);
//    
//    return d;
//}

