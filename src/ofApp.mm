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
}

void ofApp::setupGui()
{
    //gui
    int fontSize = 8;
    if (ofxiOSGetOFWindow()->isRetinaSupportedOnDevice()) fontSize *= 2;
    font.load("fonts/mono0755.ttf", fontSize);
    captureButton.addListener(this, &ofApp::onPressedCaptureButton);
    animateButton.addListener(this, &ofApp::onPressedAnimateButton);
    isModeGeometric.addListener(this, &ofApp::onPressedModeGeometricToggle);
    isShowGui = true;
    ofxGuiSetFont("fonts/mono0755.ttf",14,true,true);
    ofxGuiSetTextPadding(4);
    ofxGuiSetDefaultWidth(Config::Window::WIDTH/4);
    ofxGuiSetDefaultHeight(54);
    gui.setup();
    gui.setPosition(Config::Window::WIDTH/4 * 3 - 20, 20);
    gui.add(captureButton.setup("capture"));
    gui.add(animateButton.setup("animate"));
    gui.add(isModeGeometric.setup("geo mode", false));
}

#pragma mark - update
//--------------------------------------------------------------
void ofApp::update(){
    $Context(AR)->processor->update();
    ofxGlobalContext::Manager::defaultManager().update();
    manager.update();
    
    cout << "add: " << $Context(OSC)->address << ", track: " << $Context(OSC)->track << ", note: " << $Context(OSC)->note << endl;
    
    if($Context(OSC)->address == "/bang")
    {
        //TODO:
        //図形: track3つに分けて、それぞれに応じたアニメーションを開始する
        //FBO: track4とかに埋め込んで、それでキャプチャーする（
        
        FillMode fillMode = static_cast<FillMode>(rand() % DUMMY_TO_COUNT);
//        manager.createInstance<Circle::Bigger>(fillMode)->play(0.2);
        manager.createInstance<Circle::Anim1>()->play(0.5);
        
        //Z軸リセット
        //TODO: Z軸ランダムに変えたりできるといい。translateのスピードも
        $Context(Timer)->elapsed = 0.0;
        
        //base
        if($Context(OSC)->track == 1)
        {
            
        }
        
        //drum
        if($Context(OSC)->track == 2)
        {
            
        }
        
        //guitar
        if($Context(OSC)->track == 3)
        {
            
        }
        
        //capture fbo
        if($Context(OSC)->track == 4)
        {
            //TODO: 受け取るnoteに応じて、何分割するかとか決める
            if($Context(OSC)->note == 49)
            {
                
            }
            
            if($Context(OSC)->note == 42)
            {
                //TODO: fboキャプチャの場合は、OSCもらってキャプチャするので引数にmatrix渡す！
                //create instanceする
                manager.createInstance<CaptureDrawer>($Context(AR)->processor->getFBO())->playInfinity();
                //            captureDrawer.addCapturedFbo($Context(AR)->processor->getFBO());
            }
        }
        
        
        $Context(OSC)->address = "";
    }
}

#pragma mark - draw
//--------------------------------------------------------------
void ofApp::draw() {
    $Context(AR)->processor->draw();
    ofEnableDepthTest();
    
    $Context(AR)->camera.begin();
    $Context(AR)->processor->setARCameraMatrices();
    // === begin to draw stuff ===
    switch($Context(Property)->drawMode)
    {
        case GEOMETRIC:
            drawGeometricGraphics();
            break;
        case CAMERA_CAPTURE:
            drawCaptures();
            break;
    }
    // === end to draw stuff ===
    $Context(AR)->camera.end();
    
    ofDisableDepthTest();
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
        
        ofTranslate(0, 0, $Context(Timer)->elapsed * Config::Graphics::SPEED);
        {
            ofSetColor(255, 255);
            manager.draw();
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
        
        ofTranslate(0, 0, $Context(Timer)->elapsed * Config::Graphics::SPEED);
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
        ofSetColor(ofGetFrameNum() % 255);
        if($Context(AR)->processor->getNumAnchors() > 0)
        {
            $Context(AR)->camera.begin();
            $Context(AR)->processor->setARCameraMatrices();
            ofDrawAxis(10);
            ofPushMatrix();
            ofMultMatrix($Context(AR)->processor->getLastAnchorMatrix());
            ofDrawAxis(10);
            ofRotate(90,0,0,1);
            ofDrawBox(0, 0, 0, 0.01, 0.01, 2.0);
            ofPopMatrix();
            $Context(AR)->camera.end();
        }
        $Context(AR)->processor->debugInfo.drawDebugInformation(font);
        drawOscInfo();
        gui.draw();
    }
}

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
        FillMode fillMode = static_cast<FillMode>(rand() % DUMMY_TO_COUNT);
        int randIndex = ofRandom(9);
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
                manager.createInstance<Rectangle::Bigger>(fillMode)->play(0.5);
                break;
            case 7:
                manager.createInstance<Rectangle::Line>()->play(0.5);
                break;
            case 8:
                manager.createInstance<Rectangle::Rotate>(fillMode)->play(0.5);
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


