//
//  WelcomeScene.cpp
//  snookerGame-mobile
//
//  Created by Manish Saini 
//

#include "WelcomeScene.hpp"
#include "GameScene.hpp"

WelcomeScene::WelcomeScene(){
    
}
WelcomeScene::~WelcomeScene(){
    
}

Scene* WelcomeScene::createScene(){
       
    return WelcomeScene::create();
}

bool WelcomeScene::init(){
   if (!Scene::init()) {
        return false;
    }
    createComponents();
    return true;
}

void WelcomeScene::createComponents(){
    LayerColor *layerBg = LayerColor::create(Color4B(200,200,200,255));
    this->addChild(layerBg);
    
    MenuItemLabel *lblStartGame = MenuItemLabel::create(Label::createWithTTF("Start Game", "fonts/arial.ttf", 90), CC_CALLBACK_0(WelcomeScene::startGameCall ,this));
    
    lblStartGame->setPosition(Vec2(this->getContentSize().width/2,this->getContentSize().height*0.5));
    
    lblStartGame->setColor(Color3B(10,200,20));
    
    
    Menu *menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    layerBg->addChild(menu);
    
    menu->addChild(lblStartGame);
    
}


void WelcomeScene::startGameCall(){
    Director::getInstance()->replaceScene(GameScene::createScene());
}
