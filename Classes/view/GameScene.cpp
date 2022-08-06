//
//  GameScene.cpp
//  snookerGame-mobile
//
//  Created by Manish Saini 
//

#include "GameScene.hpp"
#include "Common.hpp"

GameScene::GameScene(){
    
}

GameScene::~GameScene(){
    
}

Scene* GameScene::createScene(){
    return GameScene::create();
}

bool GameScene::init(){
   if (!Scene::init()) {
        return false;
    }
    initComponents();
    createComponents();
    return true;
}

void GameScene::initComponents(){
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //CREATE A BALL
    dragOffsetStartX = 0;
    dragOffsetEndX = 0;
    dragOffsetStartY = 0;
    dragOffsetEndY = 0;
    isBallSwiped = false;
    ballX = Director::getInstance()->getWinSize().width/2;
    ballY = Director::getInstance()->getWinSize().height*0.2f;
    powerMultiplier = 100;
}

void GameScene::createComponents(){
    
    LayerColor  *bgLayer    =       LayerColor::create(Color4B(255,255,255,0));
    this->addChild(bgLayer);
    
    Sprite *imgBg = Sprite::create("board.png");
    imgBg->setPosition(Vec2(this->getContentSize().width/2,this->getContentSize().height/2));
    this->addChild(imgBg);
    
     b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
     world = new b2World(gravity);
    
    lblScore = Label::createWithTTF("Score : ", "fonts/arial.ttf", 90);
    lblScore->setPosition(Vec2(this->getContentSize().width/2,this->getContentSize().height*0.8));
    this->addChild(lblScore);
    lblScore->setColor(Color3B(10,10,10));
    world->SetContactListener(this);
    createTableBorders();
    defineCueBall();
    addBalls();
    setBallsStartPos();
    scheduleUpdate();
}


void GameScene::createTableBorders(){
    addWall(DIRECTOR_VISIBLE_WIDTH ,50,(DIRECTOR_VISIBLE_WIDTH / 2) ,Director::getInstance()->getVisibleOrigin().y); //CEIL
    addWall(50 ,DIRECTOR_VISIBLE_HEIGHT ,Director::getInstance()->getVisibleOrigin().x,(DIRECTOR_VISIBLE_HEIGHT / 2) ); //LEFT
    addWall(50 ,DIRECTOR_VISIBLE_HEIGHT ,Director::getInstance()->getVisibleOrigin().x+DIRECTOR_VISIBLE_WIDTH,(DIRECTOR_VISIBLE_HEIGHT / 2) ); //RIGHT
    addWall(DIRECTOR_VISIBLE_WIDTH ,50,(DIRECTOR_VISIBLE_WIDTH / 2) ,Director::getInstance()->getVisibleOrigin().y+DIRECTOR_VISIBLE_HEIGHT); //CEIL
}

void GameScene::defineCueBall(){
        ball = Ball::create();
        ball->setBallType(BALL_TYPE::TYPE_CUE);
        ball->setBallColor(BALL_COLOR::COLOR_WHITE);
        ball->setPosition(CCPoint(ballX,ballY));
        this->addChild(ball);
    
       ball->ballShape.m_radius = (ball->getContentSize().width/2) / SCALE_RATIO;
       b2FixtureDef ballFixture;
       ballFixture.density = CUE_BALL_DENSITY;
       ballFixture.friction = CUE_BALL_FRICTION;
       ballFixture.restitution = CUE_BALL_RESTITUTION;
       ballFixture.shape=&ball->ballShape;

       ball->ballBodyDef.type= b2_dynamicBody;
       ball->ballBodyDef.userData=ball;
       ball->ballBodyDef.position.Set(ball->getPosition().x/SCALE_RATIO,ball->getPosition().y/SCALE_RATIO);
       ball->ballBody = world->CreateBody(&ball->ballBodyDef);
       ball->ballBody->CreateFixture(&ballFixture);
       ball->ballBody->SetGravityScale(0);
       ball->ballBody->SetAngularDamping(DEACCELERATION_FACTOR);
       ball->ballBody->SetLinearDamping(DEACCELERATION_FACTOR);
}
 
void GameScene::addBalls(){
    for(int i = 0; i< NUM_OF_BALLS ;i++){
        Ball *ball = Ball::create();
        vecBalls.pushBack(ball);
        ball->setBallNumber(i+1);
        ball->setBallColor(colorArr[i]);
        if(i < 7){
            ball->setBallType(BALL_TYPE::TYPE_SOLID);
        }else if(i == 7){
            ball->setBallType(BALL_TYPE::TYPE_BLACK);
        }else{
            ball->setBallType(BALL_TYPE::TYPE_STRIPE);
        }
        ball->setPosition(CCPoint(ballX,ballY));
        this->addChild(ball);
        
    }
}


