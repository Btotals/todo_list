#include "PushBoxScene.h"

#define SHIFT_LEFT 256
#define SHIFT_DOWN 192

const float SIZE_WSAD = 64.0;
const int FONT_SIZE = 64;


CCSprite *player;
TMXTiledMap *tmx;
PushBoxScene::PushBoxScene()
{
	_meta = NULL;
}

PushBoxScene::~PushBoxScene()
{
	CC_SAFE_RELEASE_NULL(_meta);
}

cocos2d::Scene* PushBoxScene::createScence() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PushBoxScene::create();

	// add layer as a child to scene
	scene->addChild(layer);


	scene->addChild(tmx, 100);

	CCTMXObjectGroup *object = tmx->getObjectGroup("player");
	ValueMap players = object->getObject("zergling");
	player = CCSprite::create("tile/hehe.png");
	player->setPosition(Point(256+SHIFT_LEFT, 384-SHIFT_DOWN));
	scene->addChild(player, 101);

	CCTMXObjectGroup *objects = tmx->getObjectGroup("boxs");
	ValueVector boxs = objects->getObjects();
	for (auto obj : boxs) {
		ValueMap value = obj.asValueMap();
		int x = value.at("x").asInt();
		int y = value.at("y").asInt();
		CCSprite *box = CCSprite::create("tile/box.png");
		box->setPosition(Point(x + SHIFT_LEFT, y + SHIFT_DOWN));
		scene->addChild(box, 101);
	}

	// return the scene
	return scene;
}

bool PushBoxScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	initTouchEvent();

	tmx = TMXTiledMap::create("box.tmx");
	tmx->setPosition(Point(480, 320));
	tmx->setAnchorPoint(Vec2(0.5, 0.5));
	
	this->setMeta(tmx->layerNamed("Meta"));
	_meta->setVisible(false);

	return true;
}



void PushBoxScene::initTouchEvent(){
	auto menu = Menu::create();
	menu->setPosition(visibleSize.width,0);
	menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	this->addChild(menu,10);

	auto label_W = Label::createWithTTF("W", "fonts/Marker Felt.ttf", FONT_SIZE);
	auto label_S = Label::createWithTTF("S", "fonts/Marker Felt.ttf", FONT_SIZE);
	auto label_A = Label::createWithTTF("A", "fonts/Marker Felt.ttf", FONT_SIZE);
	auto label_D = Label::createWithTTF("D", "fonts/Marker Felt.ttf", FONT_SIZE);

	auto button_up = MenuItemLabel::create(label_W, CC_CALLBACK_1(PushBoxScene::onUpPressed, this));
	auto button_down = MenuItemLabel::create(label_S, CC_CALLBACK_1(PushBoxScene::onDownPressed, this));
	auto button_left = MenuItemLabel::create(label_A, CC_CALLBACK_1(PushBoxScene::onLeftPressed, this));
	auto button_right = MenuItemLabel::create(label_D, CC_CALLBACK_1(PushBoxScene::onRightPressed, this));
	
	button_up->setPosition(SIZE_WSAD * -1, SIZE_WSAD * 2);
	button_down->setPosition(SIZE_WSAD * -1, SIZE_WSAD * 0);
	button_left->setPosition(SIZE_WSAD * -2, SIZE_WSAD * 1);
	button_right->setPosition(SIZE_WSAD * 0, SIZE_WSAD * 1);

	button_up->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	button_down->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	button_left->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	button_right->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);

	menu->addChild(button_up);
	menu->addChild(button_down);
	menu->addChild(button_left);
	menu->addChild(button_right);
}







void PushBoxScene::onRightPressed(Ref* sender)
{
	float x = player->getPositionX();
	float y = player->getPositionY();

	Point p = trans_coor(Point(x + 64, y));
	SetPlayerPosition(p);

}

void PushBoxScene::onLeftPressed(Ref* sender)
{
	float x = player->getPositionX();
	float y = player->getPositionY();

	Point p = trans_coor(Point(x - 64, y));
	SetPlayerPosition(p);
}

void PushBoxScene::onUpPressed(Ref* sender)
{
	float x = player->getPositionX();
	float y = player->getPositionY();
	Point p = trans_coor(Point(x, y + 64));
	
	SetPlayerPosition(p);
}

void PushBoxScene::onDownPressed(Ref* sender)
{
	float x = player->getPositionX();
	float y = player->getPositionY();
	Point p = trans_coor(Point(x, y - 64));
	
	SetPlayerPosition(p);
}


Point PushBoxScene::trans_coor(Point p) {
	int x = (p.x - SHIFT_LEFT) / 64;
	int y = 8 - p.y / 64;
	return ccp(x, y);
}

void PushBoxScene::SetPlayerPosition(Point p) {
	int id = _meta->tileGIDAt(p);

	if (id)
	{
		auto properties = tmx->propertiesForGID(id).asValueMap();
		if (!properties.empty())
		{
			if (properties.at("Collidable").asBool())
			{
				return;
			}
		}
	}
	Point as = Point(p.x * 64 + SHIFT_LEFT, (8 - p.y) * 64);
	player->setPosition(as);
}

