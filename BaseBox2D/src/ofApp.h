#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxBox2d                                  box2d;   // the box2d world
    ofxBox2dCircle                            anchor;  // fixed
    ofxBox2dCircle                            anchor2;  // fixed anchor
    ofxBox2dCircle							  circle; // circulo
    ofxBox2dCircle							  projectile; // circulo
    vector      <shared_ptr<ofxBox2dJoint> >  joints;  // joints
    
    bool drag = false; // if the point was draged
};