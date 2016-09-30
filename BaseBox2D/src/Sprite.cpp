//
//  Sprite.cpp
//  example-Joint
//
//  Created by Projeção on 29/09/16.
//
//

#include "Sprite.h"
#include <math.h>

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
    if(this->image){
        ofLog(OF_LOG_NOTICE, "No image to load. Breaking!");
        return;
    }
    this->setImage(image);
    this->Setup(b2dworld, x, y, radius);
}

void Sprite::setImage(std::string imageFile){
    this->image = new ofImage();
    this->image->load(ofFile(std::filesystem::path(imageFile.c_str())));
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
    
//    ofTranslate(body->GetPosition().x, body->GetPosition().y, 0);
//    ofTranslate(this->body->GetPosition().x, this->body->GetPosition().y);
//    ofRotateZ(body->GetAngle());
    

    ofEnableAlphaBlending();
    this->getVelocity().normalize();
    this->image->draw(this->getPosition().x - this->image->getWidth() / 2 - radius /2, this->getPosition().y - this->image->getHeight() / 2 - radius /2);
    
    if(isSleeping()) {
        ofSetColor(255, 100);
    }
    ofPopStyle();
    
    ofPopMatrix();
    //desenha o sprite
}

ofImage* Sprite::getImage(){
    return this->image;
}

void Sprite::setSize(float x, float y){
    if(this->image){
        this->image->resize(x,y);
    } else {
        ofLog(OF_LOG_WARNING, "Imagem nao instanciada!");
    }
}

inline ofMatrix4x4 Sprite::affineRotation(float radians){
        
    float sina = sin(radians);
    float cosa = cos(radians);
    
    return ofMatrix4x4(
                       cosa, -sina, 0, 1,
                       sina,  cosa, 0, 1,
                       0,     0,   1 , 1,
                       1,     1 ,  1 , 1);
}

