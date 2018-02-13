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
    this->session = session;
    cout << "creating ofApp" << endl;
}

ofApp::ofApp(){}

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
    
    processor = ARProcessor::create(session);
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
    
    if (session.currentFrame){
        if (session.currentFrame.camera){
            
            camera.begin();
            processor->setARCameraMatrices();
            
            mats.clear();
//            cout << session.currentFrame.anchors.count << endl;
            for (int i = 0; i < session.currentFrame.anchors.count; i++)
            {
                mats.emplace_back(session.currentFrame.anchors[i].transform);
            }
            
            for(int i = 0; i < mats.size(); i++)
            {
                // note - if you need to differentiate between different types of anchors, there is a
                // "isKindOfClass" method in objective-c that could be used. For example, if you wanted to
                // check for a Plane anchor, you could put this in an if statement.
                // if([anchor isKindOfClass:[ARPlaneAnchor class]]) { // do something if we find a plane anchor}
                // Not important for this example but something good to remember.
                
                ofPushMatrix();
                ofMatrix4x4 mat = ARCommon::convert<matrix_float4x4, ofMatrix4x4>(mats[i]);
                ofMultMatrix(mat);
                
                ofSetColor(255);
                ofRotate(90,0,0,1);
                
                //draw something
//                img.draw(-0.025 / 2, -0.025 / 2,0.025,0.025);
                aspect = ARCommon::getNativeAspectRatio();
                fbos[i].draw(ofPoint(-aspect/8, -0.125), aspect/4, 0.25);
                
                ofPopMatrix();
            }
            
            camera.end();
        }
        
    }
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
    if (session.currentFrame){
        //anchor数が80を超えたら最新をdelete
        //TODO: なぜかdeleteされないので調べる、、
        /*
        if(processor->getNumAnchors() >= 2)
        {
            processor->removeAnchor(0);
            fbos.erase(fbos.begin());
            mats.erase(mats.begin());
        }
        */
        
        ARFrame *currentFrame = [session currentFrame];
        
        matrix_float4x4 translation = matrix_identity_float4x4;
        translation.columns[3].z = -0.2;
        matrix_float4x4 transform = matrix_multiply(currentFrame.camera.transform, translation);
        
        // Add a new anchor to the session
        ARAnchor *anchor = [[ARAnchor alloc] initWithTransform:transform];
        
        [session addAnchor:anchor];
        
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