void GameScene::setBallsStartPos(){
    int counter = 0;
    for (int i = 0; i< 5 ; i++) {
        float gapX = 1.0*((i+1.0f)/2.0f);
        float posX  = (Director::getInstance()->getWinSize().width*0.4)+(ball->getContentSize().width*gapX);
        float posY  = DIRECTOR_VISIBLE_HEIGHT*0.8f-ball->getContentSize().height*(i+1);
        for (int j = 0; j<5-i; j++) {
            Ball *ballObj ;
            if(counter == 7){
               ballObj = vecBalls.at(10);
            }else if(counter ==10){
                ballObj = vecBalls.at(7);
            }else{
                 ballObj = vecBalls.at(counter);
            }
            ballObj->setPosition(posX,posY);
            ballObj->ballShape.m_radius = (ballObj->getContentSize().width/2) / SCALE_RATIO;
            b2FixtureDef ballFixture;
            ballFixture.density = BALL_DENSITY;
            ballFixture.friction = BALL_FRICTION;
            ballFixture.restitution = BALL_RESTITUTION;
            ballFixture.shape=&ballObj->ballShape;
            ballObj->ballBodyDef.type= b2_dynamicBody;
            ballObj->ballBodyDef.userData=ballObj;
            ballObj->ballBodyDef.position.Set(ballObj->getPosition().x/SCALE_RATIO,ballObj->getPosition().y/SCALE_RATIO);
            ballObj->ballBody = world->CreateBody(&ballObj->ballBodyDef);
            ballObj->ballBody->CreateFixture(&ballFixture);
            ballObj->ballBody->SetAngularDamping(DEACCELERATION_FACTOR);
            ballObj->ballBody->SetLinearDamping(DEACCELERATION_FACTOR);
            counter++;
            posX += ballObj->getContentSize().width;
        }
    }
}

b2Body* GameScene::addWall(float w,float h,float px,float py) {
    b2PolygonShape floorShape;
    floorShape.SetAsBox(w/ SCALE_RATIO,h/ SCALE_RATIO);
    b2FixtureDef floorFixture;
    floorFixture.density = FLOOR_DENSITY;
    floorFixture.friction = FLOOR_FRICTION;
    floorFixture.restitution = FLOOR_RESTITUTION;
    floorFixture.shape=&floorShape;
    b2BodyDef floorBodyDef;

    floorBodyDef.position.Set(px/ SCALE_RATIO,py/ SCALE_RATIO);
    b2Body *floorBody = world->CreateBody(&floorBodyDef);
    floorBody->CreateFixture(&floorFixture);
    return floorBody ;
}

void GameScene::update(float dt){
 
  world->Step(dt, Commom::velocityIterations, Commom::positionIterations);
   for (b2Body *body = world->GetBodyList(); body != NULL; body = body->GetNext())
     if (body->GetUserData())
     {
       CCSprite *sprite = (CCSprite *) body->GetUserData();
       sprite->setPosition(ccp(body->GetPosition().x * SCALE_RATIO,body->GetPosition().y * SCALE_RATIO));
       sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
     }
    world->ClearForces();
    world->DrawDebugData();
}
 
bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
       dragOffsetStartX = touch->getLocation().x;
       dragOffsetStartY = touch->getLocation().y;
       CCPoint touchLocation = touch->getLocation();
       ballX = touchLocation.x;
       ballY = touchLocation.y;
 
    return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
   if(isBallSwiped){
       return;
   }
    Vec2 delta = touch->getDelta();
    log("delta pos  x %f  y %f",delta.x,delta.y);
    
    CCPoint touchLocation = touch->getLocation();
    dragOffsetEndX = touchLocation.x;
    dragOffsetEndY = touchLocation.y;
     
    float dragDistanceX =   dragOffsetEndX-dragOffsetStartX ;
    float dragDistanceY =   dragOffsetEndY -dragOffsetStartY   ;

    float dis =  delta.distance(Vec2(0,0));
    if(dis > SWIPE_FACTOR ){
        int  multiplier = powerMultiplier* dis;
        ball->ballBody->ApplyForceToCenter( b2Vec2(dragDistanceX*multiplier,dragDistanceY*multiplier),true);
        isBallSwiped = true;
    }else{
       ball->ballBody->SetTransform(b2Vec2(touchLocation.x/SCALE_RATIO,touchLocation.y/SCALE_RATIO), 0);
    }
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
    isBallSwiped = false;
}
 
void GameScene::BeginContact(b2Contact* contact) {
  if (contact->IsTouching()) {
      b2Fixture *a = contact->GetFixtureA();
      b2Fixture *b = contact->GetFixtureB();
      b2Body *aBody = a->GetBody();
      b2Body *bBody = b->GetBody();
      if ((aBody == ball->ballBody || bBody == ball->ballBody) && aBody!=NULL && bBody!=NULL) {
          b2Body    *otherBody   =   nullptr;
          otherBody         =       aBody==ball->ballBody?bBody:aBody;
      }
  }
}
