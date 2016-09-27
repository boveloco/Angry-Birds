#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofDisableAntiAliasing();

	box2d.init();
	box2d.setGravity(0, 1);
	box2d.setFPS(60.0);
	box2d.registerGrabbing();

	anchor.setup(box2d.getWorld(), 100, ofGetHeight() - ofGetHeight() / 3, 4);
	anchor2.setup(box2d.getWorld(), 100, ofGetHeight() - ofGetHeight() / 3 + 100, 4);

	//projetil
	projectile.setPhysics(300.0, 0.58, 0.1);

	circle.setPhysics(3.0, 0.58, 0.1);
	circle.setup(box2d.getWorld(), 100, ofGetHeight() - ofGetHeight() /3 + 50, 8);

	shared_ptr<ofxBox2dJoint> joint = shared_ptr<ofxBox2dJoint>(new ofxBox2dJoint);
	joint.get()->setup(box2d.getWorld(), anchor.body, circle.body);
	joints.push_back(joint);


	joint = shared_ptr<ofxBox2dJoint>(new ofxBox2dJoint);
	joint.get()->setup(box2d.getWorld(), circle.body, anchor2.body);
	joints.push_back(joint);


}

//--------------------------------------------------------------
void ofApp::update(){
	box2d.update();

	if (drag) {
		if (circle.getPosition().x >= 100) {
			projectile.setup(box2d.getWorld(), circle.body->GetPosition().x + 50, circle.body->GetPosition().y + 20, 30);
			drag = false;
		}
	}
	else if (circle.getPosition().x <= 80) {
		drag = !drag;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetHexColor(0x0);
	anchor.draw();
	anchor2.draw();
	
	ofFill();
	ofSetHexColor(0x0);
	circle.draw();
	projectile.draw();
	for (int i = 0; i < joints.size(); i++) {
		ofSetHexColor(0x444342);
		joints[i].get()->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
