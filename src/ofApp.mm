#include "ofApp.h"

//--------------------------------------------------------------
ofApp :: ofApp (ARSession * session){
    cout << "creating ofApp(ARSession * session)" << endl;
}

ofApp::ofApp(){
    cout << "creating ofApp()" << endl;
}

//--------------------------------------------------------------
ofApp :: ~ofApp () {
    cout << "destroying ofApp" << endl;
}

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetCircleResolution(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofBackground(0);
    
    //init context
    ofxGlobalContext::Manager::defaultManager().createContext<Property>();
    ofxGlobalContext::Manager::defaultManager().createContext<AR>();
    ofxGlobalContext::Manager::defaultManager().createContext<OSC>();
    ofxGlobalContext::Manager::defaultManager().createContext<Timer>();
    
    //GUI
    int fontSize = 8;
    if (ofxiOSGetOFWindow()->isRetinaSupportedOnDevice()) fontSize *= 2;
    font.load("fonts/mono0755.ttf", fontSize);
    captureButton.addListener(this, &ofApp::onPressedCaptureButton);
    animateButton.addListener(this, &ofApp::onPressedAnimateButton);
    isShowGui = true;
    ofxGuiSetFont("fonts/mono0755.ttf",14,true,true);
    ofxGuiSetTextPadding(4);
    ofxGuiSetDefaultWidth(Config::Window::WIDTH/4);
    ofxGuiSetDefaultHeight(54);
    gui.setup();
    gui.setPosition(Config::Window::WIDTH/4 * 3 - 20, 20);
    gui.add(captureButton.setup("capture"));
    gui.add(animateButton.setup("animate"));

    captureDrawer.setup();
    
    $Context(Property)->aspect = ARCommon::getNativeAspectRatio();
    cout << "aspect: " << $Context(Property)->aspect << endl;
}



//--------------------------------------------------------------
void ofApp::update(){
    $Context(AR)->processor->update();
    ofxGlobalContext::Manager::defaultManager().update();
    manager.update();
    
    cout << "add: " << $Context(OSC)->address << ", track: " << $Context(OSC)->track << ", note: " << $Context(OSC)->note << endl;
    
    if($Context(OSC)->address == "/bang")
    {
        FillMode fillMode = static_cast<FillMode>(rand() % DUMMY_TO_COUNT);
//        manager.createInstance<Circle::Bigger>(fillMode)->play(0.2);
        manager.createInstance<Circle::Anim1>()->play(0.5);
        
        if($Context(OSC)->track == 1)
        {
            //TODO: タイマー?初期化それに応じて、z座標変えてく
            //TODO: FBOもクリア?
            $Context(Timer)->elapsed = 0.0;
        }
        
        if($Context(OSC)->note == 42)
        {
            //TODO: fboキャプチャの場合は、OSCもらってキャプチャするので引数にmatrix渡す！
            captureDrawer.addCapturedFbo($Context(AR)->processor->getFBO());
        }
        
        $Context(OSC)->address = "";
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    $Context(AR)->processor->draw();
    ofEnableDepthTest();
    
    //instance継承したそれぞれのクラスで色々描画する。
    //そんでそのinstanceを出したり削除したりするためのクラスを作って、そこでMIDI note分岐してアニメーションさせるみたいな？
    //なので、createInstance時にアニメーションできるようにする！！
    if($Context(AR)->processor->getNumAnchors() > 0)
    {
        $Context(AR)->camera.begin();
        $Context(AR)->processor->setARCameraMatrices();

        ofPushMatrix();
        ofMultMatrix($Context(AR)->processor->getLastAnchorMatrix());
        ofRotate(90,0,0,1);
        
        ofTranslate(0, 0, $Context(Timer)->elapsed * Config::Graphics::SPEED);
        {
            manager.draw();
        }
        ofPopMatrix();
        
        $Context(AR)->camera.end();
    }
    
    ofDisableDepthTest();
    // ========== DEBUG STUFF ============= //
    if(isShowGui)
    {
        ofSetColor(ofGetFrameNum() % 255);
        if($Context(AR)->processor->getNumAnchors() > 0)
        {
            $Context(AR)->camera.begin();
            $Context(AR)->processor->setARCameraMatrices();
            ofPushMatrix();
            ofMultMatrix($Context(AR)->processor->getLastAnchorMatrix());
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

void ofApp::drawOscInfo()
{
    int x = 20; int y = 40;
    font.drawString("address: " + $Context(OSC)->address, x, y + 125);
    font.drawString("track: " + ofToString($Context(OSC)->track), x, y + 150);
    font.drawString("note: " + ofToString($Context(OSC)->note), x, y + 175);
    font.drawString("time: " + ofToString($Context(Timer)->elapsed), x, y + 200);
    font.drawString("anchors num: " + ofToString($Context(AR)->processor->getNumAnchors()), x, y + 225);
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
}

void ofApp::onPressedAnimateButton()
{
    FillMode fillMode = static_cast<FillMode>(rand() % DUMMY_TO_COUNT);
    int randIndex = ofRandom(3);
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
            
        default:
            break;
    }
    
    $Context(Timer)->elapsed = 0.0;
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


