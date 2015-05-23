#include "ChooseLevelScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* ChooseLevel::createScence(){
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ChooseLevel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool ChooseLevel::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//creat Level_1
	auto level_1 = MenuItemImage::create(
		"levelbutton/button_level_1.png", "levelbutton/button_clicked_level_1.png", "levelbutton/button_locked_level_1.png", CC_CALLBACK_1(ChooseLevel::Level_1, this));

	//creat Level_2
	auto level_2 = MenuItemImage::create(
		"levelbutton/button_level_2.png", "levelbutton/button_clicked_level_2.png", "levelbutton/button_locked_level_2.png", CC_CALLBACK_1(ChooseLevel::Level_1, this));
	level_2->setEnabled(false);

	auto menu = Menu::create(level_1, level_2, NULL);
	menu->alignItemsHorizontallyWithPadding(level_1->getContentSize().width / 3 * 2);
	menu->setPosition(visibleSize.width / 2, visibleSize.height-visibleSize.height/4);
	this->addChild(menu,1);

	auto bgsprite = Sprite::create("main_bg.png");
	float odds;
	float oddsY;
	oddsY = bgsprite->getContentSize().height / visibleSize.height;
	odds =  bgsprite->getContentSize().width / visibleSize.width;
	bgsprite->setScaleY(1 / oddsY);
	bgsprite->setScaleX(1/odds);
	bgsprite->setPosition(Vec2(visibleSize / 2) + origin);
	this->addChild(bgsprite,0);


	//background
	auto backItem = MenuItemImage::create("back_normal.png", "back_clicked.png", CC_CALLBACK_1(ChooseLevel::ReturnMain, this));
	backItem->setPosition(origin + Vec2(visibleSize.width,0) - Vec2(backItem->getContentSize().width,-backItem->getContentSize().height));
	auto menuback = Menu::create(backItem, NULL);
	menuback->setPosition(Vec2::ZERO);
	this->addChild(menuback, 1);

	//SpriteFrame
	auto newSprite = Sprite::create("image/Blue_Front1.png");
	newSprite->setPosition(Director::getInstance()->getVisibleSize().width / 5 * 4, Director::getInstance()->getVisibleSize().height / 5);
	this->addChild(newSprite);
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(12);
	animFrames.pushBack(SpriteFrame::create("image/Blue_Front1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Front2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Front3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Left1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Left2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Left3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Back1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Back2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Back3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Right1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Right2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Right3.png", Rect(0, 0, 65, 81)));

	// create the animation out of the frames
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animate = Animate::create(animation);
	newSprite->runAction(RepeatForever::create(animate));

	//progressBar
	auto progressSprite = Sprite::create("image/Blue_Front1.png");
	auto pT = ProgressTimer::create(progressSprite);
	pT->setType(ProgressTimer::Type::BAR);
	pT->setMidpoint(Point(0, 0));
	pT->setBarChangeRate(Point(1, 0));
	pT->runAction(RepeatForever::create(ProgressFromTo::create(5, 0, 100)));
	pT->setPosition(Point(200, 200));
	this->addChild(pT);
	return true;
}

void ChooseLevel::ReturnMain(Ref *ref)
{
	this->stopAllActions();
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void ChooseLevel::Level_1(Ref *ref)
{
	
}
