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
    Bigger()
    {
        radius = $Context(Property)->scale * 50;
//        rotation = ofRandom(0, 360);
        
        bool isUpward = (int)ofRandom(2);
        if(isUpward)
        {
            //上向いてるとき
            for (int i = 0; i < 3; i++)
            {
                points[i] = ofVec2f(cos(ofDegToRad(-90 + i*120)) * radius, sin(ofDegToRad(-90 + i*120)) * radius);
            }
        }
        else
        {
            //下向いてるとき
            for (int i = 0; i < 3; i++)
            {
                points[i] = ofVec2f(cos(ofDegToRad(90 + i*120)) * radius, sin(ofDegToRad(90 + i*120)) * radius);
            }
        }
    }
    
    void draw()
    {
        //元
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 255));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
//            ofRotateZ(rotation);
            $Context(Property)->path.triangle(points[0], points[1], points[2]);
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //コピー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2 - $Context(Property)->margin);
            ofRotateZ(180);
//            ofRotateZ(-rotation);
            $Context(Property)->pathMir.triangle(points[0], points[1], points[2]);
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
    ofVec2f points[3];
    float radius;
    float rotation;
};
        
//線がつながる
class Line : public ofxAnimationPrimitives::Instance
{
public:
    Line()
    {
        radius = $Context(Property)->scale * 50;
        
        bool isUpward = (int)ofRandom(2);
        if(isUpward)
        {
            //上向いてるとき
            for (int i = 0; i < 3; i++)
            {
                originPos[i] = ofVec2f(cos(ofDegToRad(-90 + i*120)) * radius, sin(ofDegToRad(-90 + i*120)) * radius);
            }
        }
        else
        {
            //下向いてるとき
            for (int i = 0; i < 3; i++)
            {
                originPos[i] = ofVec2f(cos(ofDegToRad(90 + i*120)) * radius, sin(ofDegToRad(90 + i*120)) * radius);
            }
        }
        
        targetPos[0] = originPos[1];
        targetPos[1] = originPos[2];
        targetPos[2] = originPos[0];
    }
    
    void draw()
    {
        //元
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 255));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            $Context(Property)->path.moveTo(originPos[0]);
            $Context(Property)->path.lineTo(originPos[0] + (targetPos[0] - originPos[0]) * Quart::easeOut(getInvLife()));
            $Context(Property)->path.moveTo(originPos[1]);
            $Context(Property)->path.lineTo(originPos[1] + (targetPos[1] - originPos[1]) * Quart::easeOut(getInvLife()));
            $Context(Property)->path.moveTo(originPos[2]);
            $Context(Property)->path.lineTo(originPos[2] + (targetPos[2] - originPos[2]) * Quart::easeOut(getInvLife()));
            $Context(Property)->path.close();
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //コピー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2 - $Context(Property)->margin);
            ofRotateZ(180);
            $Context(Property)->pathMir.moveTo(originPos[0]);
            $Context(Property)->pathMir.lineTo(originPos[0] + (targetPos[0] - originPos[0]) * Quart::easeOut(getInvLife()));
            $Context(Property)->pathMir.moveTo(originPos[1]);
            $Context(Property)->pathMir.lineTo(originPos[1] + (targetPos[1] - originPos[1]) * Quart::easeOut(getInvLife()));
            $Context(Property)->pathMir.moveTo(originPos[2]);
            $Context(Property)->pathMir.lineTo(originPos[2] + (targetPos[2] - originPos[2]) * Quart::easeOut(getInvLife()));
            $Context(Property)->pathMir.close();
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
    ofVec2f targetPos[3];
    ofVec2f originPos[3];
    float radius;
};

//回転する
class Rotate : public ofxAnimationPrimitives::Instance
{
public:
    Rotate()
    {
        float radius = $Context(Property)->scale * 50;
        rotation = ofRandom(90, 270);
        
        bool isUpward = (int)ofRandom(2);
        if(isUpward)
        {
            //上向いてるとき
            for (int i = 0; i < 3; i++)
            {
                points[i] = ofVec2f(cos(ofDegToRad(-90 + i*120)) * radius, sin(ofDegToRad(-90 + i*120)) * radius);
            }
        }
        else
        {
            //下向いてるとき
            for (int i = 0; i < 3; i++)
            {
                points[i] = ofVec2f(cos(ofDegToRad(90 + i*120)) * radius, sin(ofDegToRad(90 + i*120)) * radius);
            }
        }
    }
    
