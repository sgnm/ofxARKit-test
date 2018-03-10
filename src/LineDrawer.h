//
//  LineDrawer.h
//  ofxARKit-test
//
//  Created by Shin on 2018/02/21.
//

#pragma once

#include "ofxAnimationPrimitives.h"

using namespace ofx::AnimationPrimitives::Easing;

//TODO: そもそも演出用に垂線がいるかどうか
class LineDrawer : public ofxAnimationPrimitives::Instance
{
public:
    LineDrawer(ofMatrix4x4 mat)
    {
        matrix = mat;
        ofNoFill();
        ofSetLineWidth(3);
    }
    
    ~LineDrawer()
    {
        
    }
    
    void update()
    {
        
    }
    
    void draw()
    {
        ofPushMatrix();
        ofMultMatrix(matrix);
        
        ofSetColor(255);
        ofRotate(90,0,0,1);
        
        $Context(Property)->aspect = ARCommon::getNativeAspectRatio();
        
        
//        switch($Context(OSC)->address)
//        {
//            case "/Note1":
//
//                break;
//        }
        
        ofPopMatrix();
    }
private:
    ofMatrix4x4 matrix;
};
