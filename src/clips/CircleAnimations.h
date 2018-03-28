//
//  Bigger.h
//  ofxARKit-test
//
//  Created by Shin on 2018/02/24.
//

#pragma once

#include "Config.h"

using namespace ofx::AnimationPrimitives::Easing;
using namespace Config::Graphics;

namespace Circle
{
    
//マスクが大きくなる
class CutOut : public ofxAnimationPrimitives::Instance
{
    //TODO:
    /* 輪郭がギザギザしてる
     * 外枠がアニメーション時に全く大きくなってない
     * フェードアウトが少し早いかも→小さい円が大きい円に届いていない
     */
    
public:
    CutOut()
    {
    }
    
    void draw()
    {
        float outerRadius = ofClamp($Context(Property)->scale * 50 + Back::easeIn(getInvLife()) * -1.0, $Context(Property)->scale * 50, $Context(Property)->scale * 50 * 1.2);
        float innerRadius = ofClamp(20 + $Context(Property)->scale * 50 * Quart::easeIn(getInvLife()), 0.0, $Context(Property)->scale * 50);
        
        //元
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 255));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            $Context(Property)->path.circle(0, 0, outerRadius); //大
            $Context(Property)->path.circle(0, 0, innerRadius); //小
            $Context(Property)->path.close();
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //ミラー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2 - $Context(Property)->margin, ofGetHeight()/2);
            
            $Context(Property)->pathMir.circle(0, 0, outerRadius); //大
            $Context(Property)->pathMir.circle(0, 0, innerRadius); //小
            $Context(Property)->path.close();
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
};
    
//大きくなる
class Bigger : public ofxAnimationPrimitives::Instance
{
public:
    Bigger()
    {
    }
    
    void draw()
    {
        //元
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 255));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            $Context(Property)->path.circle(0, 0, $Context(Property)->scale * 50 * Quart::easeOut(getInvLife())); //大
            $Context(Property)->path.close();
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //ミラー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2 - $Context(Property)->margin, ofGetHeight()/2);
            
            $Context(Property)->pathMir.circle(0, 0, $Context(Property)->scale * 50 * Quart::easeOut(getInvLife())); //大
            $Context(Property)->path.close();
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
};

//小さくなる
class Smaller : public ofxAnimationPrimitives::Instance
{
public:
    Smaller()
    {
    }
    
    void draw()
    {
        //小さくなる必要ない。大きいままfade outした方がきれい
        //元
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 255));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            $Context(Property)->path.circle(0, 0, $Context(Property)->scale * 50); //大
            $Context(Property)->path.close();
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //ミラー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2 - $Context(Property)->margin, ofGetHeight()/2);
            
            $Context(Property)->pathMir.circle(0, 0, $Context(Property)->scale * 50); //大
            $Context(Property)->path.close();
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
};

}
