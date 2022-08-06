//
//  WelcomeScene.hpp
//  snookerGame-mobile
//
//  Created by Manish Saini  
//

#ifndef WelcomeScene_hpp
#define WelcomeScene_hpp

#include <stdio.h>

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene  : public cocos2d::Scene{
     WelcomeScene();
    ~WelcomeScene();
public:
   
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(WelcomeScene);
    
    void createComponents();
    
    void startGameCall();
    
};
#endif /* WelcomeScene_hpp */
