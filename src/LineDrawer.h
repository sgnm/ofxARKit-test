//
//  LineDrawer.h
//  ofxARKit-test
//
//  Created by Shin on 2018/02/21.
//

#pragma once

#include "ofxAnimationPrimitives.h"

using namespace ofx::AnimationPrimitives::Easing;

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
        $Context(AR)->camera.begin();
        $Context(AR)->processor->setARCameraMatrices();
        
        ofPushMatrix();
        ofMultMatrix(matrix);
        
        ofSetColor(255);
        ofRotate(90,0,0,1);
        
        $Context(Property)->aspect = ARCommon::getNativeAspectRatio();
        
        ofSetColor(255, 255.0);
        ofDrawCircle(0, 0, -1.0 + Quart::easeOut(getLife()), 0.1 * Quart::easeOut(getLife()));
        //getLife: 1 -> 0, out: -0.0 -> -1.0
        
        //TODO: vboMeshにしてcircleとかもその点に描けるようにする
        static ofPoint pos1(0, 0, -0.2), pos2(0, 0, -0.2);
        pos2.z += getInvLife() * 2.0;
        ofDrawLine(pos1, pos2);
        
        
//        switch($Context(OSC)->address)
//        {
//            case "/Note1":
//
//                break;
//        }
        
        ofPopMatrix();
        
        $Context(AR)->camera.end();
    }
private:
    ofMatrix4x4 matrix;
};
