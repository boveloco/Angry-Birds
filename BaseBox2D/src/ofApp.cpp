#include "ofApp.h"
string path  = "img/red.png";
int sizex = 30;
int sizey = 100;
int posx = 695;
int posy = 414;
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
    
    s.setPhysics(3.0, 0.58, 0.1);
    s.Setup(box2d.getWorld(), 117, ofGetHeight() - ofGetHeight() / 3 + 10 , 15);
    s.setImage(path);
    s.setSize(50, 50);
    
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
    
    //castelo
    this->createWall(posx, posy , sizex, sizey);
    this->createWall(posx + sizey, posy , sizex, sizey);
    
    this->createWall(posx, posy - sizex , sizey, sizex);
    this->createWall(posx + sizey, posy - sizex , sizey, sizex);
    //primeiro castelo pronto
    posx += 202;
    
    this->createWall(posx, posy , sizex, sizey);
    this->createWall(posx + sizey, posy , sizex, sizey);
    
    this->createWall(posx, posy - sizex , sizey, sizex);
    this->createWall(posx + sizey, posy - sizex , sizey, sizex);
    //segundo castelo pronto
    posy -= (sizey + sizex);
    posx -= 50;
    
    this->createWall(posx, posy , sizex, sizey);
    this->createWall(posx + sizey, posy , sizex, sizey);
    
    this->createWall(posx, posy - sizex , sizey, sizex);
    this->createWall(posx + sizey, posy - sizex , sizey, sizex);
    
    this->createWall(posx - sizey , posy , sizex, sizey);
    this->createWall(posx - sizey, posy - sizex , sizey, sizex);
    //terceiro castelo pronto
    posy -= (sizey + sizex);
    posx -= 50;
    this->createWall(posx, posy , sizex, sizey);
    this->createWall(posx + sizey, posy , sizex, sizey);
    
    this->createWall(posx, posy - sizex , sizey, sizex);
    this->createWall(posx + sizey, posy - sizex , sizey, sizex);
    
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
    //grouds and walls
    ground.draw();
    ground2.draw();
    wall1.draw();
    wall2.draw();
    
    ofSetHexColor(0x0);
    anchor.draw();
    anchor2.draw();
    ofFill();
    
    ofSetHexColor(0xffffff);
    s.Draw();
    
    for (int i = 0; i < walls.size(); i++){
        ofSetHexColor(0x0000ff);
        walls[i].get()->draw();
//        std::cout<< walls[i].get()->getPosition() << std::endl;
    }
    
    for (int i = 0; i < projectiles.size(); i++){
        ofSetHexColor(0xffffff);
        projectiles[i].get()->Draw();
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
    
    shared_ptr<Sprite> projectile = shared_ptr<Sprite>(new Sprite);
    projectile.get()->setPhysics(3.0, 0.58, 1);
    b2Vec2 vel = s.body->GetLinearVelocity();
    projectile.get()->setImage(path);
    projectile.get()->setSize(50, 50);
    projectile.get()->setFixedRotation(true);
    projectile.get()->Setup(box2d.getWorld(), s.getPosition().x + 10, s.getPosition().y - size * 0.5 , size);
    projectile.get()->body->ApplyForceToCenter(b2Vec2(multiply * vel.x, multiply * vel.y), true);
    projectiles.push_back(projectile);
    
    char* n = new char();
    sprintf(n, "%f", projectile.get()->getRotation());
    ofLog(OF_LOG_NOTICE, n);
}
void ofApp::createWall(float x, float y, float w, float h){
    
    shared_ptr<ofxBox2dRect> wall = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
    wall.get()->setPhysics(3.0, 0.58, 1.5);
    wall.get()->setFixedRotation(false);
    wall.get()->setup(box2d.getWorld(), x, y, w, h);
    this->walls.push_back(wall);
}