    void draw()
    {
        //元
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 255));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(rotation);
            $Context(Property)->path.triangle(points[0], points[1], points[2]);
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //コピー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2 - $Context(Property)->margin);
            ofRotateZ(180);
            ofRotateZ(-rotation);
            $Context(Property)->pathMir.triangle(points[0], points[1], points[2]);
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
    ofVec2f points[3];
    float rotation;
};
    
//切り抜かれた図形が描画される
class CutOut : public ofxAnimationPrimitives::Instance
{
public:
    CutOut()
    {
        float radius = $Context(Property)->scale * 50;
        bool isUpward = (int)ofRandom(2);
        if(isUpward)
        {
            //上向いてるとき
            for (int i = 0; i < 3; i++)
            {
                bigPoints[i] = ofVec2f(cos(ofDegToRad(-90 + i*120)) * radius, sin(ofDegToRad(-90 + i*120)) * radius);
            }
        }
        else
        {
            //下向いてるとき
            for (int i = 0; i < 3; i++)
            {
                bigPoints[i] = ofVec2f(cos(ofDegToRad(90 + i*120)) * radius, sin(ofDegToRad(90 + i*120)) * radius);
            }
        }
        
        smallPoints[0] = bigPoints[0] / 2;
        smallPoints[1] = bigPoints[1] / 2;
        smallPoints[2] = bigPoints[2] / 2;
    }
    
    void update()
    {
        smallPoints[0] = bigPoints[0] / 2 + bigPoints[0] * Quart::easeIn(getInvLife());
        smallPoints[1] = bigPoints[1] / 2 + bigPoints[1] * Quart::easeIn(getInvLife());
        smallPoints[2] = bigPoints[2] / 2 + bigPoints[2] * Quart::easeIn(getInvLife());
    }
    
    void draw()
    {
        //元
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 255));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            $Context(Property)->path.triangle(bigPoints[0], bigPoints[1], bigPoints[2]);
            $Context(Property)->path.triangle(smallPoints[0], smallPoints[1], smallPoints[2]);
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //ミラー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2 - $Context(Property)->margin);
            ofRotateZ(180);
            $Context(Property)->pathMir.triangle(bigPoints[0], bigPoints[1], bigPoints[2]);
            $Context(Property)->pathMir.triangle(smallPoints[0], smallPoints[1], smallPoints[2]);
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
    ofVec2f bigPoints[3];
    ofVec2f smallPoints[3];
};
    
//切り抜きしながら回転
class CutOutRotate : public ofxAnimationPrimitives::Instance
{
public:
    CutOutRotate()
    {
        float radius = $Context(Property)->scale * 50;
        float rotation = ofRandom(90, 270);
        bool isUpward = (int)ofRandom(2);
        if(isUpward)
        {
            //上向いてるとき
            for (int i = 0; i < 3; i++)
            {
                bigPoints[i] = ofVec2f(cos(ofDegToRad(-90 + i*120)) * radius, sin(ofDegToRad(-90 + i*120)) * radius);
            }
        }
        else
        {
            //下向いてるとき
            for (int i = 0; i < 3; i++)
            {
                bigPoints[i] = ofVec2f(cos(ofDegToRad(90 + i*120)) * radius, sin(ofDegToRad(90 + i*120)) * radius);
            }
        }
        
        smallPoints[0] = bigPoints[0] / 2;
        smallPoints[1] = bigPoints[1] / 2;
        smallPoints[2] = bigPoints[2] / 2;
    }
    
    void update()
    {
        smallPoints[0] = bigPoints[0] / 2 + bigPoints[0] * Quart::easeIn(getInvLife());
        smallPoints[1] = bigPoints[1] / 2 + bigPoints[1] * Quart::easeIn(getInvLife());
        smallPoints[2] = bigPoints[2] / 2 + bigPoints[2] * Quart::easeIn(getInvLife());
    }
    
    void draw()
    {
        //元
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 255));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(rotation);
            $Context(Property)->path.triangle(bigPoints[0], bigPoints[1], bigPoints[2]);
            $Context(Property)->path.triangle(smallPoints[0], smallPoints[1], smallPoints[2]);
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //ミラー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2 - $Context(Property)->margin);
            ofRotateZ(180);
            ofRotateZ(-rotation);
            $Context(Property)->pathMir.triangle(bigPoints[0], bigPoints[1], bigPoints[2]);
            $Context(Property)->pathMir.triangle(smallPoints[0], smallPoints[1], smallPoints[2]);
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
    ofVec2f bigPoints[3];
    ofVec2f smallPoints[3];
    float rotation;
};

}


