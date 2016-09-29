//
//  Sprite.cpp
//  example-Joint
//
//  Created by Projeção on 29/09/16.
//
//

#include "Sprite.h"

Sprite::Sprite(){
    
}

void Sprite::Setup(b2World * b2dworld, float x, float y, float radius){
    
    if(b2dworld == NULL) {
        ofLog(OF_LOG_NOTICE, "ofxBox2dCircle :: setup : - must have a valid world -");
        return;
    }
    
    // these are used to create the shape
    b2CircleShape shape;
    
    shape.m_p.SetZero();
    shape.m_radius		= radius / OFX_BOX2D_SCALE;
    this->radius		= radius;
    
    fixture.shape		= &shape;
    fixture.density		= density;
    fixture.friction	= friction;
    fixture.restitution	= bounce;
    
    if(density == 0.f)	bodyDef.type	= b2_staticBody;
    else				bodyDef.type	= b2_dynamicBody;
    
    bodyDef.position.Set(x/OFX_BOX2D_SCALE, y/OFX_BOX2D_SCALE);
    
    body = b2dworld->CreateBody(&bodyDef);
    body->CreateFixture(&fixture);
    
    alive = true;
}
void Sprite::Setup(b2World *b2dworld, float x, float y, float radius, std::string image){
//    if(image){
//        ofLog(OF_LOG_NOTICE, "No image to load. Breaking!");
//        return;
//    }
    this->setImage(image);
    this->Setup(b2dworld, x, y, radius);
}

void Sprite::setImage(std::string imageFile){
    this->image = new ofImage();
    this->image->load(ofFile(std::filesystem::path(imageFile.c_str())));
    this->image->resize(50, 50);
}

void Sprite::getRadius(){
    return this->radius;
}

void Sprite::setRadius(float r){
    this->radius = r;
}

void Sprite::Draw(){
    
    if(!isBody()) return;
    
    
    ofPushMatrix();
    ofTranslate(body->GetPosition().x, body->GetPosition().y, 0);
    ofRotate(getRotation(), 0, 0, 1);
    
    
    
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(0);
    ofDrawLine(0, 0, radius, 0);
    if(isSleeping()) {
        ofSetColor(255, 100);
        
    }
    ofPopStyle();
    
    ofPopMatrix();
    //desenha o sprite
    this->image->draw(this->getPosition().x - this->image->getWidth() / 2, this->getPosition().y - this->image->getHeight() / 2);

}

ofImage* Sprite::getImage(){
    return this->image;
}
