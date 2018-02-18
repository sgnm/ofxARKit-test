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
    
    //sound
    initialBufferSize = 512;
    sampleRate = 44100;
    drawCounter = 0;
    bufferCounter = 0;
    
    buffer = new float[initialBufferSize];
    memset(buffer, 0, initialBufferSize * sizeof(float));
    
    // 0 output channels,
    // 1 input channels
    // 44100 samples per second
    // 512 samples per buffer
    // 1 buffer
    ofSoundStreamSetup(0, 1, this, sampleRate, initialBufferSize, 1);
    
    
#ifdef TARGET_OPENGLES
    shader.load("shaders/normal");
#else
    ofLogError("Set target to OpenGLES!");
#endif
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
        
        //一定以上の音量だったら別loadする。
        if(isPostEffect)
        {
            if(smoothedVol > 0.02)
            {
                static int i = 0;
                while (shaderIndex == i)
                {
                    i = ofRandom(5);
                }
                switch(i)
                {
                    case 1:
                        shader.load("shaders/mono");
                        break;
                    case 2:
                        shader.load("shaders/invert");
                            break;
                    case 3:
                        shader.load("shaders/convergence");
                        break;
                    case 4:
                        shader.load("shaders/cut_slider");
                        break;
                    case 5:
                        shader.load("shaders/outline");
                        break;
                    case 0:
                        shader.load("shaders/normal");
                        break;
                }
                
                shaderIndex = i;
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
            shader.setUniform2f("resolution", WIDTH, HEIGHT);
            shader.setUniformTexture("texture", fbos[index].getTexture(), 0);
            
            fbos[index].draw(ofPoint(-aspect/8, -0.125), aspect/4, 0.25);
        }
        shader.end();
        
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
    
    cout << "vol: " << smoothedVol << endl;
    
    bufferCounter++;
    
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


