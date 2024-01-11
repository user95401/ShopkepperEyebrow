#include "ModUtils.hpp"
#include "HooksUtils.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;
#include "Layers/ShopkepperEyebrow.hpp"
void __fastcall onOneOfGrayOnes(CCLayer* self, void* edx, CCObject* pSender) {
    ShopkepperEyebrow::create()->pushToMe(pSender);
}
//0x12D370
bool __fastcall MenuLayer_init(CCLayer* self, void* edx) {
    MappedHooks::getOriginal(MenuLayer_init)(self, edx);
    twoTimesBoolCallEscapeByParrentNode(self);
    //failed download label
    CCLabelBMFont* pCCLabelBMFont = CCLabelBMFont::create("", "bigFont.fnt");
    pCCLabelBMFont->setAnchorPoint(CCPointZero);
    pCCLabelBMFont->setPositionX(68.f / 1.8);
    pCCLabelBMFont->setPositionY(68.f);
    pCCLabelBMFont->setScale(0.30f);
    self->addChild(pCCLabelBMFont);
    //modResourcesPath
    ModUtils::AddSearchPathForMod();
    //ShopkepperEyebrow
    if (!ModUtils::FindOutIfFileExists("ShopkepperEyebrow.png")) {
        if (S_OK != ModUtils::DownloadFile("https://github.com/user95401/ShopkepperEyebrow/blob/main/Resources/ShopkepperEyebrow.png?raw=true", "ShopkepperEyebrow.png")) {
            //if fails add text
            pCCLabelBMFont->setString(std::format("{}\nFailed to download {}", pCCLabelBMFont->getString(),
                "ShopkepperEyebrow.png").c_str());
        }
    }
    //ShopkeppersMsg
    if (!ModUtils::FindOutIfFileExists("ShopkeppersMsg.png")) {
        if (S_OK != ModUtils::DownloadFile("https://github.com/user95401/ShopkepperEyebrow/blob/main/Resources/ShopkeppersMsg.png?raw=true", "ShopkeppersMsg.png")) {
            //if fails add text
            pCCLabelBMFont->setString(std::format("{}\nFailed to download {}", pCCLabelBMFont->getString(),
                "ShopkeppersMsg.png").c_str());
        }
    }
    //ShopkeppersMsgTitle
    if (!ModUtils::FindOutIfFileExists("ShopkeppersMsgTitle.png")) {
        if (S_OK != ModUtils::DownloadFile("https://github.com/user95401/ShopkepperEyebrow/blob/main/Resources/ShopkeppersMsgTitle.png?raw=true", "ShopkeppersMsgTitle.png")) {
            //if fails add text
            pCCLabelBMFont->setString(std::format("{}\nFailed to download {}", pCCLabelBMFont->getString(),
                "ShopkeppersMsgTitle.png").c_str());
        }
    }
    //ShopkeppersMsgTitle
    if (!ModUtils::FindOutIfFileExists("Deckers_Star_-_Inside_job_type_beat.mp3")) {
        if (S_OK != ModUtils::DownloadFile("https://github.com/user95401/ShopkepperEyebrow/raw/main/Resources/Deckers_Star_-_Inside_job_type_beat.mp3", "Deckers_Star_-_Inside_job_type_beat.mp3")) {
            //if fails add text
            pCCLabelBMFont->setString(std::format("{}\nFailed to download {}", pCCLabelBMFont->getString(),
                "Deckers_Star_-_Inside_job_type_beat.mp3").c_str());
        }
    }
    return true;
}
DWORD WINAPI ModThread(void* hModule) {
    //game ver check
    if (ModUtils::GetGameVersion() != "2.203")
        if (MessageBoxA(nullptr, "This mod developed for Geometry Dash 2.203!\nStill countinue?", "Wrong game version", MB_OKCANCEL | MB_ICONWARNING) != IDOK)
            return 1;
    //othher stuff
    MH_Initialize();
    MappedHooks::registerHook(base + 0x70780, onOneOfGrayOnes);
    MappedHooks::registerHook(base + 0x70B10, onOneOfGrayOnes);
    MappedHooks::registerHook(base + 0x70B90, onOneOfGrayOnes);
    MappedHooks::registerHook(base + 0x27B2E0, MenuLayer_init);
    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    CreateThread(0, 0, ModThread, hModule, 0, 0);
    return TRUE;
}
