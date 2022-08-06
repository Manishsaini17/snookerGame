//
//  Ball.cpp
//  snookerGame-mobile
//
//  Created by Manish Saini 
//

#include "Ball.hpp"
Ball::Ball(){
    
}

Ball::~Ball(){
    
}
 
bool Ball::init(){
    if(!Sprite::initWithFile("ball.png")){
        return false;
    }
    this->setContentSize(Size(50,50));
    
    return true;
}

void Ball::setBallType(BALL_TYPE type){
    this->type = type;
}

void Ball::setBallNumber(int number){
    this->ballNumber = number;
}

void Ball::setBallColor(BALL_COLOR color){
    this->color = color;
    if(color == BALL_COLOR::COLOR_BLACK){
           this->setTexture("Balls/black.png");
       }else if(color == BALL_COLOR::COLOR_RED){
           this->setTexture("Balls/red.png");
       }else if(color == BALL_COLOR::COLOR_GREEN){
           this->setTexture("Balls/green.png");
       }else if(color == BALL_COLOR::COLOR_VIOLET){
           this->setTexture("Balls/violet.png");
       }else if(color == BALL_COLOR::COLOR_BROWN){
           this->setTexture("Balls/brown.png");
       }else if(color == BALL_COLOR::COLOR_BLUE){
           this->setTexture("Balls/blue.png");
       }else if(color == BALL_COLOR::COLOR_PINK){
           this->setTexture("Balls/pink.png");
       }else if(color == BALL_COLOR::COLOR_YELLOW){
           this->setTexture("Balls/yellow.png");
       }
}
