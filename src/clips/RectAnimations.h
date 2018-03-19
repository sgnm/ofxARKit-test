//
//  RectAnimations.h
//  ofxARKit-test
//
//  Created by Shin on 2018/03/10.
//

#include "Config.h"

using namespace ofx::AnimationPrimitives::Easing;
using namespace Config::Graphics;

namespace Rectangle
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
        //(-100, -100), (-100, 100), (100, 100), (100, -100)
//        points[0] = ofVec2f(-SCALE * Quart::easeOut(getInvLife()), -SCALE * Quart::easeOut(getInvLife()));
//        points[1] = ofVec2f(-SCALE * Quart::easeOut(getInvLife()), SCALE * Quart::easeOut(getInvLife()));
//        points[1] = ofVec2f(SCALE * Quart::easeOut(getInvLife()), SCALE * Quart::easeOut(getInvLife()));
//        points[2] = ofVec2f(0, -SCALE * Quart::easeOut(getInvLife()));
        
        //4点が中心から大きくなっていく感じ
        ofPushMatrix();
        ofPushStyle();
        {
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofDrawRectangle(0, 0, SCALE * Quart::easeOut(getInvLife()), SCALE * Quart::easeOut(getInvLife()));
        }
        ofPopStyle();
        ofPopMatrix();
    }
    
private:
    FillMode fillMode_;
    ofMatrix4x4 matrix_;
    
    ofVec2f points[4];
};
    
//線がつながる
class Line : public ofxAnimationPrimitives::Instance
{
public:
    Line()
    {
        matrix_ = $Context(AR)->processor->getLastAnchorMatrix();
        originPos[0] = ofVec2f(-SCALE, -SCALE);
        originPos[1] = ofVec2f(-SCALE, SCALE);
        originPos[2] = ofVec2f(SCALE, SCALE);
        originPos[3] = ofVec2f(SCALE, -SCALE);
        
        targetPos[0] = originPos[1];
        targetPos[1] = originPos[2];
        targetPos[2] = originPos[3];
        targetPos[3] = originPos[0];
    }
    
    ~Line()
    {
        
    }
    
    void update()
    {
        
    }
    
    void draw()
    {
        //(-100, -100), (-100, 100), (100, 100), (100, -100)
        ofDrawLine(originPos[0], originPos[0] + (targetPos[0] - originPos[0]) * Quart::easeOut(getInvLife()));
        ofDrawLine(originPos[1], originPos[1] + (targetPos[1] - originPos[1]) * Quart::easeOut(getInvLife()));
        ofDrawLine(originPos[2], originPos[2] + (targetPos[2] - originPos[2]) * Quart::easeOut(getInvLife()));
        ofDrawLine(originPos[3], originPos[3] + (targetPos[3] - originPos[3]) * Quart::easeOut(getInvLife()));
    }
    
private:
    ofMatrix4x4 matrix_;
    ofVec2f targetPos[4];
    ofVec2f originPos[4];
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
        
        ofPushMatrix();
        ofPushStyle();
        {
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofRotateZ(rotation * Quart::easeOut(getInvLife()));
            ofDrawRectangle(0, 0, SCALE * Quart::easeOut(getInvLife()), SCALE * Quart::easeOut(getInvLife()));
        }
        ofPopStyle();
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
    }
    
    ~CutOut()
    {
        
    }
    
    void update()
    {
        
    }
    
    void draw()
    {
        path.clear();
        path.translate(ofPoint(SCALE/2, SCALE/2)); //中心に移動
        path.setFillColor(ofColor(255));
        //大
        path.rectangle(-SCALE/2, -SCALE/2, SCALE, SCALE);
        //小
        path.rectangle(-SCALE/4 - SCALE/4 * Quart::easeIn(getInvLife()), -SCALE/4 - SCALE/4 * Quart::easeIn(getInvLife()), SCALE/2 + SCALE/2 * Quart::easeIn(getInvLife()), SCALE/2 + SCALE/2 * Quart::easeIn(getInvLife()));
        
        path.draw();
//        ofDrawRectangle(0, 0, SCALE * Quart::easeOut(getInvLife()), SCALE * Quart::easeOut(getInvLife()));
    }
    
private:
    ofPath path;
};
    
//切り抜きしながら回転
class CutOutRotate : public ofxAnimationPrimitives::Instance
{
public:
    CutOutRotate()
    {
        rotation = ofRandom(90, 270);
    }
    
    ~CutOutRotate()
    {
        
    }
    
    void update()
    {
        
    }
    
    void draw()
    {
        path.clear();
        path.translate(ofPoint(SCALE/2, SCALE/2)); //中心に移動
        path.setFillColor(ofColor(255));
        //大
        path.rectangle(-SCALE/2, -SCALE/2, SCALE, SCALE);
        //小
        path.rectangle(-SCALE/4 - SCALE/4 * Quart::easeIn(getInvLife()), -SCALE/4 - SCALE/4 * Quart::easeIn(getInvLife()), SCALE/2 + SCALE/2 * Quart::easeIn(getInvLife()), SCALE/2 + SCALE/2 * Quart::easeIn(getInvLife()));
        
        //回転
        path.rotate(rotation * Quart::easeOut(getInvLife()), ofVec3f(0, 0, 1));
        
        path.draw();
        //        ofDrawRectangle(0, 0, SCALE * Quart::easeOut(getInvLife()), SCALE * Quart::easeOut(getInvLife()));
    }
    
private:
    ofPath path;
    float rotation;
};

}
