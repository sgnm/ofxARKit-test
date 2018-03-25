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
    Bigger()
    {
        size = $Context(Property)->scale * 50;
    }
    
    void draw()
    {
        //元
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 255));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            float v = Quart::easeOut(getInvLife());
            $Context(Property)->path.rectangle(-size/2 * v, -size/2 * v, size * v, size * v);
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //ミラー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2 - $Context(Property)->margin, ofGetHeight()/2);
            
            float v = Quart::easeOut(getInvLife());
            $Context(Property)->pathMir.rectangle(-size/2 * v, -size/2 * v, size * v, size * v);
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
    float size;
};
    
//線がつながる
class Line : public ofxAnimationPrimitives::Instance
{
public:
    Line()
    {
        size = $Context(Property)->scale * 50;
        originPos[0] = ofVec2f(-size, -size);
        originPos[1] = ofVec2f(-size, size);
        originPos[2] = ofVec2f(size, size);
        originPos[3] = ofVec2f(size, -size);
        
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
            $Context(Property)->path.moveTo(originPos[3]);
            $Context(Property)->path.lineTo(originPos[3] + (targetPos[3] - originPos[3]) * Quart::easeOut(getInvLife()));
            $Context(Property)->path.close();
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //コピー
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2 - $Context(Property)->margin, ofGetHeight()/2);
            
            $Context(Property)->pathMir.moveTo(originPos[0]);
            $Context(Property)->pathMir.lineTo(originPos[0] + (targetPos[0] - originPos[0]) * Quart::easeOut(getInvLife()));
            $Context(Property)->pathMir.moveTo(originPos[1]);
            $Context(Property)->pathMir.lineTo(originPos[1] + (targetPos[1] - originPos[1]) * Quart::easeOut(getInvLife()));
            $Context(Property)->pathMir.moveTo(originPos[2]);
            $Context(Property)->pathMir.lineTo(originPos[2] + (targetPos[2] - originPos[2]) * Quart::easeOut(getInvLife()));
            $Context(Property)->pathMir.moveTo(originPos[3]);
            $Context(Property)->pathMir.lineTo(originPos[3] + (targetPos[3] - originPos[3]) * Quart::easeOut(getInvLife()));
            $Context(Property)->pathMir.close();
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
        
    }
    
private:
    ofVec2f targetPos[4];
    ofVec2f originPos[4];
    float size;
};
    
//回転する
class Rotate : public ofxAnimationPrimitives::Instance
{
public:
    Rotate()
    {
        size = $Context(Property)->scale * 50;
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
        //元
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 255));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            float v = Quart::easeOut(getInvLife());
            ofRotateZ(rotation * v);
            $Context(Property)->path.rectangle(-size/2 * v, -size/2 * v, size * v, size * v);
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //ミラー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2 - $Context(Property)->margin, ofGetHeight()/2);
            
            float v = Quart::easeOut(getInvLife());
            ofRotateZ(-rotation * v);
            $Context(Property)->pathMir.rectangle(-size/2 * v, -size/2 * v, size * v, size * v);
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
    float size;
    float rotation;
};
    
//切り抜かれた図形が描画される
class CutOut : public ofxAnimationPrimitives::Instance
{
public:
    CutOut()
    {
        size = $Context(Property)->scale * 50;
    }
    
    ~CutOut()
    {
        
    }
    
    void update()
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
            float v = Quart::easeIn(getInvLife());
//            ofRotateZ(rotation * v);
            $Context(Property)->path.rectangle(-size/2, -size/2, size, size);
            $Context(Property)->path.rectangle(-size/4 - size/4 * v, -size/4 - size/4 * v, size/2 + size/2 * v, size/2 + size/2 * v);
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //ミラー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2 - $Context(Property)->margin, ofGetHeight()/2);
            
            float v = Quart::easeIn(getInvLife());
            //            ofRotateZ(rotation * v);
            $Context(Property)->pathMir.rectangle(-size/2, -size/2, size, size);
            $Context(Property)->pathMir.rectangle(-size/4 - size/4 * v, -size/4 - size/4 * v, size/2 + size/2 * v, size/2 + size/2 * v);
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
    float size;
};
    
//切り抜きしながら回転
class CutOutRotate : public ofxAnimationPrimitives::Instance
{
public:
    CutOutRotate()
    {
        size = $Context(Property)->scale * 50;
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
        //元
        $Context(Property)->path.clear();
        $Context(Property)->path.setColor(ofColor(255, Quart::easeOut(getLife()) * 255));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(rotation * Quart::easeOut(getInvLife()));
            float v = Quart::easeIn(getInvLife());
            $Context(Property)->path.rectangle(-size/2, -size/2, size, size);
            $Context(Property)->path.rectangle(-size/4 - size/4 * v, -size/4 - size/4 * v, size/2 + size/2 * v, size/2 + size/2 * v);
            $Context(Property)->path.draw();
        }
        ofPopMatrix();
        
        //ミラー
        $Context(Property)->pathMir.clear();
        $Context(Property)->pathMir.setColor(ofColor(255, Quart::easeOut(getLife()) * 100));
        ofPushMatrix();
        {
            ofTranslate(ofGetWidth()/2 - $Context(Property)->margin, ofGetHeight()/2);
            
            ofRotateZ(-rotation * Quart::easeOut(getInvLife()));
            float v = Quart::easeIn(getInvLife());
            $Context(Property)->pathMir.rectangle(-size/2, -size/2, size, size);
            $Context(Property)->pathMir.rectangle(-size/4 - size/4 * v, -size/4 - size/4 * v, size/2 + size/2 * v, size/2 + size/2 * v);
            $Context(Property)->pathMir.draw();
        }
        ofPopMatrix();
    }
    
private:
    float rotation;
    float size;
};

}
