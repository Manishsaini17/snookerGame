//
//  GameScene.hpp
//  snookerGame-mobile
//
//  Created by Manish Saini
//

#ifndef GameScene_h
#define GameScene_h
#include <Box2D/Box2D.h>
#include <stdio.h>
#include "cocos2d.h"
#include "Ball.hpp"
USING_NS_CC;

class GameScene  : public cocos2d::Scene, b2ContactListener{
     GameScene();
    ~GameScene();
public:
    
    BALL_COLOR colorArr[15] = {BALL_COLOR::COLOR_RED,BALL_COLOR::COLOR_YELLOW,BALL_COLOR::COLOR_GREEN,BALL_COLOR::COLOR_BROWN,BALL_COLOR::COLOR_BLUE,BALL_COLOR::COLOR_PINK,COLOR_VIOLET,BALL_COLOR::COLOR_BLACK,   BALL_COLOR::COLOR_RED,BALL_COLOR::COLOR_YELLOW,BALL_COLOR::COLOR_GREEN,BALL_COLOR::COLOR_BROWN,BALL_COLOR::COLOR_BLUE,BALL_COLOR::COLOR_PINK,COLOR_VIOLET};
     
    Vector<Ball*> vecBalls;
    b2World *world;
    
    //CREATE A BALL
    Ball * ball;

    // set true if ball swiped
    bool isBallSwiped;
     
    float ballX;
    float ballY;
    int dragOffsetStartX;
    int dragOffsetEndX;
    int dragOffsetStartY;
    int dragOffsetEndY;
    Label *lblScore;
    float powerMultiplier;
 
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(GameScene);
    void initComponents();
    void createComponents();
    b2Body* addWall(float w,float h,float px,float py);
    
    // add all walls
    void createTableBorders();
    
    // add cue ball
    void defineCueBall();
    
    // add other balls
    void addBalls();
    void setBallsStartPos();// set all balls starting position
    void update(float dt);
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void BeginContact(b2Contact* contact);
 };
#endif /* GameScene_h */
