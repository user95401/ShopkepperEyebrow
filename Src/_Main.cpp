#include "ModUtils.hpp"
#include "HooksUtils.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

#include "Layers/ShopkepperEyebrow.hpp"

HWND hWnd;

//onMultiplayer(cocos2d::CCObject* sender) = win 0x70330;
void __fastcall onMultiplayer(CCLayer* self, void* edx, CCObject* pSender) {
    //MappedHooks::getOriginal(onMultiplayer)(self, edx, pSender);
    ShopkepperEyebrow::create()->pushToMe(pSender);
}

//onAdventureMap(cocos2d::CCObject* sender) = win 0x706C0;
void __fastcall onAdventureMap(CCLayer* self, void* edx, CCObject* pSender) {
    //MappedHooks::getOriginal(onAdventureMap)(self, edx, pSender);
    ShopkepperEyebrow::create()->pushToMe(pSender);
}

//onEventLevel(cocos2d::CCObject* sender) = win 0x70740;
void __fastcall onEventLevel(CCLayer* self, void* edx, CCObject* pSender) {
    //MappedHooks::getOriginal(onAdventureMap)(self, edx, pSender);
    ShopkepperEyebrow::create()->pushToMe(pSender);
}

//MappedHooks::registerHook((DWORD)GetModuleHandle(0) + 0x271B30, LoadingLayer_init);
bool __fastcall LoadingLayer_init(CCLayer* self, void* edx, bool fromReload) {
    MappedHooks::getOriginal(LoadingLayer_init)(self, edx, fromReload);
    twoTimesBoolCallEscapeByParrentNode(self);
    //failed download label
    CCLabelBMFont* pCCLabelBMFont = CCLabelBMFont::create("", "bigFont.fnt");
    pCCLabelBMFont->setAnchorPoint(CCPointZero);
    pCCLabelBMFont->setPositionX(38.f / 2.2);
    pCCLabelBMFont->setPositionY(38.f);
    pCCLabelBMFont->setScale(0.20f);
    self->addChild(pCCLabelBMFont);
    //modResourcesPath
    ModUtils::AddSearchPathForMod();
    //ShopkepperEyebrow
    if (!CCFileUtils::sharedFileUtils()->isFileExist("ShopkepperEyebrow.png")) {
        if (S_OK != ModUtils::DownloadFile("", "ShopkepperEyebrow.png")) {
            //if fails add text
            pCCLabelBMFont->setString(std::format("{}\nFailed to download {}", pCCLabelBMFont->getString(),
                "ShopkepperEyebrow.png").c_str());
        }
    }
    //ShopkeppersMsg
    if (!CCFileUtils::sharedFileUtils()->isFileExist("ShopkeppersMsg.png")) {
        if (S_OK != ModUtils::DownloadFile("", "ShopkeppersMsg.png")) {
            //if fails add text
            pCCLabelBMFont->setString(std::format("{}\nFailed to download {}", pCCLabelBMFont->getString(),
                "ShopkeppersMsg.png").c_str());
        }
    }
    //ShopkeppersMsgTitle
    if (!CCFileUtils::sharedFileUtils()->isFileExist("ShopkeppersMsgTitle.png")) {
        if (S_OK != ModUtils::DownloadFile("", "ShopkeppersMsgTitle.png")) {
            //if fails add text
            pCCLabelBMFont->setString(std::format("{}\nFailed to download {}", pCCLabelBMFont->getString(),
                "ShopkeppersMsgTitle.png").c_str());
        }
    }
    return true;
}

DWORD WINAPI ModThread(void* hModule) {
    //game ver check
    if (ModUtils::GetGameVersion() != "2.200")
        if (MessageBoxA(hWnd, "This mod developed for Geometry Dash 2.200!\nStill countinue?", "Wrong game version", MB_OKCANCEL | MB_ICONWARNING) != IDOK)
            return 1;
    //othher stuff
    MH_Initialize();
    MappedHooks::registerHook(base + 0x70330, onMultiplayer);
    MappedHooks::registerHook(base + 0x706C0, onAdventureMap);
    MappedHooks::registerHook(base + 0x70740, onEventLevel);
    MappedHooks::registerHook(base + 0x271B30, LoadingLayer_init);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    hWnd = GetForegroundWindow();//сatch the game window right on launch (maybe on launch) hehe
    CreateThread(0, 0, ModThread, hModule, 0, 0);
    return TRUE;
}
