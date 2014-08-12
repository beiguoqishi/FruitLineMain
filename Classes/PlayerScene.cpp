#include "PlayerScene.h"
#include "VisibleRect.h"

USING_NS_CC;

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
