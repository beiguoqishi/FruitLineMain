//
//  StartScene.cpp
//  FruitLine
//
//  Created by liupengtao on 14-8-12.
//
//

#include "StartScene.h"
#include "VisibleRect.h"
#include "PlayerScene.h"

bool Start::init() {
    if (!Layer::init()) {
        return false;
    }
    
    initComponent();
    return true;
}

void Start::initComponent() {
    auto bg = Sprite::create("welcome.jpg");
    bg->setAnchorPoint(Vec2(0.5,0));
    bg->setPosition(VisibleRect::bottom());
    addChild(bg);

    auto gameTip = Sprite::create("title.png");
    gameTip->setAnchorPoint(Vec2(0.5,1));
    gameTip->setPosition(VisibleRect::top());
    addChild(gameTip);

    auto playBtn = Sprite::create("play.png");
    playBtn->setAnchorPoint(Vec2(0.5,0.5));
    playBtn->setPosition(VisibleRect::center());
    addChild(playBtn);
    bindPlayListener(playBtn);
}

void Start::bindPlayListener(Sprite *playBtn) {
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch,Event* event) {
        auto scale = ScaleBy::create(0.2, 1.5);
        playBtn->runAction(scale);
        return true;
    };
    listener->onTouchEnded = [=](Touch* touch,Event* event) {
        playBtn->stopAllActions();
        auto director = Director::getInstance();
        auto playerScene = Player::createScene();
        if (director->getRunningScene()) {
            auto flipXLeft = TransitionFlipX::create(1, playerScene, TransitionScene::Orientation::RIGHT_OVER);
            director->replaceScene(playerScene);
        } else {
            director->runWithScene(playerScene);
        }
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, playBtn);
}

Scene* Start::createScene() {
    auto scene = Scene::create();
    auto layer = Start::create();
    scene->addChild(layer);
    return scene;
}