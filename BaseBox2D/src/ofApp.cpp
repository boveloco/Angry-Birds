#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofDisableAntiAliasing();
    
    box2d.init();
    box2d.setGravity(0, 15);
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    box2d.createBounds();
    
    anchor.fixture.filter.maskBits = 0x0000;
    anchor2.fixture.filter.maskBits = 0x0000;
    anchor.setup(box2d.getWorld(), 100, ofGetHeight() - ofGetHeight() / 3 - 25, 4);
    anchor2.setup(box2d.getWorld(), 135, ofGetHeight() - ofGetHeight() / 3 + 35, 4);
    
    
    
    //projetil
    shared_ptr<ofxBox2dCircle> projectile = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
    projectile.get()->setPhysics(30.0, 0.58, 0.3);
    projectiles.push_back(projectile);
    
    //sprite red
    //red.load("/Users/projecao/workspace/of_v0.9.3_osx_release/addons/ofxBox2d/example-Joint/img/red.png");
    //red.resize(size * 5, size * 5);
    
    //circle.fixture.filter.maskBits= 0x0000;
    //circle.setPhysics(3.0, 0.58, 0.1);
    //circle.setup(box2d.getWorld(), 117,  ofGetHeight() - ofGetHeight() / 3 + 10 , 8);
    
    s.setPhysics(3.0, 0.58, 0.1);
    s.Setup(box2d.getWorld(), 117, ofGetHeight() - ofGetHeight() / 3 + 10 , 15);
    s.setImage("/Users/projecao/workspace/of_v0.9.3_osx_release/addons/ofxBox2d/example-Joint/img/red.png");
    s.getImage()->resize(50,50);
    
    
    //joints
    shared_ptr<ofxBox2dJoint> joint = shared_ptr<ofxBox2dJoint>(new ofxBox2dJoint);
    joint.get()->setup(box2d.getWorld(), anchor.body, s.body);
    joints.push_back(joint);

    joint = shared_ptr<ofxBox2dJoint>(new ofxBox2dJoint);
    joint.get()->setup(box2d.getWorld(), s.body, anchor2.body);
    joints.push_back(joint);
    
    //ground
    ground.setup(box2d.getWorld(),ofRectangle(ofPoint(ofGetWidth() * 0.5, ofGetHeight()), ofGetWidth(), 100));
    ground2.setup(box2d.getWorld(), ofRectangle(ofPoint(ofGetWidth() / 3 * 2, ofGetHeight() / 3 * 2), 500, 30));
    wall1.setup(box2d.getWorld(), ofRectangle(ofPoint(ofGetWidth(), ofGetHeight() * 0.5), 30, ofGetHeight() ));
    wall2.setup(box2d.getWorld(), ofRectangle(ofPoint(0, ofGetHeight() * 0.5), 30, ofGetHeight() ));
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    box2d.update();
    
    
    if (release) {
        if (s.getPosition().x >= 110) {
            addProjectile();
            release = false;
        }
    }
    else if (s.getPosition().x <= 100) {
        release = true;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    s.Draw();
    //red.draw(circle.getPosition().x - red.getWidth()* 0.5 , circle.getPosition().y - red.getHeight() * 0.5);
    
    //grouds and walls
    ground.draw();
    ground2.draw();
    wall1.draw();
    wall2.draw();
    
    ofSetHexColor(0x0);
    anchor.draw();
    anchor2.draw();
    
    ofFill();
    ofSetHexColor(0x0);
    circle.draw();
    
    for (int i = 0; i < projectiles.size(); i++){
        ofSetHexColor(0x0);
        projectiles[i].get()->draw();
    }
    
    for (int i = 0; i < joints.size(); i++) {
        ofSetHexColor(0x444342);
        joints[i].get()->draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'n'){
        addProjectile();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

void ofApp::addProjectile(){
    float multiply = 200;
    
    shared_ptr<ofxBox2dCircle> projectile = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
    projectile.get()->setPhysics(3.0, 0.58, 1);
    b2Vec2 vel = s.body->GetLinearVelocity();
    projectile.get()->setup(box2d.getWorld(), s.getPosition().x + 10, s.getPosition().y - size * 0.5 , size);
    projectile.get()->body->ApplyForceToCenter(b2Vec2(multiply * vel.x, multiply * vel.y), true);
    //projectile.get()->body->SetLinearVelocity(vel);
    projectiles.push_back(projectile);
    
    s.body->SetLinearVelocity(b2Vec2(0,0));
}
