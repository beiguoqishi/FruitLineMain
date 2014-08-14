#ifndef __FRUIT_SPRITE_H__
#define __FRUIT_SPRITE_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class FruitSprite : public Sprite {
public:
	virtual bool init();
	static FruitSprite* create(const string& filename);
	bool isSel = false;
	CC_SYNTHESIZE(Elem&, elem, Elem);
};

#endif