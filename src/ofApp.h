#pragma once

#include "ofxiOS.h"
#include <ARKit/ARKit.h>
#include "ofxARKit.h"
#include "Config.h"
#include "Context.h"
#include "ofxAnimationPrimitives.h"
#include "CaptureDrawer.h"
#include "CircleAnimations.h"
#include "TriAnimations.h"
#include "RectAnimations.h"
#include "ofxGui.h"

class ofApp : public ofxiOSApp {
    
public:
    void setup();
    void setupGui();
    void update();
    void draw();
    void drawOscInfo();
    void drawDebugInfo();
    void drawGeometricGraphics();
    void drawCaptures();
    void exit();
    
    void onPressedCaptureButton();
    void onPressedAnimateButton();
    void onPressedModeGeometricToggle(bool &e);
    void touchDown(ofTouchEventArgs &touch);
    void touchMoved(ofTouchEventArgs &touch);
    void touchUp(ofTouchEventArgs &touch);
    void touchDoubleTap(ofTouchEventArgs &touch);
    void touchCancelled(ofTouchEventArgs &touch);
    
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
    
    //gui
    ofTrueTypeFont font;
    ofxButton captureButton;
    ofxButton animateButton;
    ofxToggle isModeGeometric;
    ofxPanel gui;
    bool isShowGui;
    
    //clip manager
    ofxAnimationPrimitives::InstanceManager manager;
};


