//
//  MainMenu.h
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 08/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#ifndef __Tool2_Cocoa__MainMenu__
#define __Tool2_Cocoa__MainMenu__

#include <iostream>

class MainMenu
{
public:
    NSSlider *radius;
    NSSlider *buildings;
    
    NSTextField *buildingsNumberField;
    NSTextField *radiusField;
    
    NSPopUpButton *blockType;
    
    float radiusVal;
    float buildingsVal;
    
    void changedRadius();
    void changedBuildingsNumber();
    void updateLabels();
    void updateValues();
};

#endif /* defined(__Tool2_Cocoa__MainMenu__) */
