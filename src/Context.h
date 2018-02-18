//
//  Context.h
//  ofxARKit-test
//
//  Created by Shin on 2018/02/18.
//

#pragma once

#include "ofxGlobalContext.h"

class Property : public ofxGlobalContext::Context
{
public:
    float aspect;
    float volume;
    
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
