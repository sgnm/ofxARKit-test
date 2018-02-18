#pragma once

#include "ofxiOS.h"
#include <ARKit/ARKit.h>
#include "ofxARKit.h"
#include "Context.h"
#include "Config.h"
#include "CaptureDrawer.h"

class ofApp : public ofxiOSApp {
    
public:
    
    ofApp(ARSession * session);
    ofApp();
    ~ofApp();
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void touchDown(ofTouchEventArgs &touch);
    void touchMoved(ofTouchEventArgs &touch);
    void touchUp(ofTouchEventArgs &touch);
    void touchDoubleTap(ofTouchEventArgs &touch);
    void touchCancelled(ofTouchEventArgs &touch);
    
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
    
    ofTrueTypeFont font;
    
    CaptureDrawer captureDrawer;
    
    //audio
    void audioIn(float * input, int bufferSize, int nChannels);
    
    int    initialBufferSize;
    int    sampleRate;
    int    drawCounter;
    int bufferCounter;
    float * buffer;
    
    float smoothedVol;
    float scaledVol;
};


