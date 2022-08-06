//
//  Ball.hpp
//  snookerGame-mobile
//
//  Created by Manish Saini
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>

#include <stdio.h>
#include "cocos2d.h"
#include <Box2D/Box2D.h>

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;


enum BALL_COLOR{
    COLOR_RED    = 1,
    COLOR_YELLOW = 2,
    COLOR_GREEN  = 3,
    COLOR_BROWN  = 4,
    COLOR_BLUE   = 5,
    COLOR_PINK   = 6,
    COLOR_VIOLET = 7,
    COLOR_BLACK  = 8,
    COLOR_WHITE  = 9 // for cue ball
};
enum BALL_TYPE{
    TYPE_SOLID  = 1,
    TYPE_STRIPE = 2,
    TYPE_CUE    = 3,
    TYPE_BLACK  = 4
    
};

class Ball : public cocos2d::Sprite{
public:
     Ball();
    ~Ball();
    BALL_TYPE              type;
    BALL_COLOR             color;
    int ballNumber;
    
    b2CircleShape ballShape;
    b2Body *ballBody;
    b2BodyDef ballBodyDef;
   
    virtual bool init();
    CREATE_FUNC(Ball);
    
    void setBallType(BALL_TYPE type);
    void setBallColor(BALL_COLOR color);
    void setBallNumber(int number);
};

#endif /* Ball_hpp */
