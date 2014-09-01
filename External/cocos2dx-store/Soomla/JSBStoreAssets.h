
// Created by Taras Tovchenko

#ifndef __JSBStoreAssets_H_
#define __JSBStoreAssets_H_


#include "cocos2d.h"
#include "CCStoreAssets.h"

namespace soomla {

    class JSBStoreAssets : public CCStoreAssets {
    public:
        JSBStoreAssets(cocos2d::ValueMap& storeParams);
        virtual ~JSBStoreAssets();
        
        virtual int getVersion();
        virtual cocos2d::__Array *getCurrencies();
        virtual cocos2d::__Array *getGoods();
        virtual cocos2d::__Array *getCurrencyPacks();
        virtual cocos2d::__Array *getCategories();
        virtual cocos2d::__Array *getNonConsumableItems();
        
    protected:
        cocos2d::__Array *mCurrencies = nullptr;
        cocos2d::__Array *mGoods = nullptr;
        cocos2d::__Array *mCurrencyPacks = nullptr;
        cocos2d::__Array *mCategories = nullptr;
        cocos2d::__Array *mNonConsumableItems = nullptr;
        int               mVersion = 1;
    };
}

#endif //__JSBStoreAssets_H_
