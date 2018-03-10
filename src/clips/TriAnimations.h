//
//  TriAnimations.h
//  ofxARKit-test
//
//  Created by Shin on 2018/03/10.
//

#pragma once

#include "Config.h"

using namespace ofx::AnimationPrimitives::Easing;
using namespace Config::Graphics;

namespace Tri
{

//大きくなる
class Bigger : public ofxAnimationPrimitives::Instance
{
public:
    Bigger(FillMode fillMode = FILL)
    {
        matrix_ = $Context(AR)->processor->getLastAnchorMatrix();
        fillMode_ = fillMode;
        ofSetLineWidth(LINE_WIDTH);
    }
    
    void draw()
    {
        switch(fillMode_)
        {
            case FILL:
                ofFill();
                break;
            case NO_FILL:
                ofNoFill();
                break;
        }
        //(-100, 100), (100, 100), (0, -100)
        points[0] = ofVec2f(-SCALE * Quart::easeOut(getInvLife()), SCALE * Quart::easeOut(getInvLife()));
        points[1] = ofVec2f(SCALE * Quart::easeOut(getInvLife()), SCALE * Quart::easeOut(getInvLife()));
        points[2] = ofVec2f(0, -SCALE * Quart::easeOut(getInvLife()));
                            
        //３点が中心から大きくなっていく感じ
        ofDrawTriangle(points[0], points[1], points[2]);
    }
    
private:
    FillMode fillMode_;
    ofMatrix4x4 matrix_;
    
    ofVec2f points[3];
};
        
//線がつながる
class Line : public ofxAnimationPrimitives::Instance
{
public:
    Line()
    {
        matrix_ = $Context(AR)->processor->getLastAnchorMatrix();
        originPos[0] = ofVec2f(-SCALE, SCALE);
        originPos[1] = ofVec2f(SCALE, SCALE);
        originPos[2] = ofVec2f(0, -SCALE);
        
        targetPos[0] = originPos[1];
        targetPos[1] = originPos[2];
        targetPos[2] = originPos[0];
    }
    
    ~Line()
    {
        
    }
    
    void update()
    {
        
    }
    
    void draw()
    {
        //(-1, 1), ()
        //(-100, 100), (100, 100), (0, -100)
        ofDrawLine(originPos[0], originPos[0] + (targetPos[0] - originPos[0]) * Quart::easeOut(getInvLife()));
        ofDrawLine(originPos[1], originPos[1] + (targetPos[1] - originPos[1]) * Quart::easeOut(getInvLife()));
        ofDrawLine(originPos[2], originPos[2] + (targetPos[2] - originPos[2]) * Quart::easeOut(getInvLife()));
    }
    
private:
    ofMatrix4x4 matrix_;
    ofVec2f targetPos[3];
    ofVec2f originPos[3];
};

//回転する
class Rotate : public ofxAnimationPrimitives::Instance
{
public:
    Rotate(FillMode fillMode = FILL)
    {
        matrix_ = $Context(AR)->processor->getLastAnchorMatrix();
        rotation = ofRandom(90, 270);
    }
    
    ~Rotate()
    {
        
    }
    
    void update()
    {
        
    }
    
    void draw()
    {
        switch(fillMode_)
        {
            case FILL:
                ofFill();
                break;
            case NO_FILL:
                ofNoFill();
                break;
        }
        //(-100, 100), (100, 100), (0, -100)
        points[0] = ofVec2f(-SCALE, SCALE);
        points[1] = ofVec2f(SCALE, SCALE);
        points[2] = ofVec2f(0, -SCALE);

        ofPushMatrix();
        {
            ofRotateZ(rotation * Quart::easeOut(getInvLife()));
            ofDrawTriangle(points[0], points[1], points[2]);
        }
        ofPopMatrix();
    }
    
private:
    ofMatrix4x4 matrix_;
    FillMode fillMode_;
    
    ofVec2f points[3];
    float rotation;
};

}


