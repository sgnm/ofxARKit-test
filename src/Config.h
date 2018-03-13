//
//  Config.h
//  ofxARKit-test
//
//  Created by Shin on 2018/02/18.
//

#pragma once

namespace Config
{
    namespace Window
    {
        //w: 640 /h: 1136
        const float WIDTH = 640.0;
        const float HEIGHT = 1136.0;
    }
    
    namespace AR
    {
        const int MAX_NUM_ANCHORS = 90;
    }
    
    namespace OSC
    {
        const int PORT = 8000;
    }
    
    namespace Graphics
    {
        const float SCALE = 0.25;
        const int LINE_WIDTH = 10;
        const float SPEED = 1.0;
        
        enum FillMode
        {
            FILL,
            NO_FILL,
            DUMMY_TO_COUNT
        };
        
        enum DrawMode
        {
            GEOMETRIC,
            CAMERA_CAPTURE
        };
    }
}
