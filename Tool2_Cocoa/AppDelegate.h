//
//  AppDelegate.h
//  Tool2_Cocoa
//
//  Created by Gustavo Buzogany Eboli on 07/08/2013.
//  Copyright (c) 2013 Gustavo Buzogany Eboli. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSSlider *radius;
@property (assign) IBOutlet NSSlider *buildings;

@property (assign) IBOutlet NSTextField *buildingsNumberField;
@property (assign) IBOutlet NSTextField *radiusField;

@property (assign) IBOutlet NSPopUpButton *blockType;

@end
