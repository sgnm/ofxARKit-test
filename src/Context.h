//
//  Context.h
//  ofxARKit-test
//
//  Created by Shin on 2018/02/18.
//

#pragma once

#include "Config.h"
#include "ofxGlobalContext.h"
#include "ofxGui.h"

class Property : public ofxGlobalContext::Context
{
public:
    float aspect;
    float volume;
    ofxFloatSlider scale;
    ofxIntSlider margin;
    Config::Graphics::DrawMode drawMode;
    ofPath path;
    ofPath pathMir;
    
    Property()
    {
        
    }
};

class AR : public ofxGlobalContext::Context
{
public:
    ofCamera camera;
    ARSession *session;
    ARRef processor; //ARProcessorの参照
    
    AR()
    {
        //SFormatに設定を書き込んで、新しくsessionを始めるみたいな
        ARCore::SFormat format;
        format.enableLighting();
        session = ARCore::generateNewSession(format);
        
        processor = ARProcessor::create(session);
        processor->setup();
    }
    
    void update()
    {
        
    }
};

#include "ofxOSC.h"

class OSC : public ofxGlobalContext::Context
{
public:
    ofxOscReceiver receiver;
    string address = "";
    float val;
//    int track = 0;
//    int note = 0;
    
    OSC()
    {
        receiver.setup(Config::OSC::PORT);
    }
    
    void update()
    {
        while(receiver.hasWaitingMessages())
        {
            // get the next message
            ofxOscMessage m;
            receiver.getNextMessage(m);
            address = m.getAddress();
            val = m.getArgAsFloat(0);
//            track = m.getArgAsInt(0);
//            note = m.getArgAsInt(1);
        }
    }
};

class Timer : public ofxGlobalContext::Context
{
public:
    float tick;
    float elapsed;
    float rate;
    
    Timer()
    {
        elapsed = 0;
        rate = 0;
    }
    
    void update()
    {
        float inv_target_frame = (1. / 60);
        tick = ofGetLastFrameTime();
        rate = tick / inv_target_frame;
        elapsed += tick;
    }
};
