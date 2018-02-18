#pragma once

#include "ofxiOS.h"
#include <ARKit/ARKit.h>
#include "ofxARKit.h"

//w: 640 /h: 1136
const float WIDTH = 640.0;
const float HEIGHT = 1136.0;
const int MAX_NUM_ANCHORS = 90;

class ofApp : public ofxiOSApp {
    
public:
    
    ofApp (ARSession * session);
    ofApp();
    ~ofApp ();
    
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
    
    vector < matrix_float4x4 > mats;
    vector<ARAnchor*> anchors;
    ofCamera camera;
    ofTrueTypeFont font;
    ofImage img;
    
    // ====== AR STUFF ======== //
    ARSession * session;
    ARRef processor; //ARProcessorの参照
    
    // custom by sgnm
    vector<ofFbo> fbos;
    float aspect;
    
    //shader
    ofShader shader;
    vector<ofShader> shaders;
    
    //audio
    void audioIn(float * input, int bufferSize, int nChannels);
    
    int    initialBufferSize;
    int    sampleRate;
    int    drawCounter;
    int bufferCounter;
    float * buffer;
    
    float smoothedVol;
    float scaledVol;
    
    int shaderIndex = 0;
    bool isPostEffect = true;
};


