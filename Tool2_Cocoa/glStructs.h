//
//  glStructs.h
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 27/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef Tool2_glStructs_h
#define Tool2_glStructs_h

// Uniform index.
enum {
    UNIFORM_PROJ_MATRIX,
    UNIFORM_USETEX,
    UNIFORM_TEXCOORD,
    NUM_UNIFORMS
};

// samplers index
enum {
    SAMPLER_TEX,
    NUM_SAMPLERS
};

// Attribute index.
enum {
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    NUM_ATTRIBUTES
};

#endif
