
#include "JSBStoreAssets.h"

using namespace soomla;


JSBStoreAssets::JSBStoreAssets(cocos2d::ValueMap& storeParams) {
}

JSBStoreAssets::~JSBStoreAssets() {
    CC_SAFE_RELEASE(mCurrencies);
    CC_SAFE_RELEASE(mGoods);
    CC_SAFE_RELEASE(mCurrencyPacks);
    CC_SAFE_RELEASE(mCategories);
    CC_SAFE_RELEASE(mNonConsumableItems);
}

int JSBStoreAssets::getVersion() {
    return mVersion;
}

cocos2d::__Array *JSBStoreAssets::getCurrencies() {
    return mCurrencies;
}

cocos2d::__Array *JSBStoreAssets::getGoods() {
    return mGoods;
}

cocos2d::__Array *JSBStoreAssets::getCurrencyPacks() {
    return mCurrencyPacks;
}

cocos2d::__Array *JSBStoreAssets::getCategories() {
    return mCategories;
}

cocos2d::__Array *JSBStoreAssets::getNonConsumableItems() {
    return mNonConsumableItems;
}