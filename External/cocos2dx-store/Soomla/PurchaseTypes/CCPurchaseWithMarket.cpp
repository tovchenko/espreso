/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

// Created by Fedor Shubin on 5/19/13.

#include "CCPurchaseWithMarket.h"

namespace soomla {
    // tovchenko: added
    CCPurchaseWithMarket::CCPurchaseWithMarket(cocos2d::ValueMap& params)
    : mMarketItem(nullptr)
    {
        auto productId = cocos2d::__String::create(params["productId"].asString());
        auto price = cocos2d::__Double::create(params["price"].asDouble());
        
        initWithMarketItem(CCMarketItem::create(productId, cocos2d::CCInteger::create(CCMarketItem::CONSUMABLE), price));
    }
    
    CCPurchaseWithMarket *CCPurchaseWithMarket::create(cocos2d::__String *productId, cocos2d::__Double *price) {
        return createWithMarketItem(CCMarketItem::create(
                productId, cocos2d::CCInteger::create(CCMarketItem::CONSUMABLE), price));
    }

    CCPurchaseWithMarket *CCPurchaseWithMarket::createWithMarketItem(CCMarketItem *marketItem) {
        CCPurchaseWithMarket *ret = new CCPurchaseWithMarket();
        if (ret->initWithMarketItem(marketItem)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCPurchaseWithMarket::initWithMarketItem(CCMarketItem *marketItem) {
        bool res = CCPurchaseType::init();
        if (res) {
            setMarketItem(marketItem);
            return true;
        } else {
            return false;
        }
    }

    CCPurchaseWithMarket::~CCPurchaseWithMarket() {
        CC_SAFE_RELEASE(mMarketItem);
    }
}
