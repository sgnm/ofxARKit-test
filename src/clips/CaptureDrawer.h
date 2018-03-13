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

//TODO: captureDrawerもinstance化して、初期化でshader, matrix等自由効かせられるようにする
class CaptureDrawer : public ofxAnimationPrimitives::Instance
{
    ofFbo capturedFbo_;
    ofShader shader;
    bool isPostEffect = true;
    float volumeThreshold = 0.02;
    EffectType effectType_;
    ofMatrix4x4 matrix_;
    
public:
    
    CaptureDrawer(const ofFbo &capturedFbo)
    {
        matrix_ = $Context(AR)->processor->getLastAnchorMatrix();
        addCapturedFbo(capturedFbo);
#ifdef TARGET_OPENGLES
        setEffect(Normal);
//        shader.load("shaders/normal");
#else
        ofLogError("Set target to OpenGLES!");
#endif
    }
    
    void update()
    {
        
    }
    
    void draw()
    {
        ofPushMatrix();
        ofMultMatrix(matrix_);
        ofRotate(90,0,0,1); //z軸に90度回転
        //=== draw begin ===
        if(isPostEffect)
        {
            //TODO: volumeじゃなくて、oscもらう
            if($Context(Property)->volume > volumeThreshold)
            {
                setRandomEffect();
            }
        }
//        else
//        {
//            shader.load("shaders/normal");
//        }
        
        shader.begin();
        {
            //TODO: stepじゃなくてOSC&押しっぱなしとかにする。effect trueにしといて音に反応してエフェクトかかるみたいな？
            shader.setUniform1f("rand", ofRandom(1));
            shader.setUniform2f("resolution", Config::Window::WIDTH, Config::Window::HEIGHT);
            shader.setUniformTexture("texture", capturedFbo_.getTexture(), 0);
            
            capturedFbo_.draw(ofPoint(-$Context(Property)->aspect/8, -0.125), $Context(Property)->aspect/4, 0.25);
        }
        shader.end();
        //=== draw end ===
        ofPopMatrix();
        
    }
    
    void addCapturedFbo(const ofFbo &capturedFbo)
    {
        ofFbo fbo;
        fbo.allocate(Config::Window::WIDTH, Config::Window::HEIGHT, GL_RGBA);
        fbo.begin();
        {
            ofSetColor(255, 255);
            //w: 640 /h: 1136
            capturedFbo.draw(0, 0, Config::Window::WIDTH, Config::Window::HEIGHT);
        }
        fbo.end();
        
        capturedFbo_ = fbo;
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
