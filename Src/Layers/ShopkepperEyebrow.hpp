#pragma once
#include "ModUtils.hpp"
using namespace cocos2d;
using namespace extension;
using namespace gd;

class ShopkepperEyebrow : public CCLayer {
public:
    inline static ShopkepperEyebrow* me;//why
    static ShopkepperEyebrow* create();
    virtual bool init();
    virtual void keyBackClicked();
    void pushToMe(CCObject*);
    void onBack(CCObject*);
};
