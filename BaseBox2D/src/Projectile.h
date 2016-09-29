//
//  Projectile.h
//  example-Joint
//
//  Created by Projeção on 27/09/16.
//
//
#include "ofxBox2d.h"
#ifndef example_Joint_Projectile_h
#define example_Joint_Projectile_h


class Projectile : ofxBox2dCircle {
public:
    
private:
    b2BodyDef myBodyDef;
};

Projectile::Projectile(){
    myBodyDef.type = b2_dynamicBody;
}

#endif
