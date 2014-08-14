#include "FruitSprite.h"

bool FruitSprite::init() {
	if (!Sprite::init()) {
		return false;
	}
	return true;
}

FruitSprite* FruitSprite::create(const string& filename) {
	auto fruit = new (std::nothrow) FruitSprite();
	if (fruit && fruit->initWithFile(filename)) {
		fruit->autorelease();
		return fruit;
	}
	CC_SAFE_DELETE(fruit);
	return nullptr;
}