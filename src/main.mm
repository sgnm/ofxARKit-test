#include "ofApp.h"
int main(){
    
    //  here are the most commonly used iOS window settings.
    //------------------------------------------------------
    ofiOSWindowSettings settings;
    //Retina解像度の有無
    settings.enableRetina = true; // enables retina resolution if the device supports it.
    //3D描画のためのデプスバッファの有無
    settings.enableDepth = true; // enables depth buffer for 3d drawing.
    //アンチエイリアスの有無
    settings.enableAntiAliasing = false; // enables anti-aliasing which smooths out graphics on the screen.
    //アンチエイリアスに使われるサンプルの数
    settings.numOfAntiAliasingSamples = 0; // number of samples used for anti-aliasing.
    //TODO: よくわからないので調べる。おそらく縦横判定?→なんか縦横でもtrue, falseでもあんま変わらないっぽい、、、
    settings.enableHardwareOrientation = false; // enables native view orientation.
    //TODO: よくわからないので調べる。おそらく縦横変更時のアニメーション
    settings.enableHardwareOrientationAnimation = false; // enables native orientation changes to be animated.
    //TODO: OpenGLESのバージョン指定。ここではES2らしい→ARKitってMetal使ってるんじゃないの？、、
    settings.glesVersion = OFXIOS_RENDERER_ES2; // type of renderer to use, ES1, ES2, etc.
    
    ofAppiOSWindow * window = (ofAppiOSWindow *)(ofCreateWindow(settings).get());
    
    bool bUseNative = true;
    if (bUseNative){
        /**
         *
         * ネイティブのiOSセットアップを使って起動する方法
         *
         * まずofAppiOSWindowが作られて、ofSetupOpenGL()に追加される
         * 注意:ofRunApp()には送られない - 実際にアプリが必要なときに発生する
         *
         * 最後に、AppDelegateが使うofAppiOSWindowを知らせてあげて終わらせる
         * これはカスタムされたAppDelegateで、ネイティブiOSアプリを起動するためのコードが中に書かれている
         * AppDelegateはofxiOSAppDelegateを継承しなければならない
         *
         **/
         
        /**
         *
         *  Below is how you start using a native ios setup.
         *
         *  First a ofAppiOSWindow is created and added to ofSetupOpenGL()
         *  Notice that no app is being sent to ofRunApp() - this happens later when we actually need the app.
         *
         *  One last thing that needs to be done is telling ofAppiOSWindow which AppDelegate to use.
         *  This is a custom AppDelegate and inside it you can start coding your native iOS application.
         *  The AppDelegate must extend ofxiOSAppDelegate.
         *
         **/
        
        window->startAppWithDelegate("MyAppDelegate");
    }
    else {
        //こっちが通常のofxiOSアプリの動かし方
        /**
         *
         *  This is the normal way of running an app using ofxiOS.
         *  This code has been left in this example to show that ofxiOS still works
         *
         **/
        
        return ofRunApp(new ofApp());
    }
    
}

