#include "ShopkepperEyebrow.hpp"
#include "../CCMenuItemLabelExt.hpp"

//custom button that similar to CCMenuItemSpriteExtra

bool ShopkepperEyebrow::init() {
    //allow keypad for layer
    this->setKeypadEnabled(true);
    //allow touching for layer
    this->setTouchEnabled(true);
    
    //we love that
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    //a bg
    CCSprite* baga = ModUtils::createSprite("square.png");
    this->addChild(baga, -5, 8592);
    baga->setScaleX(winSize.width / baga->getContentSize().width);
    baga->setScaleY(winSize.height / baga->getContentSize().height);
    baga->setPosition(winSize / 2);
    baga->setColor({255,255,255});

    CCMenu* Menu = CCMenu::create();
    Menu->setPosition(CCPoint());
    this->addChild(Menu, 100, 5940);//do u know that exists addChild(node, index) and addChild(node, index, tag)???

    auto GJ_arrow_03_001 = CCMenuItemLabelExt::create(
        ModUtils::createSprite("GJ_arrow_03_001.png"),
        this,
        menu_selector(ShopkepperEyebrow::onBack)
    );

    auto menuThatExistOnlyForBackBtn = CCMenu::createWithItem(GJ_arrow_03_001);
    this->addChild(menuThatExistOnlyForBackBtn);
    menuThatExistOnlyForBackBtn->setPosition({ 25.000f, winSize.height - 25 });


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
