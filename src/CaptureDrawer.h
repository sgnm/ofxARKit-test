//
//  CaptureDrawer.h
//  ofxARKit-test
//
//  Created by Shin on 2018/02/18.
//

#pragma once

enum EffectType
{
    Normal = 0,
    Mono,
    Invert,
    Convergence,
    CutSlider,
    Outline
};

class CaptureDrawer
{
    vector<ofFbo> capturedFbos;
    ofShader shader;
    bool isPostEffect = true;
    float volumeThreshold = 0.02;
    EffectType effectType_;
    
public:
    
    void setup()
    {
#ifdef TARGET_OPENGLES
        shader.load("shaders/normal");
#else
        ofLogError("Set target to OpenGLES!");
#endif
    }
    
    void update()
    {
        
    }
    
    void draw(int index)
    {
        if(isPostEffect)
        {
            if($Context(Property)->volume > volumeThreshold)
            {
                setRandomEffect();
            }
        }
        else
        {
            shader.load("shaders/normal");
        }
            
        shader.begin();
        {
            //TODO: stepじゃなくてOSC&押しっぱなしとかにする。effect trueにしといて音に反応してエフェクトかかるみたいな？
            shader.setUniform1f("rand", ofRandom(1));
            shader.setUniform2f("resolution", Config::Window::WIDTH, Config::Window::HEIGHT);
            shader.setUniformTexture("texture", capturedFbos[index].getTexture(), 0);
            
            capturedFbos[index].draw(ofPoint(-$Context(Property)->aspect/8, -0.125), $Context(Property)->aspect/4, 0.25);
        }
        shader.end();
    }
    
    void addCapturedFbo(const ofFbo &capturedFbo)
    {
        ofFbo fbo;
        fbo.allocate(Config::Window::WIDTH, Config::Window::HEIGHT, GL_RGBA);
        fbo.begin();
        {
            //w: 640 /h: 1136
            capturedFbo.draw(0, 0, Config::Window::WIDTH, Config::Window::HEIGHT);
        }
        fbo.end();
        
        capturedFbos.emplace_back(fbo);
    }
    
    void enablePostEffect()
    {
        isPostEffect = true;
    }
    
    void disablePostEffect()
    {
        isPostEffect = false;
    }
    
    void setEffect(EffectType effectType)
    {
        switch(effectType)
        {
            case Normal:
                shader.load("shaders/normal");
                break;
            case Mono:
                shader.load("shaders/mono");
                break;
            case Invert:
                shader.load("shaders/invert");
                break;
            case Convergence:
                shader.load("shaders/convergence");
                break;
            case CutSlider:
                shader.load("shaders/cut_slider");
                break;
            case Outline:
                shader.load("shaders/outline");
                break;
        }
        
        effectType_ = effectType;
    }
    
    void setRandomEffect()
    {
        static EffectType effectType = Normal;
        while (effectType_ == effectType)
        {
            effectType = static_cast<EffectType>(rand() % Outline);
        }
        setEffect(effectType);
    }
};
