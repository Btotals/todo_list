#include "cocos2d.h"

USING_NS_CC;

class PushBoxScene :public Layer
{
public:
	PushBoxScene();
	~PushBoxScene();

	CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXLayer*, _meta, Meta);

	CREATE_FUNC(PushBoxScene);

	virtual bool init();


	void initTouchEvent();

	static cocos2d::Scene* createScence();

	void onRightPressed(Ref* sender);
	void onLeftPressed(Ref* sender);
	void onUpPressed(Ref* sender);
	void onDownPressed(Ref* sender);

	Point trans_coor(Point p);
	void SetPlayerPosition(Point P);

private:
	Size visibleSize;
};
