//
// Created by Fedor Shubin on 6/25/14.
//

#include "CCServiceManager.h"
#include "CCNdkBridge.h"

USING_NS_CC;

namespace soomla {
    static CCServiceManager *sInstance = nullptr;

    CCServiceManager *CCServiceManager::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCServiceManager();
            sInstance->init();
            sInstance->retain();
        }
        return sInstance;
    }

    bool CCServiceManager::init() {
        CCCoreService::initShared();

        return true;
    }

    void CCServiceManager::setCommonParams(cocos2d::ValueMap& commonParams) {
        // todo: __Dictionary
        auto dict = __Dictionary::create();
        for (auto val : commonParams) {
            dict->setObject(__String::create(val.second.asString()), val.first);
        }
        
        __String *customSecret = dynamic_cast<__String *>(dict->objectForKey("customSecret"));
        if (customSecret == NULL || customSecret->length()==0) {
            __String *message = __String::createWithFormat("Can't initialize CCStoreService without customSecret");
            CCLOGERROR("%s %s", "CCServiceManager", message->getCString());

            return;
        }

        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCServiceManager::setCommonParams"), "method");
        params->setObject(dict, "params");
        CCNdkBridge::callNative(params, NULL);
    }
}

