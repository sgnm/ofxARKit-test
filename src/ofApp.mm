#include "ofApp.h"

#pragma mark - setup
//--------------------------------------------------------------
void ofApp::setup() {
    //basic settings
    ofSetCircleResolution(60);
    ofEnableSmoothing();
    ofBackground(0);
    
    //init context
    ofxGlobalContext::Manager::defaultManager().createContext<Property>();
    ofxGlobalContext::Manager::defaultManager().createContext<AR>();
    ofxGlobalContext::Manager::defaultManager().createContext<OSC>();
    ofxGlobalContext::Manager::defaultManager().createContext<Timer>();
    $Context(Property)->aspect = ARCommon::getNativeAspectRatio();
    cout << "aspect: " << $Context(Property)->aspect << endl;
    
    //setup gui
    setupGui();
    
    //blur setting
    ofFbo::Settings s;
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat = GL_RGBA;
    s.textureTarget = GL_TEXTURE_2D;
    s.maxFilter = GL_LINEAR; GL_NEAREST;
    s.numSamples = 0;
    s.numColorbuffers = 1;
    s.useDepth = true;
    s.useStencil = false;
    gpuBlur.setup(s, false);
    
    gpuBlur.blurOffset = 0.027;
    gpuBlur.blurPasses = 5;
    gpuBlur.numBlurOverlays = 1;
    gpuBlur.blurOverlayGain = 255;
}

void ofApp::setupGui()
{
    //gui
    int fontSize = 8;
    if (ofxiOSGetOFWindow()->isRetinaSupportedOnDevice()) fontSize *= 2;
    font.load("fonts/mono0755.ttf", fontSize);
    captureButton.addListener(this, &ofApp::onPressedCaptureButton);
    animateButton.addListener(this, &ofApp::onPressedAnimateButton);
    clearAnchorsButton.addListener(this, &ofApp::onPressedClearAnchorsButton);
    clearInstancesButton.addListener(this, &ofApp::onPressedClearInstancesButton);
    isModeGeometric.addListener(this, &ofApp::onPressedModeGeometricToggle);
    isShowGui = true;
    ofxGuiSetFont("fonts/mono0755.ttf",14,true,true);
    ofxGuiSetTextPadding(4);
    ofxGuiSetDefaultWidth(Config::Window::WIDTH/4);
    ofxGuiSetDefaultHeight(54);
    gui.setup();
    gui.setPosition(Config::Window::WIDTH/4 * 3 - 20, 60);
    gui.add(captureButton.setup("capture"));
    gui.add(animateButton.setup("animate"));
    gui.add(clearAnchorsButton.setup("C anchors"));
    gui.add(clearInstancesButton.setup("C instances"));
    gui.add(isModeGeometric.setup("geo mode", true));
    gui.add(scale.setup("scale", 1.0, 0.5, 5.0));
}

#pragma mark - update
//--------------------------------------------------------------
void ofApp::update(){
    $Context(Property)->scale = scale;
    $Context(AR)->processor->update();
    ofxGlobalContext::Manager::defaultManager().update();
    
    manager.update();
    
//    cout << "add: " << $Context(OSC)->address << ", track: " << $Context(OSC)->track << ", note: " << $Context(OSC)->note << endl;
    
    if($Context(OSC)->address != "")
    {
        if($Context(OSC)->address == "/geo")
        {
            $Context(Property)->drawMode = GEOMETRIC;
            onPressedAnimateButton();
        }
        
        if($Context(OSC)->address == "/capture")
        {
            $Context(Property)->drawMode = CAMERA_CAPTURE;
            onPressedCaptureButton();
        }

        if($Context(OSC)->address == "/effect")
        {
            $Context(Property)->drawMode = CAMERA_CAPTURE;
            onPressedAnimateButton();
        }
        
        if($Context(OSC)->address == "/clear")
        {
            $Context(AR)->processor->removeAllAnchors();
            manager.clear();
        }
//        cout << "note: " << $Context(OSC)->note << endl;
        //TODO:
        //図形: track3つに分けて、それぞれに応じたアニメーションを開始する
        //FBO: track4とかに埋め込んで、それでキャプチャーする（
        
        $Context(OSC)->address = "";
    }
}

