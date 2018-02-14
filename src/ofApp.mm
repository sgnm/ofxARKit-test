#include "ofApp.h"

//matrixの行列取得して、ログ吐き出してるだけっぽい
void logSIMD(const simd::float4x4 &matrix)
{
    std::stringstream output;
    int columnCount = sizeof(matrix.columns) / sizeof(matrix.columns[0]);
    for (int column = 0; column < columnCount; column++) {
        int rowCount = sizeof(matrix.columns[column]) / sizeof(matrix.columns[column][0]);
        for (int row = 0; row < rowCount; row++) {
            output << std::setfill(' ') << std::setw(9) << matrix.columns[column][row];
            output << ' ';
        }
        output << std::endl;
    }
    output << std::endl;
}

//--------------------------------------------------------------
ofApp :: ofApp (ARSession * session){
    //呼ばれない
    this->session = session;
    cout << "creating ofApp(ARSession * session)" << endl;
}

ofApp::ofApp(){
    //SFormatに設定を書き込んで、新しくsessionを始めるみたいな
    ARCore::SFormat format;
    format.enableLighting();
    this->session = ARCore::generateNewSession(format);
    cout << "creating ofApp()" << endl;
}

//--------------------------------------------------------------
ofApp :: ~ofApp () {
    cout << "destroying ofApp" << endl;
}

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(127);
    
    img.load("OpenFrameworks.png");
    
    int fontSize = 8;
    if (ofxiOSGetOFWindow()->isRetinaSupportedOnDevice())
        fontSize *= 2;
    
    font.load("fonts/mono0755.ttf", fontSize);
    
    processor = ARProcessor::create(this->session);
    processor->setup();
}



//--------------------------------------------------------------
void ofApp::update(){
    
    processor->update();
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableAlphaBlending();
    
    ofDisableDepthTest();
    processor->draw();
    ofEnableDepthTest();
    
    processor->anchorController->loopAnchors([=](ARObject obj, int index)->void {
        
        camera.begin();
        processor->setARCameraMatrices();
        
        ofPushMatrix();
        ofMultMatrix(obj.modelMatrix);
        
        ofSetColor(255);
        ofRotate(90,0,0,1);
        
        aspect = ARCommon::getNativeAspectRatio();
        fbos[index].draw(ofPoint(-aspect/8, -0.125), aspect/4, 0.25);
        
        ofPopMatrix();
        
        camera.end();
        
    });
    
    ofDisableDepthTest();
    // ========== DEBUG STUFF ============= //
//    processor->debugInfo.drawDebugInformation(font);
    
    
}

//--------------------------------------------------------------
void ofApp::exit() {
    //
}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs &touch){
    cout << "num: " << processor->getNumAnchors() << endl;
    if(processor->getNumAnchors() > MAX_NUM_ANCHORS)
    {
        //TODO: 削除はできたけど90超えるとなぜかアプリ落ちるっぽい？、、
        //一定数超えたらアンカー削除
        processor->removeAnchor(0);
    }
    
//    processor->addAnchor(ofVec3f(touch.x,touch.y,-0.2)); //xy座標指定してアンカー追加, draw側も合わせる必要がある. WIPっぽいので使わない.
    processor->addAnchor(-0.2);
    
    // fboがローカル変数じゃないとうまくいかない。おそらくメンバー変数だと参照を保持しているので全部変わってしまうみたいな
    ofFbo fbo;
    fbo.allocate(WIDTH, HEIGHT, GL_RGBA);
    fbo.begin();
    {
        //w: 640 /h: 1136
        processor->getFBO().draw(0, 0, WIDTH, HEIGHT);
    }
    fbo.end();
    
    ofFbo tempFbo = processor->getFBO();
    
    fbos.emplace_back(fbo);
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs &touch){
    
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs &touch){
    
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs &touch){
    
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
    processor->updateDeviceInterfaceOrientation();
    processor->deviceOrientationChanged();
    
}


//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs& args){
    
}


