#include "PlayerScene.h"
#include "VisibleRect.h"
#include "FruitSprite.h"

USING_NS_CC;

using namespace std;

Scene* Player::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Player::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Player::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	initComponent();

	return true;
}

void Player::initComponent() {
	auto bg = Sprite::create("bg.png");
	bg->setAnchorPoint(Vec2(0.5,0));
	bg->setPosition(VisibleRect::bottom());
	addChild(bg);

	playingStatusBg = Sprite::create("playing_status.png");
	playingStatusBg->setAnchorPoint(Vec2(0.5, 1));
	playingStatusBg->setPosition(VisibleRect::top());
	addChild(playingStatusBg);

	updatePlayingStatusTip();

	initPlayGrid();
}

void Player::updatePlayingStatusTip() {
	auto levelBatchNode = SpriteBatchNode::create("numbertime.png");
	addChild(levelBatchNode);

	levelSprite = static_cast<Sprite*>(getChildByTag(LEVEL_SPRITE_TAG));
	if (levelSprite) {
		levelSprite->removeFromParent();
	}
	levelSprite = Sprite::createWithTexture(levelBatchNode->getTexture(), Rect(14 * (level),0,14,19));
	levelSprite->setPosition(Vec2(93,VisibleRect::getVisibleHeight() - 45));
	addChild(levelSprite,1,LEVEL_SPRITE_TAG);
}

void Player::initPlayGrid() {
	playGrid = Sprite::create("grid_bg.png");
	playGrid->setAnchorPoint(Vec2(0.5, 0));
	playGrid->setPosition(VisibleRect::bottom() + Vec2(0,50));
	addChild(playGrid, 1);

	bindGridEvent();

	fillGrid();
}

void Player::fillGrid() {
	srand(time(0));
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			Elem el = elems[i][j];
			if (el.blank) {
				auto fruit = generateFruit(i,j,el);
				playGrid->addChild(fruit);
				auto moveTo = MoveTo::create(0.3, Vec2(el.x, el.y));
				auto seq = Sequence::create(moveTo, CallFuncN::create(CC_CALLBACK_1(Player::fruitMoveToDest,this)),nullptr);
				fruit->runAction(seq);
			}
		}
	}
}

void Player::fruitMoveToDest(FruitSprite* fruit) {
	auto el = fruit->getElem();
	el.fruit = fruit;
}

FruitSprite* Player::generateFruit(int row, int col,Elem& el) {
	int kind = 4;
	switch (level) {
	case 1:
	case 2:
	case 3:
		kind = 4;
		break;
	case 4:
	case 5:
		kind = 5;
		break;
	case 6:
		kind = 6;
		break;
	case 7:
		kind = 7;
		break;
	default:
		kind = 8;
		break;
	}
	
	int fruitIdx = (rand() % kind) + 1;
	auto fruit = FruitSprite::create(StringUtils::format("fruit%d.png", fruitIdx));
	fruit->setAnchorPoint(Vec2(0.5, 0.5));
	float x = OFFSET_LEFT + (ELEM_WIDTH / 2.f) * (col * 2 + 1) + PADDING;
	float y = OFFSET_BOTTOM + (ELEM_HEIGHT / 2.f) * (row * 2 + 1) + PADDING + 10;
	if (row > 3) {
		y += 5;
	}
	el.x = x;
	el.y = y;
	fruit->setPosition(Vec2(x, ELEM_HEIGHT / 2.f) + (VisibleRect::top() - playGrid->getPosition()));
	el.fruitType = fruitIdx;
	el.blank = false;
	fruit->setElem(el);
	return fruit;
}

void Player::bindGridEvent() {
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchGridBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchGridMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchGridEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, playGrid);
}

bool Player::onTouchGridBegan(Touch* touch, Event* event) {
	auto p = playGrid->convertTouchToNodeSpace(touch);
	auto s = playGrid->getContentSize();
	auto r = Rect(0, 0, s.width, s.height);
	if (r.containsPoint(p)) {
		return true;
	}
	return false;
}

void Player::onTouchGridMoved(Touch* touch, Event* event) {
	auto p = playGrid->convertTouchToNodeSpaceAR(touch);
	int* coord = calculateGridPosByPoint(p);
	int x = coord[0], y = coord[1];
	delete[] coord;
	if (x >= 0 && x < COL && y >= 0 && y < COL) {
		Elem& el = elems[x][y];
		if (el.fruit && !el.selFruit) {
			doSelFruit(el);
		}
	}
}

void Player::doSelFruit(Elem& el) {
	int fruitType = el.fruitType;
	auto fruit = el.fruit;
	auto selFruit = FruitSprite::create(StringUtils::format("sel%d.png", fruitType));
	el.selFruit = selFruit;
	selFruit->setAnchorPoint(Vec2(0.5, 0.5));
	selFruit->setPosition(fruit->getPosition());
	fruit->setVisible(false);
	playGrid->addChild(selFruit);
	auto scale = ScaleBy::create(0.4, 0.7);
	auto scaleBack = scale->reverse();
	selFruit->runAction(RepeatForever::create(Sequence::create(scale, scaleBack, nullptr)));
}

void Player::onTouchGridEnded(Touch* touch, Event* event) {

}

int* Player::calculateGridPosByPoint(const Vec2& p) {
	auto actualP = p - OFFSET_POINT;
	float xCoord = actualP.x;
	float yCoord = actualP.y;
	int x = (int)(xCoord / (PADDING + ELEM_WIDTH));
	int y = (int)(yCoord / (PADDING + ELEM_HEIGHT));
	int* coord = new int[2];
	coord[0] = x;
	coord[1] = y;
	return coord;
}