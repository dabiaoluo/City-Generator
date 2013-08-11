//
//  MainMenu.cpp
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 08/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#include "MainMenu.h"
//
//- (void)changed:(id)sender
//{
//    NSSlider *radius = sender;
//    printf("%f\n", [radius floatValue]);
//    [_radiusField setFloatValue:[radius floatValue]];
//}


void MainMenu::updateLabels()
{
    [buildingsNumberField setFloatValue:[buildings floatValue]];
    [radiusField setFloatValue:[radius floatValue]];
    
    updateValues();
}

void MainMenu::updateValues()
{

    buildingsVal = [buildings integerValue];
    radiusVal = [radius floatValue];
}

void MainMenu::changedRadius()
{
    
}

void MainMenu::changedBuildingsNumber()
{
    
}