#pragma mark - draw
//--------------------------------------------------------------
void ofApp::draw() {
    //=====================================
    //カメラ画像を描画
    ofSetColor(255);
    $Context(AR)->processor->draw();
    //=====================================
    
    //=====================================
    //managerをfboに描画
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    gpuBlur.beginDrawScene();
    {
        ofClear(0, 0, 0, 0);
        ofSetColor(255);
        manager.draw(); //2Dで書く
    }
    gpuBlur.endDrawScene();
    //=====================================
    
    //=====================================
    //camera有効化、matrixかけてあげて、その中でfboを描画
    $Context(AR)->camera.begin();
    $Context(AR)->processor->setARCameraMatrices();
    
    if($Context(AR)->processor->getNumAnchors() > 0)
    {
        gpuBlur.performBlur();
        
        ofPushMatrix();
        ofMultMatrix($Context(AR)->processor->getLastAnchorMatrix());
        ofRotate(90,0,0,1); //z軸に90度回転
        
        ofTranslate(0, 0, -depth - $Context(Timer)->elapsed * speed);
        {
            //overlay the blur on top
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //pre-multiplied alpha
            gpuBlur.drawBlurFbo(ofPoint(-$Context(Property)->aspect * scale, -scale), $Context(Property)->aspect * 2 * scale, 2 * scale);
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            
            //draw the "clean" scene
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            gpuBlur.drawSceneFBO(ofPoint(-$Context(Property)->aspect * scale, -scale), $Context(Property)->aspect * 2 * scale, 2 * scale);
        }
        ofPopMatrix();
        ofDisableBlendMode();
    }
    $Context(AR)->camera.end();
    //=====================================
    
    // draw debug information
    drawDebugInfo();
}

void ofApp::drawGeometricGraphics()
{
    if($Context(AR)->processor->getNumAnchors() > 0)
    {
        //ジオメトリーックアニメーションを描画
        //===============================
        //元
        ofPushMatrix();
        ofMultMatrix($Context(AR)->processor->getLastAnchorMatrix());
        ofRotate(90,0,0,1); //z軸に90度回転
        
        ofTranslate(0, 0, -depth - $Context(Timer)->elapsed * speed);
        {
            ofSetColor(255, 255);
            //==========================
            //fboを、matrix内のサイズでdrawする（capture drawerと一緒）
            gpuBlur.performBlur();
            
            //overlay the blur on top
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //pre-multiplied alpha
            gpuBlur.drawBlurFbo(ofPoint(-$Context(Property)->aspect/8, -0.125), $Context(Property)->aspect/4, 0.25);
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            
            //draw the "clean" scene
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            gpuBlur.drawSceneFBO(ofPoint(-$Context(Property)->aspect/8, -0.125), $Context(Property)->aspect/4, 0.25);
            ofDisableBlendMode();
            //==========================
        }
        ofPopMatrix();
        //===============================
        
        //===============================
        //鏡、コピー
        ofPushMatrix();
        ofMatrix4x4 mat = $Context(AR)->processor->getLastAnchorMatrix();
        
        //移動行列、最初に検知した軸を元にy座標を反転
        ofVec3f tl = mat.getTranslation();
        tl.y *= -1.0;
        mat.setTranslation(tl);
        
        //回転行列
        // TODO: コピーのやつに、rotation（向きとか）を後で反映させる
        ofQuaternion qt = mat.getRotate();
//        qt.makeRotate(180, 0, 0, 1);
        qt.inverse();
        mat.setRotate(qt);
        
        ofMultMatrix(mat);
        ofRotate(90,0,0,1); //z軸に90度回転
        
        ofTranslate(0, 0, -depth - $Context(Timer)->elapsed * speed);
        {
            ofSetColor(255, 150);
            manager.draw();
        }
        
        ofPopMatrix();
        //===============================
    }
    else
    {
        ofLogWarning("anchors num is less than 0!");
    }
}

void ofApp::drawCaptures()
{
    if($Context(AR)->processor->getNumAnchors() > 0)
    {
        ofSetColor(255, 255);
        manager.draw();
    }
    else
    {
        ofLogWarning("anchors num is less than 0!");
    }
}

void ofApp::drawOscInfo()
{
    static int x = 20;
    static int y = 40;
    font.drawString("address: " + $Context(OSC)->address, x, y + 125);
    font.drawString("track: " + ofToString($Context(OSC)->track), x, y + 150);
    font.drawString("note: " + ofToString($Context(OSC)->note), x, y + 175);
    font.drawString("time: " + ofToString($Context(Timer)->elapsed), x, y + 200);
    font.drawString("anchors num: " + ofToString($Context(AR)->processor->getNumAnchors()), x, y + 225);
    font.drawString("planes num: " + ofToString($Context(AR)->processor->getNumPlanes()), x, y + 250);
    static string drawModeString = "";
    switch($Context(Property)->drawMode)
    {
        case GEOMETRIC:
            drawModeString = "Geometric";
            break;
        case CAMERA_CAPTURE:
            drawModeString = "Camera capture";
            break;
    }
    font.drawString("draw mode: " + ofToString(drawModeString), x, y + 275);
}

