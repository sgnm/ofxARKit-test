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
    
//切り抜かれた図形が描画される
class CutOut : public ofxAnimationPrimitives::Instance
{
public:
    CutOut()
    {
        //(-100, 100), (100, 100), (0, -100)
        bigPoints[0] = ofVec2f(-SCALE/2, SCALE/2);
        bigPoints[1] = ofVec2f(SCALE/2, SCALE/2);
        bigPoints[2] = ofVec2f(0, -SCALE/2);
        
        smallPoints[0] = ofVec2f(-SCALE/4, SCALE/4);
        smallPoints[1] = ofVec2f(SCALE/4, SCALE/4);
        smallPoints[2] = ofVec2f(0, -SCALE/4);
    }
    
    ~CutOut()
    {
        
    }
    
    void update()
    {
        smallPoints[0] = ofVec2f(-SCALE/4 - SCALE/4 * Quart::easeIn(getInvLife()), SCALE/4 + SCALE/4 * Quart::easeIn(getInvLife()));
        smallPoints[1] = ofVec2f(SCALE/4 + SCALE/4 * Quart::easeIn(getInvLife()), SCALE/4 + SCALE/4 * Quart::easeIn(getInvLife()));
        smallPoints[2] = ofVec2f(0, -SCALE/4 - SCALE/4 * Quart::easeIn(getInvLife()));
    }
    
    void draw()
    {
        path.clear();
        path.translate(ofPoint(SCALE/2, SCALE/2)); //中心に移動
        path.setFillColor(ofColor(255));
        //大
        path.triangle(bigPoints[0], bigPoints[1], bigPoints[2]);
        //小
        path.triangle(smallPoints[0], smallPoints[1], smallPoints[2]);
        
        path.draw();
        //        ofDrawRectangle(0, 0, SCALE * Quart::easeOut(getInvLife()), SCALE * Quart::easeOut(getInvLife()));
    }
    
private:
    ofPath path;
    ofVec2f bigPoints[3];
    ofVec2f smallPoints[3];
};
    
//切り抜きしながら回転
class CutOutRotate : public ofxAnimationPrimitives::Instance
{
public:
    CutOutRotate()
    {
        bigPoints[0] = ofVec2f(-SCALE/2, -SCALE/4);
        bigPoints[1] = ofVec2f(SCALE/2, -SCALE/4);
        bigPoints[2] = ofVec2f(0, SCALE/2 * ROUTE3 -SCALE/4);
        
        smallPoints[0] = bigPoints[0] / 2;
        smallPoints[1] = bigPoints[1] / 2;
        smallPoints[2] = bigPoints[2] / 2;
        
        //TODO: 反対にもランダムに回転できるようにする
        rotation = ofRandom(90, 270);
    }
    
    ~CutOutRotate()
    {
        
    }
    
    void update()
    {
        smallPoints[0] = bigPoints[0] / 2 + bigPoints[0] * Quart::easeIn(getInvLife());
        smallPoints[1] = bigPoints[1] / 2 + bigPoints[1] * Quart::easeIn(getInvLife());
        smallPoints[2] = bigPoints[2] / 2 + bigPoints[2] * Quart::easeIn(getInvLife());
//        smallPoints[0] = ofVec2f(-SCALE/4 - SCALE/4 * Quart::easeIn(getInvLife()), SCALE/4 + SCALE/4 * Quart::easeIn(getInvLife()));
//        smallPoints[1] = ofVec2f(SCALE/4 + SCALE/4 * Quart::easeIn(qgetInvLife()), SCALE/4 + SCALE/4 * Quart::easeIn(getInvLife()));
//        smallPoints[2] = ofVec2f(0, -SCALE/4 - SCALE/4 * Quart::easeIn(getInvLife()));
    }
    
    void draw()
    {
        path.clear();
        path.translate(ofPoint(SCALE/2, SCALE/2)); //中心に移動
        path.setFillColor(ofColor(255));
//        path.circle(0, 0, 0.05);
//        path.circle(SCALE/2, SCALE/2, 0.05); //右上に表示されたのでy軸上プラス
        //大
        path.triangle(bigPoints[0], bigPoints[1], bigPoints[2]);
        //小
        path.triangle(smallPoints[0], smallPoints[1], smallPoints[2]);
        //回転
        path.rotate(rotation * Quart::easeOut(getInvLife()), ofVec3f(0, 0, 1));
        
        path.draw();
        //        ofDrawRectangle(0, 0, SCALE * Quart::easeOut(getInvLife()), SCALE * Quart::easeOut(getInvLife()));
    }
    
private:
    ofPath path;
    ofVec2f bigPoints[3];
    ofVec2f smallPoints[3];
    float rotation;
};

}


