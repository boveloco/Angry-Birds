#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Sprite.h"

class ofApp : public ofBaseApp{
    
    ofImage red;
    
    Sprite  s;
    
    bool release = false;   // if mouse release
    float size = 12;         // projectile size
    ofxBox2d                                  box2d;   // the box2d world
    ofxBox2dCircle                            anchor;  // fixed
    ofxBox2dCircle                            anchor2;  // fixed anchor
    ofxBox2dRect                              ground; //chao
    ofxBox2dRect                              ground2; //chao
    ofxBox2dRect                              wall1; //chao
    ofxBox2dRect                              wall2; //chao
    vector      <shared_ptr<ofxBox2dPolygon> > targets; // circulos
    vector      <shared_ptr<Sprite> >         projectiles; // circulos
    vector      <shared_ptr<ofxBox2dRect> >   walls; // circulos
    vector      <shared_ptr<ofxBox2dJoint> >  joints;  // joints
    
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
    void addProjectile();
    
    void createWall(float x, float y, float w, float h);
    
    
    
};