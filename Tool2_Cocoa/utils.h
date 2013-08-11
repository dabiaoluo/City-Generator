#ifndef _UTILS_H_
#define _UTILS_H_

#ifndef GLfloat
#include <OpenGL/gl3.h>
#endif

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Utils {
public:
    /* Generate a perspective view matrix using a field of view angle fov,

     * window aspect ratio, near and far clipping planes */
    static void perspective(GLfloat *matrix, GLfloat fov, GLfloat aspect, GLfloat nearz, GLfloat farz);
        
    /* A simple function that will read a file into an allocated char pointer buffer */
    static char* filetobuf(const char *file);
    
    /* A simple function that prints a message, the error code returned by SDL, and quits the application */
    static void sdldie(const char *msg);
    
    static GLfloat* ortho(GLfloat *m, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat znear, GLfloat zfar);
    
    static float distPointLine(glm::vec3 v, glm::vec3 w, glm::vec3 p);
    static float distPointLine2(glm::vec3 point, glm::vec3 anchor, glm::vec3 end);
};


#endif /* #ifndef _UTILS_H_ */
