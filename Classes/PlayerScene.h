#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

enum TAG {
	LEVEL_SPRITE_TAG,
	SEL_FRUIT_LINE_TAG
};

#define ROW 7
#define COL 7
#define ELEM_WIDTH 67
#define ELEM_HEIGHT 67
#define OFFSET_LEFT 3
#define OFFSET_BOTTOM 15
#define	PADDING 1
#define OFFSET_POINT Vec2(3,15);

typedef struct FruitElem {
	int row;
	int col;
	float x;
	float y;
	unsigned char fruitType;
	bool blank = true;
	FruitSprite* fruit = nullptr;
	FruitSprite* selFruit = nullptr;
	friend bool operator == (const Elem& el1, const Elem& el2);
} Elem;

bool operator== (const Elem& el1, const Elem& el2)  {
	return el1.row == el2.row && el1.col == el2.col;
}

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
	Elem elems[ROW][COL];
	int level = 1;
	Sprite* playingStatusBg;
	Sprite* levelSprite;
	Sprite* playGrid;
	Vector<const Elem&> selFruits;

	void initComponent();
	void updatePlayingStatusTip();
	void initPlayGrid();
	void fillGrid();
	FruitSprite* generateFruit(int row, int col,Elem& el);
	void bindGridEvent();
	bool onTouchGridBegan(Touch* touch, Event* event);
	void onTouchGridMoved(Touch* touch, Event* event);
	void onTouchGridEnded(Touch* touch, Event* event);
	int* calculateGridPosByPoint(const Vec2& p);
	void fruitMoveToDest(FruitSprite* fruit);
	void doSelFruit(Elem& el);
	void initGridElemCoord();
	void joinSelFruits(const Elem& el);
	bool elemAdjacent(const Elem& l, const Elem& r);
	void lineFruits();
};

#endif // __Payer_SCENE_H__
