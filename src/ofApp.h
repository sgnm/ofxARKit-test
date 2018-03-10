#pragma once

#include "ofxiOS.h"
#include <ARKit/ARKit.h>
#include "ofxARKit.h"
#include "Config.h"
#include "Context.h"
#include "CaptureDrawer.h"
#include "ofxAnimationPrimitives.h"
#include "CircleAnimations.h"
#include "TriAnimations.h"
#include "RectAnimations.h"
#include "ofxGui.h"

class ofApp : public ofxiOSApp {
    
public:
    
    ofApp(ARSession * session);
    ofApp();
    ~ofApp();
    
    void setup();
    void update();
    void draw();
    void drawPlanes();
    void drawAnchors();
    void drawOscInfo();
    void exit();
    
    void onPressedCaptureButton();
    void onPressedAnimateButton();
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
    ofxPanel gui;
    bool isShowGui;
    
    CaptureDrawer captureDrawer;
    ofxAnimationPrimitives::InstanceManager manager;
};


