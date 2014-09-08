
// Created by Taras Tovchenko

#ifndef __JSBStoreAssets_H_
#define __JSBStoreAssets_H_


#include "cocos2d.h"
#include "CCStoreAssets.h"

namespace soomla {
    typedef cocos2d::__Array Array;

    class JSBStoreAssets : public CCStoreAssets {
    public:
        JSBStoreAssets() {}
        virtual ~JSBStoreAssets();
        
        auto addCategory(cocos2d::Ref* category)->void; // CCVirtualCategory
        auto addCurrency(cocos2d::Ref* currency)->void; // CCVirtualCurrency
        auto addCurrencyPack(cocos2d::Ref* pack)->void; // CCVirtualCurrencyPack
        auto addGood(cocos2d::Ref* good)->void; // CCVirtualGood
        auto addNonConsumableItem(cocos2d::Ref* item)->void; // CCNonConsumableItem
        auto setVersion(int ver)->void { _version = ver; }
        
    protected:
        virtual auto getVersion()->int { return _version; }
        virtual auto getCurrencies()->Array* override { return _currencies; }
        virtual auto getGoods()->Array* override { return _goods; }
        virtual auto getCurrencyPacks()->Array* override { return _currencyPacks; }
        virtual auto getCategories()->Array* override { return _categories; }
        virtual auto getNonConsumableItems()->Array* override { return _nonConsumableItems; }
        
        Array*  _currencies = nullptr;
        Array*  _goods = nullptr;
        Array*  _currencyPacks = nullptr;
        Array*  _categories = nullptr;
        Array*  _nonConsumableItems = nullptr;
        int     _version = 1;
    };
}

#endif //__JSBStoreAssets_H_
