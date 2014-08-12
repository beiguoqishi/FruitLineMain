#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

enum TAG {
	LEVEL_SPRITE_TAG
};

class Player : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Player);
private:
	int level = 1;
	Sprite* playingStatusBg;
	Sprite* levelSprite;
	void initComponent();
	void updatePlayingStatusTip();
};

#endif // __Payer_SCENE_H__
