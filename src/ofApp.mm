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
    ofBackground(127);
    
    int fontSize = 8;
    if (ofxiOSGetOFWindow()->isRetinaSupportedOnDevice()) fontSize *= 2;
    
    font.load("fonts/mono0755.ttf", fontSize);
    
    //sound
    initialBufferSize = 512;
    sampleRate = 44100;
    drawCounter = 0;
    bufferCounter = 0;
    
    buffer = new float[initialBufferSize];
    memset(buffer, 0, initialBufferSize * sizeof(float));
    
    ofSoundStreamSetup(0, 1, this, sampleRate, initialBufferSize, 1);
    
    captureDrawer.setup();
    
    //init context
    ofxGlobalContext::Manager::defaultManager().createContext<Property>();
    ofxGlobalContext::Manager::defaultManager().createContext<AR>();
}



//--------------------------------------------------------------
void ofApp::update(){
    $Context(AR)->processor->update();
    ofxGlobalContext::Manager::defaultManager().update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableAlphaBlending();
    
    ofDisableDepthTest();
    $Context(AR)->processor->draw();
    ofEnableDepthTest();
    
    $Context(AR)->processor->anchorController->loopAnchors([=](ARObject obj, int index)->void {
        
        $Context(AR)->camera.begin();
        $Context(AR)->processor->setARCameraMatrices();
        
        ofPushMatrix();
        ofMultMatrix(obj.modelMatrix);
        
        ofSetColor(255);
        ofRotate(90,0,0,1);
        
        $Context(Property)->aspect = ARCommon::getNativeAspectRatio();
        
        captureDrawer.draw(index);
        
        ofPopMatrix();
        
        $Context(AR)->camera.end();
        
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
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    if(initialBufferSize < bufferSize){
        ofLog(OF_LOG_ERROR, "your buffer size was set to %i - but the stream needs a buffer size of %i", initialBufferSize, bufferSize);
    }
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    float numCounted = 0.0;
    
    int minBufferSize = MIN(initialBufferSize, bufferSize);
    for(int i=0; i<minBufferSize; i++) {
        buffer[i] = input[i] * 0.5;
        curVol += buffer[i] * buffer[i];
        numCounted++;
    }
    
    //this is how we get the mean of rms :)
    curVol /= numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    $Context(Property)->volume = smoothedVol;
    
    cout << "vol: " << smoothedVol << endl;
    
    bufferCounter++;
    
}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs &touch){
    cout << "num: " << $Context(AR)->processor->getNumAnchors() << endl;
    if($Context(AR)->processor->getNumAnchors() > Config::AR::MAX_NUM_ANCHORS)
    {
        //TODO: 削除はできたけど90超えるとなぜかアプリ落ちるっぽい？、、
        //一定数超えたらアンカー削除
        $Context(AR)->processor->removeAnchor(0);
    }
    
    $Context(AR)->processor->addAnchor(-0.2);
    
    captureDrawer.addCapturedFbo($Context(AR)->processor->getFBO());
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
    $Context(AR)->processor->updateDeviceInterfaceOrientation();
    $Context(AR)->processor->deviceOrientationChanged();
    
}


//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs& args){
    
}


