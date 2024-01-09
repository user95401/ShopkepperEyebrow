#include "ShopkepperEyebrow.hpp"

//custom button that similar to CCMenuItemSpriteExtra
#include "../CCMenuItemLabelExt.hpp"

class MyNotStruct : public ShopkepperEyebrow {
public:
    void asd(float) {

        //we love that
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        //a bg
        auto baga = TheObjOrSomeObj(CCSprite*, this->getChildByTag(8592));
        baga->setScaleX(winSize.width / baga->getContentSize().width);
        baga->setScaleY(winSize.height / baga->getContentSize().height);
        baga->setPosition(winSize / 2);

        //THE ShopkepperEyebrow
        auto ShopkepperEyebrow = TheObjOrSomeObj(CCSprite*, this->getChildByTag(7543));
        ShopkepperEyebrow->setScale((winSize.width / 2.8) / ShopkepperEyebrow->getContentSize().width);
        ShopkepperEyebrow->setPositionX(winSize.width);
        ShopkepperEyebrow->setAnchorPoint({ 1.2f, 0.f });

        //ShopkeppersMsg
        auto ShopkeppersMsg = TheObjOrSomeObj(CCSprite*, this->getChildByTag(1032));
        ShopkeppersMsg->setScale((winSize.width / 2) / ShopkeppersMsg->getContentSize().width);
        ShopkeppersMsg->setPositionY(winSize.height / 2.25);
        ShopkeppersMsg->setAnchorPoint({ -0.1f, 0.5f });

        //ShopkeppersMsg
        auto ShopkeppersMsgTitle = TheObjOrSomeObj(CCSprite*, this->getChildByTag(621));
        ShopkeppersMsgTitle->setScale((winSize.width / 2) / ShopkeppersMsgTitle->getContentSize().width);
        ShopkeppersMsgTitle->setPositionY(winSize.height / 1.35);
        ShopkeppersMsgTitle->setAnchorPoint({ -0.1f, 0.5f });

        auto menuThatExistOnlyForBackBtn = TheObjOrSomeObj(CCMenu*, this->getChildByTag(6254));
        menuThatExistOnlyForBackBtn->setPosition({ 24.000f, winSize.height - 24 });

    }
};

bool ShopkepperEyebrow::init() {
    //allow keypad for layer
    this->setKeypadEnabled(true);
    //allow touching for layer
    this->setTouchEnabled(true);

    //music
    GameManager::sharedState()->fadeInMusic("Deckers_Star_-_Inside_job_type_beat.mp3");

    //add stuff

    CCSprite* baga = ModUtils::createSprite("square.png");
    this->addChild(baga, -5, 8592);
    baga->setColor({ 255,255,255 });

    CCSprite* ShopkepperEyebrow = ModUtils::createSprite("ShopkepperEyebrow.png", 4.f);
    this->addChild(ShopkepperEyebrow, 0, 7543);

    CCSprite* ShopkeppersMsgTitle = ModUtils::createSprite("ShopkeppersMsgTitle.png", 4.f);
    this->addChild(ShopkeppersMsgTitle, 0, 621);

    CCSprite* ShopkeppersMsg = ModUtils::createSprite("ShopkeppersMsg.png", 4.f);
    this->addChild(ShopkeppersMsg, 0, 1032);

    auto GJ_arrow_03_001 = CCMenuItemLabelExt::create(
        ModUtils::createSprite("GJ_arrow_03_001.png"),
        this,
        menu_selector(ShopkepperEyebrow::onBack)
    );

    auto menuThatExistOnlyForBackBtn = CCMenu::createWithItem(GJ_arrow_03_001);
    this->addChild(menuThatExistOnlyForBackBtn, 0, 6254);

    //update stuff
    this->schedule(schedule_selector(MyNotStruct::asd), 0.1f);

    return true;
}

void ShopkepperEyebrow::onBack(CCObject* object) {
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}

void ShopkepperEyebrow::pushToMe(CCObject* pSender) {
    //soo, lets create CCScene with ShopkepperEyebrow idk what to say else
    //small code king
    auto scene = CCScene::create();
    scene->addChild(ShopkepperEyebrow::create());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
}

// This is the create method, a static method that creates
// a new instance, and initializes it.
ShopkepperEyebrow* ShopkepperEyebrow::create() {
    auto ret = new ShopkepperEyebrow();
    if (ret && ret->init()) {
        ret->autorelease();
    }
    else {
        // if `new` or `init` went wrong, delete the object and return a nullptr
        delete ret;
        ret = nullptr;
    }
    return ret;
}

//rewritable function that calling when u press escape or any alse back themed events
void ShopkepperEyebrow::keyBackClicked() {
    onBack(CCNode::create());//or nullptr
}