void ofApp::drawDebugInfo()
{
    if(isShowGui)
    {
        $Context(AR)->camera.begin();
        $Context(AR)->processor->setARCameraMatrices();
        ofDrawAxis(10);
        ofSetColor(ofGetFrameNum() % 255);
        if($Context(AR)->processor->getNumAnchors() > 0)
        {
            ofPushMatrix();
            ofMultMatrix($Context(AR)->processor->getLastAnchorMatrix());
            ofDrawAxis(10);
            ofRotate(90,0,0,1);
            ofDrawBox(0, 0, 0, 0.01, 0.01, 2.0);
            ofPopMatrix();
        }
        $Context(AR)->camera.end();
        $Context(AR)->processor->debugInfo.drawDebugInformation(font);
        drawOscInfo();
        gui.draw();
    }
}

#pragma mark - events
//--------------------------------------------------------------
void ofApp::exit() {
    captureButton.removeListener(this,&ofApp::onPressedCaptureButton);
}

//--------------------------------------------------------------
void ofApp::onPressedCaptureButton()
{
    if($Context(AR)->processor->getNumAnchors() > Config::AR::MAX_NUM_ANCHORS)
    {
        //TODO: 削除はできたけど90超えるとなぜかアプリ落ちるっぽい？、、
        //一定数超えたらアンカー削除
        $Context(AR)->processor->removeAnchor(0);
    }

    $Context(AR)->processor->addAnchor(-0.2);
    if($Context(Property)->drawMode == CAMERA_CAPTURE)
    {
        manager.createInstance<CaptureDrawer>($Context(AR)->processor->getFBO())->playInfinity();
    }
}

//--------------------------------------------------------------
void ofApp::onPressedAnimateButton()
{
    if($Context(Property)->drawMode == GEOMETRIC)
    {
        //z軸をランダムに設定
        //TODO: ランダムにしてもなんか微妙なので一旦0で、、
        depth = ofRandom(0.0, 1.0);
        speed = ofRandom(0.5, 1.5);
//        depth = 0.0;
        
        //エフェクトをランダムに設定
        FillMode fillMode = static_cast<FillMode>(rand() % DUMMY_TO_COUNT);
        int randIndex = ofRandom(13);
//        int randIndex = 12;
        switch (randIndex) {
            case 0:
                manager.createInstance<Circle::Anim1>(fillMode)->play(0.5);
                break;
            case 1:
                manager.createInstance<Circle::Bigger>(fillMode)->play(0.5);
                break;
            case 2:
                manager.createInstance<Circle::Smaller>(fillMode)->play(0.5);
                break;
            case 3:
                manager.createInstance<Tri::Bigger>(fillMode)->play(0.5);
                break;
            case 4:
                manager.createInstance<Tri::Line>()->play(0.5);
                break;
            case 5:
                manager.createInstance<Tri::Rotate>(fillMode)->play(0.5);
                break;
            case 6:
                manager.createInstance<Tri::CutOut>()->play(0.5);
                break;
            case 7:
                manager.createInstance<Tri::CutOutRotate>()->play(0.5);
                break;
            case 8:
                manager.createInstance<Rectangle::Bigger>(fillMode)->play(0.5);
                break;
            case 9:
                manager.createInstance<Rectangle::Line>()->play(0.5);
                break;
            case 10:
                manager.createInstance<Rectangle::Rotate>(fillMode)->play(0.5);
                break;
            case 11:
                manager.createInstance<Rectangle::CutOut>()->play(0.5);
                break;
            case 12:
                manager.createInstance<Rectangle::CutOutRotate>()->play(0.5);
                break;
                
            default:
                break;
        }
    }
    else if($Context(Property)->drawMode == CAMERA_CAPTURE)
    {
        for(const auto &drawer : manager.getInstance<CaptureDrawer>())
        {
            //TODO: ランダムにする必要ないかも。エフェクト揃ってる方が綺麗な気がする。
            drawer->setRandomEffect();
        }
    }
    
    $Context(Timer)->elapsed = 0.0;
}

//--------------------------------------------------------------
void ofApp::onPressedClearAnchorsButton()
{
    $Context(AR)->processor->removeAllAnchors();
}

//--------------------------------------------------------------
void ofApp::onPressedClearInstancesButton()
{
    manager.clear();
}

//--------------------------------------------------------------
void ofApp::onPressedModeGeometricToggle(bool &isToggleOn)
{
    if(isToggleOn)
    {
        $Context(Property)->drawMode = GEOMETRIC;
    }
    else
    {
        $Context(Property)->drawMode = CAMERA_CAPTURE;
    }
}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs &touch){
    
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs &touch){
    
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs &touch){
    
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs &touch){
    isShowGui = !isShowGui;
}

//--------------------------------------------------------------
void ofApp::lostFocus(){
    
}

//--------------------------------------------------------------
void ofApp::gotFocus(){
    
}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){
    $Context(AR)->processor->updateDeviceInterfaceOrientation();
    $Context(AR)->processor->deviceOrientationChanged();    
}


//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs& args){
    
}


