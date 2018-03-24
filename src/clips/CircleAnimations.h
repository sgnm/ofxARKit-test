//
//  Bigger.h
//  ofxARKit-test
//
//  Created by Shin on 2018/02/24.
//

#pragma once

#include "Config.h"
#include "ofxRing.h"

using namespace ofx::AnimationPrimitives::Easing;
using namespace Config::Graphics;

namespace Circle
{

//マスクが大きくなる
class Anim1 : public ofxAnimationPrimitives::Instance
{
public:
    Anim1(FillMode fillMode = FILL)
    {
        ring.setup();
    }
    
    void draw()
    {
//        ofSetColor(255, getLife() * 255);
        
        float outRad = ofClamp(SCALE + Back::easeIn(getInvLife()) * -1.0, SCALE, 0.3);
        float inRad = ofClamp(0.2 + SCALE * Quart::easeIn(getInvLife()), 0.0, SCALE);
        ring.setOuterRadius(outRad);
        ring.setInnerRadius(inRad);
        
        ring.draw();
    }
    
private:
    ofxRing ring;
};
    
//大きくなる
class Bigger : public ofxAnimationPrimitives::Instance
{
public:
    Bigger(FillMode fillMode = FILL)
    {
//        matrix_ = $Context(AR)->processor->getLastAnchorMatrix();
        fillMode_ = fillMode;
        ofSetLineWidth(LINE_WIDTH);
    }
    
    void draw()
    {
//        ofPushMatrix();
//        ofMultMatrix(matrix_);
//        ofRotate(90,0,0,1);
        // === draw begin ===
        
//        ofSetColor(255, getLife() * 255);
        //TODO: global depth
        switch(fillMode_)
        {
            case FILL:
                ofFill();
                break;
            case NO_FILL:
                ofNoFill();
                break;
        }
//        ofDrawCircle(0, 0, SCALE * Quart::easeOut(getInvLife()));
        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, $Context(Property)->scale * 50 * Quart::easeOut(getInvLife()));
        
        // === draw end ===
//        ofPopMatrix();
    }
    
private:
    FillMode fillMode_;
    ofMatrix4x4 matrix_;
};

//小さくなる
class Smaller : public ofxAnimationPrimitives::Instance
{
public:
    Smaller(FillMode fillMode = FILL)
    {
        fillMode_ = fillMode;
        ofSetLineWidth(LINE_WIDTH);
    }
    
    void draw()
    {
        
//        ofSetColor(255, getLife() * 255);
        //TODO: global depth
        switch(fillMode_)
        {
            case FILL:
                ofFill();
                break;
            case NO_FILL:
                ofNoFill();
                break;
        }
//        ofDrawCircle(0, 0, SCALE * Quart::easeOut(getLife()));
        //小さくなる必要ない。大きいままfade outした方がきれい
        ofDrawCircle(0, 0, SCALE);
    }
    
private:
    FillMode fillMode_;
};

//

}
