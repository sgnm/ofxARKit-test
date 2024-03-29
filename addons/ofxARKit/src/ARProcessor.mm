//
//  CameraFrameConverter.cpp
//  ARToolkit
//
//  Created by Joseph Chow on 8/4/17.
//

#include "ARProcessor.h"
using namespace ARCommon;
using namespace ARCore;

#pragma mark - init
ARProcessor::ARProcessor(ARSession * session){
    this->session = session;
    
    debugInfo = ARDebugUtils::ARDebugInfo(session);
}

ARProcessor::~ARProcessor(){
    pauseSession();
    session = nullptr;
    
    // remove this instance of the ARCam - if there are other ARCams around, they will still be in memory
    camera.reset();
    anchorController.reset();
}

#pragma mark - debug API
void ARProcessor::toggleDebug(){
    debugMode = !debugMode;
}

void ARProcessor::pauseSession(){
      [session pause];
}

void ARProcessor::logTrackingState(){
    camera->logTrackingState();
}

void ARProcessor::restartSession(){
    // note - I don't know if this actually works once a session has been
    // stopped, may have to recreate session.
    [session runWithConfiguration:session.configuration];
}

#pragma mark - basic API
void ARProcessor::setup(bool debugMode){
    this->debugMode = debugMode;
    anchorController = ARAnchorManager::create(session);
    camera = ARCam::create(session);
    camera->setup(this->debugMode);
}

void ARProcessor::draw(){
    camera->draw();
}

void ARProcessor::update(){
    camera->update();
    if(debugMode){
        pointCloud.updatePointCloud(session.currentFrame);
    }
    
    anchorController->update();
    
}

void ARProcessor::updatePlanes(){
    anchorController->updatePlanes();
}


void ARProcessor::drawFrame(){
    draw();
}

#pragma mark - camera API
// =========== CAMERA API ============ //
void ARProcessor::forceInterfaceOrientation(UIInterfaceOrientation orientation){
    camera->setInterfaceOrientation(orientation);
}
void ARProcessor::setARCameraMatrices(){
    camera->setARCameraMatrices();
}

ofVec3f ARProcessor::getCameraPosition(){
    return ARCommon::getAnchorXYZ(camera->getTransformMatrix());
}

ofTexture ARProcessor::getCameraTexture(){
   return camera->getCameraTexture();
}

ARCommon::ARCameraMatrices ARProcessor::getCameraMatrices(){
     return camera->getCameraMatrices();
}

float ARProcessor::getLightIntensity(){
    return camera->getAmbientIntensity();
}

ARTrackingState ARProcessor::getTrackingState(){
    return camera->getTrackingState();
}

void ARProcessor::rotateCameraFrame(float angle){
    camera->updateRotationMatrix(angle);
}

void ARProcessor::updateDeviceInterfaceOrientation(){
    camera->updateInterfaceOrientation();
}

ARCameraMatrices ARProcessor::getMatricesForOrientation(UIInterfaceOrientation orientation,float near, float far){
    return camera->getMatricesForOrientation(orientation,near,far);
}


void ARProcessor::deviceOrientationChanged(){
    camera->updateDeviceOrientation();
}

#pragma mark - anchor API
// ======= ANCHOR API ========= //
void ARProcessor::addAnchor(float zZoom){
    anchorController->addAnchor(zZoom);
}

void ARProcessor::addAnchor(ofVec3f position){
    auto matrices = getCameraMatrices();
 
    ofMatrix4x4 model = toMat4(session.currentFrame.camera.transform);
    anchorController->addAnchor(position,matrices.cameraProjection,model * getCameraMatrices().cameraView);
}

void ARProcessor::removeAnchor(NSUUID * anchorId)
{
    anchorController->removeAnchor(anchorId);
}

void ARProcessor::removeAnchor(int index)
{
    anchorController->removeAnchor(index);
}

void ARProcessor::removeAllAnchors()
{
    anchorController->clearAnchors();
}

int ARProcessor::getNumAnchors()
{
    return anchorController->getNumAnchors();
}

ofMatrix4x4 ARProcessor::getAnchorMatrix(int index)
{
    return anchorController->getAnchorMatrix(index);
}

ofMatrix4x4 ARProcessor::getLastAnchorMatrix()
{
    return anchorController->getLastAnchorMatrix();
}

#pragma mark - plane API
int ARProcessor::getNumPlanes()
{
    return anchorController->getNumPlanes();
}

std::vector<PlaneAnchorObject> ARProcessor::getHorizontalPlanes()
{
    return anchorController->getPlaneAnchors();
}

PlaneAnchorObject ARProcessor::getLastHorizontalPlane()
{
    return anchorController->getLastPlane();
}

ofMatrix4x4 ARProcessor::getPlaneMatrix(int index)
{
    return anchorController->getPlaneMatrix(index);
}

ofMatrix4x4 ARProcessor::getLastPlaneMatrix()
{
    return anchorController->getLastPlaneMatrix();
}

void ARProcessor::drawHorizontalPlanes(){
    anchorController->drawPlanes(camera->getCameraMatrices());
}

#pragma mark - face API
// ======= FACE API ========= //
void ARProcessor::updateFaces(){
    anchorController->updateFaces();
}

#pragma mark - debug API
// ======== DEBUG API =========== //
void ARProcessor::drawPointCloud(){
    if(debugMode){
        pointCloud.draw(camera->getProjectionMatrix(), camera->getViewMatrix());
    } else {
        ofLog(OF_LOG_WARNING, "Debug Mode not set");
    }
}
