//
// Created by Fedor Shubin on 6/25/14.
//

#ifndef __CCServiceManager_H_
#define __CCServiceManager_H_

#include "cocos2d.h"
#include "CCCoreService.h"

namespace soomla {
    class CCServiceManager: cocos2d::Ref {
    public:
        static CCServiceManager *getInstance();
        bool init();
        void setCommonParams(cocos2d::ValueMap& commonParams);
    };
}

#endif //__CCServiceManager_H_
