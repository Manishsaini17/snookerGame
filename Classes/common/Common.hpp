//
//  Common.hpp
//  snookerGame-mobile
//
//  Created by Manish Saini 
//

#ifndef Commom_hpp
#define Commom_hpp

#include <stdio.h>

#define     DIRECTOR_VISIBLE_WIDTH              Director::getInstance()->getVisibleSize().width
#define     DIRECTOR_VISIBLE_HEIGHT             Director::getInstance()->getVisibleSize().height

 
// game property
#define SCALE_RATIO 32.0
#define SWIPE_FACTOR 50
#define DEACCELERATION_FACTOR 0.995

#define NUM_OF_BALLS  15

// ball property
#define BALL_DENSITY 10
#define BALL_FRICTION 0.5
#define BALL_RESTITUTION 0.5

// floor property
#define FLOOR_DENSITY 0
#define FLOOR_FRICTION 0.0
#define FLOOR_RESTITUTION 1.0

// cue ball property
#define CUE_BALL_DENSITY 10
#define CUE_BALL_FRICTION 0.8
#define CUE_BALL_RESTITUTION 0.6

class Commom{
public:
   const static int positionIterations = 10; // world position Iterations
   const static int velocityIterations = 10; // world velocity Iteration
};


#endif /* Commom_hpp */
