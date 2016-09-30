//
//  Sprite.h
//  example-Joint
//
//  Created by Projeção on 29/09/16.
//
//
//#pragma once

#ifndef __example_Joint__Sprite__
#define __example_Joint__Sprite__

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"
#include <String>
#include <iostream>
#include <fstream>


class Sprite : public ofxBox2dBaseShape {
public:
    Sprite();
    void Setup(b2World * b2dworld, float x, float y, float radius, std::string image);
    void Setup(b2World * b2dworld, float x, float y, float radius);
    void setImage(std::string imageFile);
    void setRadius(float r);
    void getRadius();
    void Draw();
    ofImage* getImage();
    void setSize(float x, float y);
    
private:
    ofImage* image;
    float radius = 15;
    /**
     * Cod Vinicius Godoy:
     *
     */
    ofMatrix4x4 affineRotation(float radians);
};


#endif /* defined(__example_Joint__Sprite__) */
