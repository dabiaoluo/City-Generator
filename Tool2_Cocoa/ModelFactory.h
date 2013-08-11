//
//  ModelFactory.h
//  Tool2
//
//  Created by Gustavo Buzogany Eboli on 27/07/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2__ModelFactory__
#define __Tool2__ModelFactory__

#include <iostream>
#include "Model.h"
#include "ModelComponent.h"

class ModelFactory
{
public:
    ModelFactory();
    
    void newComponent();
    void newModel();
    void pushComponent(ModelComponent* mc);
    void pushCurrComponent();
    void finish();
    
    ModelComponent* getCurrComponent();
    
    Model* currModel;
    ModelComponent* currComponent;
    
    int n;
};

#endif /* defined(__Tool2__ModelFactory__) */
