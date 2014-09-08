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

//  Created by Igor Yegoroff on 5/17/13.

#include "CCVirtualCurrency.h"

namespace soomla {
    // tovchenko: added
    CCVirtualCurrency::CCVirtualCurrency(cocos2d::ValueMap& params) {
        auto name = cocos2d::__String::create(params["name"].asString());
        auto description = cocos2d::__String::create(params["description"].asString());
        auto itemId = cocos2d::__String::create(params["itemId"].asString());
        
        init(name, description, itemId);
    }
    
    CCVirtualCurrency* CCVirtualCurrency::create(cocos2d::__String* name, cocos2d::__String* description, cocos2d::__String* itemId) {
        CCVirtualCurrency*ret = new CCVirtualCurrency();
        if (ret->init(name, description, itemId)) {
            ret->autorelease();
        } 
        else {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }

    cocos2d::__Dictionary *CCVirtualCurrency::toDictionary() {
        return this->putTypeData(CCVirtualItem::toDictionary(), CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CURRENCY);
    }
}