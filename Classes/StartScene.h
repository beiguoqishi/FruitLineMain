//
//  StartScene.h
//  FruitLine
//
//  Created by liupengtao on 14-8-12.
//
//

#ifndef __FruitLine__StartScene__
#define __FruitLine__StartScene__

#include "cocos2d.h"

USING_NS_CC;

class Start : public Layer {
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
	// implement the "static create()" method manually
	CREATE_FUNC(Start);
    
private:
    void initComponent();
    void bindPlayListener(Sprite* playBtn);
};

#endif /* defined(__FruitLine__StartScene__) */
