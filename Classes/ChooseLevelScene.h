#include "cocos2d.h"

class ChooseLevel : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScence();
	virtual bool init();
	void ReturnMain(Ref *ref);
	void Level_1(Ref *ref);

	CREATE_FUNC(ChooseLevel);
};